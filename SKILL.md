---
name: GREEN-API C++ SDK
version: 1.0.0
description: AI Skill for writing correct code with GREEN-API WhatsApp API SDK (C++)
tags: [whatsapp, api, green-api, c++, messaging]
status: stable
author: GREEN-API
documentation: https://green-api.com/en/docs/api/
sdk_repository: https://github.com/green-api/whatsapp-api-client-cpp
---

# GREEN-API C++ SDK Skill

This skill teaches AI agents to write **correct and production-ready code** using the GREEN-API WhatsApp SDK for C++. All method names, classes, and parameters are verified against the official SDK source code.

## When to Use This Skill

Use this skill when:
- Writing C++ applications for WhatsApp messaging via GREEN-API
- Sending/receiving WhatsApp messages, files, or media
- Managing groups, contacts, or account settings
- Polling notifications or handling webhooks
- Implementing WhatsApp automation, bots, or integrations

## Key Constraints & Best Practices

### 1. Phone Number Formats (Critical)
- **Personal chat**: `71234567890@c.us` (country code + number + `@c.us`)
- **Group chat**: `79876543210-1581234048@g.us` (creator number - timestamp + `@g.us`)
- Always include the suffix (`@c.us` or `@g.us`)
- Without proper format, messages will fail silently

### 2. Instance Authorization
- **Account must be authorized** before sending messages
- Authorization methods: `account.qr()`, `account.scanqrcode()`, or `account.getAuthorizationCode()`
- Check authorization status: `account.getStateInstance()` → state must be `authorized`
- Unauthorized instances queue messages for up to 24 hours

### 3. Message Send Delays
- **Minimum delay between messages**: 900ms (configurable via `delaySendMessagesMilliseconds` setting)
- To avoid rate limiting: set delay manually via `account.setSettings()` or through console
- Group messages have same delay requirement
- Respect WhatsApp rules: simulate human behavior

### 4. Method Response Structure
All methods return `Response` object:
```cpp
struct Response {
    bool success;           // true if request succeeded
    int statusCode;         // HTTP status code
    nlohmann::json body;    // Response JSON body
};
```
- Always check `response.success` before accessing `response.body`
- Non-2xx status codes indicate API or network errors
- Check official docs for error codes: https://green-api.com/en/docs/api/

### 5. JSON Parameters (nlohmann/json)
- Most methods accept `nlohmann::json` objects as parameters
- Use direct JSON construction: `nlohmann::json msg = {{"chatId", "79876543210@c.us"}, {"message", "Hello"}}`
- Required fields vary by method (see references/)
- Extra fields are ignored; missing required fields cause 4xx errors

## Client Initialization

### Standard Setup
```cpp
#include "greenapi.hpp"
using namespace greenapi;

int main() {
    // Initialize with API credentials from https://console.green-api.com
    GreenApi client(
        "https://api.green-api.com",           // apiUrl
        "https://media.green-api.com",         // mediaUrl
        "1101000001",                          // idInstance (your instance number)
        "aabbccddeeff00112233445566778899"     // apiTokenInstance (your token)
    );
    
    // Use client.sending, client.receiving, client.account, etc.
    return 0;
}
```

### Credentials Source
- Get `idInstance` and `apiTokenInstance` from: https://console.green-api.com
- Do **NOT** hardcode credentials; use environment variables or config files
- Example:
```cpp
#include <cstdlib>
std::string idInstance = std::getenv("GREEN_API_ID") ?: "1101000001";
std::string apiToken = std::getenv("GREEN_API_TOKEN") ?: "";
GreenApi client("https://api.green-api.com", "https://media.green-api.com", idInstance, apiToken);
```

## Common Scenarios

### Scenario 1: Sending Text Message

**When**: You need to send a WhatsApp message to a contact or group.

**Method**: `client.sending.sendMessage(message)`

**Code**:
```cpp
#include "greenapi.hpp"
#include <nlohmann/json.hpp>
using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com", 
                    "1101000001", "your_api_token");
    
    // Verify authorization first
    Response auth = client.account.getStateInstance();
    if (!auth.success || auth.body["stateInstance"] != "authorized") {
        std::cerr << "Instance not authorized!" << std::endl;
        return 1;
    }
    
    // Send message to personal chat
    nlohmann::json message = {
        {"chatId", "79876543210@c.us"},
        {"message", "Hello from GREEN-API!"}
    };
    Response resp = client.sending.sendMessage(message);
    
    if (resp.success) {
        std::cout << "Message sent! ID: " << resp.body["idMessage"] << std::endl;
    } else {
        std::cerr << "Error: " << resp.statusCode << " - " << resp.body << std::endl;
    }
    
    return 0;
}
```

**Error Handling**:
- `401 Unauthorized`: Check `idInstance` and `apiTokenInstance`
- `400 Bad Request`: Verify `chatId` format (must end with `@c.us` or `@g.us`)
- `429 Too Many Requests`: Respect send delay (900ms minimum)

---

### Scenario 2: Receiving Messages (Polling)

**When**: You need to listen for incoming messages in a loop.

**Methods**: `client.receiving.receiveNotification()`, `client.receiving.deleteNotification()`

**Code**:
```cpp
#include "greenapi.hpp"
#include <chrono>
#include <thread>

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com", 
                    "1101000001", "your_api_token");
    
    std::cout << "Polling for notifications (Ctrl+C to stop)..." << std::endl;
    
    while (true) {
        // Receive one notification (waits up to 5 seconds)
        Response notif = client.receiving.receiveNotification(5);
        
        if (notif.success && notif.body.contains("receiptId")) {
            int receiptId = notif.body["receiptId"];
            nlohmann::json body = notif.body.value("body", nlohmann::json::object());
            
            // Check notification type
            std::string type = body.value("typeWebhook", "");
            if (type == "incomingMessageReceived") {
                std::string chatId = body.value("senderData", nlohmann::json::object())
                                         .value("chatId", "unknown");
                std::string text = body.value("messageData", nlohmann::json::object())
                                       .value("textMessageData", nlohmann::json::object())
                                       .value("textMessage", "");
                
                std::cout << "Message from " << chatId << ": " << text << std::endl;
                
                // Delete notification from queue
                client.receiving.deleteNotification(receiptId);
            }
        }
        
        // Small delay to avoid busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
```

**Key Points**:
- `receiveTimeout` (default 5s): how long to wait for a notification
- If timeout expires and no notification: response.success is true but no receiptId
- Always call `deleteNotification()` after processing to remove from queue
- Unprocessed notifications stay in queue (up to 100 notifications)

---

### Scenario 3: Sending File by URL

**When**: You need to send an image, PDF, or other file from a URL.

**Method**: `client.sending.sendFileByUrl(message)`

**Code**:
```cpp
#include "greenapi.hpp"

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com", 
                    "1101000001", "your_api_token");
    
    nlohmann::json message = {
        {"chatId", "79876543210@c.us"},
        {"urlFile", "https://example.com/image.jpg"},
        {"fileName", "photo.jpg"},
        {"caption", "Check this image!"}  // optional
    };
    
    Response resp = client.sending.sendFileByUrl(message);
    if (resp.success) {
        std::cout << "File sent! Message ID: " << resp.body["idMessage"] << std::endl;
    } else {
        std::cerr << "Error: " << resp.statusCode << std::endl;
    }
    
    return 0;
}
```

**Supported File Types**:
- Images: `.jpg`, `.png`, `.gif`, `.webp`
- Documents: `.pdf`, `.doc`, `.xls`, `.ppt`, etc.
- Audio/Video: `.mp3`, `.mp4`, `.wav`, etc.
- Max size: 100 MB

---

### Scenario 4: Creating and Managing Groups

**When**: You need to create groups, add members, or manage settings.

**Methods**: `client.groups.createGroup()`, `client.groups.addGroupParticipant()`, etc.

**Code**:
```cpp
#include "greenapi.hpp"

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com", 
                    "1101000001", "your_api_token");
    
    // Create group (max 1 group per 5 minutes)
    nlohmann::json groupData = {
        {"groupName", "My awesome group"},
        {"participants", nlohmann::json::array({
            "79876543210@c.us",
            "79876543211@c.us"
        })}
    };
    
    Response createResp = client.groups.createGroup(groupData);
    if (!createResp.success) {
        std::cerr << "Failed to create group!" << std::endl;
        return 1;
    }
    
    std::string groupId = createResp.body["chatId"];
    std::cout << "Group created: " << groupId << std::endl;
    
    // Add another participant
    nlohmann::json addMember = {
        {"groupId", groupId},
        {"participantChatId", "79876543212@c.us"}
    };
    client.groups.addGroupParticipant(addMember);
    
    // Send message to group
    nlohmann::json groupMsg = {
        {"chatId", groupId},
        {"message", "Welcome to the group!"}
    };
    client.sending.sendMessage(groupMsg);
    
    return 0;
}
```

**Constraints**:
- Group creation: **max 1 group per 5 minutes** (anti-spam)
- Group ID format: `<creator_number>-<timestamp>@g.us`
- Participants must be valid phone numbers with `@c.us` suffix

---

### Scenario 5: Setting Up Webhook for Incoming Messages

**When**: You want asynchronous notifications via HTTP callback (instead of polling).

**Setup Steps**:

1. **Configure webhook URL** in your instance settings:
```cpp
nlohmann::json settings = {
    {"webhookUrl", "https://your-server.com/webhook"},
    {"webhookUrlToken", "your-secret-token"}  // optional, for authorization header
};
Response resp = client.account.setSettings(settings);
```

2. **Implement webhook endpoint** (your server):
```cpp
// Example using a simple HTTP library (e.g., crow, pistache, etc.)
// POST /webhook
void handleWebhook(const nlohmann::json& payload) {
    std::string type = payload.value("typeWebhook", "");
    
    if (type == "incomingMessageReceived") {
        nlohmann::json data = payload["body"]["messageData"];
        std::string text = data["textMessageData"]["textMessage"];
        std::string from = payload["body"]["senderData"]["chatId"];
        
        std::cout << "Message from " << from << ": " << text << std::endl;
    }
}
```

3. **Webhook vs Polling Trade-offs**:
   - **Webhook**: Real-time, lower latency, requires public endpoint
   - **Polling**: Works behind NAT/firewall, simpler setup, higher latency

---

## API Method Reference

### Method Groups

All methods are organized into groups via `GreenApi` class members:

| Class | Purpose | See |
|-------|---------|-----|
| `client.account` | Account state, auth, settings | `references/account.md` |
| `client.sending` | Send messages, files, media | `references/sending.md` |
| `client.receiving` | Receive messages, download files | `references/receiving.md` |
| `client.groups` | Create/manage groups | `references/groups.md` |
| `client.journals` | Chat history, call logs | `references/journals.md` |
| `client.statuses` | Send/view WhatsApp stories | `references/statuses.md` |
| `client.queues` | Manage send queue | `references/queues.md` |
| `client.readMark` | Mark messages as read | `references/readMark.md` |
| `client.serviceMethods` | Avatar, contacts, chat list | `references/serviceMethods.md` |

### Quick Method Index

**Account**: `getSettings`, `setSettings`, `getStateInstance`, `getStatusInstance`, `reboot`, `logout`, `qr`, `scanqrcode`, `getAuthorizationCode`, `getWaSettings`, `getStateInstanceHistory`

**Sending**: `sendMessage`, `sendPoll`, `sendFileByUpload`, `sendFileByUrl`, `uploadFile`, `getFileSaveTime`, `sendLocation`, `sendContact`, `forwardMessages`, `sendInteractiveButtons`, `sendInteractiveButtonsReply`

**Receiving**: `receiveNotification`, `deleteNotification`, `downloadFile`

**Groups**: `createGroup`, `updateGroupName`, `getGroupData`, `addGroupParticipant`, `removeGroupParticipant`, `setGroupAdmin`, `removeAdmin`, `leaveGroup`, `updateGroupSettings`

**Journals**: `getChatHistory`, `getMessage`, `lastIncomingMessages`, `lastOutgoingMessages`, `lastIncomingCalls`, `lastOutgoingCalls`

**Statuses**: `sendTextStatus`, `sendVoiceStatus`, `sendMediaStatus`, `deleteStatus`, `getStatusStatistic`, `getIncomingStatuses`, `getOutgoingStatuses`

**Queues**: `showMessagesQueue`, `clearMessagesQueue`

**ReadMark**: `readChat`

**ServiceMethods**: `checkWhatsapp`, `getAvatar`, `getContacts`, `getContactInfo`, `editMessage`, `deleteMessage`, `archiveChat`, `unarchiveChat`, `setDisappearingChat`, `getChats`, `sendTyping`

---

## Common Pitfalls & Solutions

### ❌ Pitfall: Invalid Chat ID Format
```cpp
// WRONG - missing suffix
client.sending.sendMessage({
    {"chatId", "79876543210"},
    {"message", "Hi"}
});
```
**✅ Fix**:
```cpp
client.sending.sendMessage({
    {"chatId", "79876543210@c.us"},  // personal chat
    {"message", "Hi"}
});
// OR for group:
client.sending.sendMessage({
    {"chatId", "79876543210-1581234048@g.us"},  // group chat
    {"message", "Hi"}
});
```

---

### ❌ Pitfall: Ignoring Authorization
```cpp
// WRONG - assuming instance is already authorized
Response resp = client.sending.sendMessage({
    {"chatId", "79876543210@c.us"},
    {"message", "Hi"}
});
// Message fails or sits in queue for 24 hours
```
**✅ Fix**:
```cpp
// Always check auth first
Response authCheck = client.account.getStateInstance();
if (!authCheck.success) {
    std::cerr << "API error: " << authCheck.statusCode << std::endl;
    return 1;
}

std::string state = authCheck.body["stateInstance"];
if (state != "authorized") {
    // Trigger QR code flow
    Response qrResp = client.account.qr();
    std::cout << "Scan QR: " << qrResp.body["qr"] << std::endl;
    return 1;
}

// Now safe to send
client.sending.sendMessage({
    {"chatId", "79876543210@c.us"},
    {"message", "Hi"}
});
```

---

### ❌ Pitfall: Not Checking Response Success
```cpp
// WRONG
Response resp = client.sending.sendMessage(msg);
std::cout << "Sent: " << resp.body["idMessage"] << std::endl;
// Crashes if send failed
```
**✅ Fix**:
```cpp
Response resp = client.sending.sendMessage(msg);
if (resp.success) {
    std::cout << "Sent: " << resp.body["idMessage"] << std::endl;
} else {
    std::cerr << "Send failed (HTTP " << resp.statusCode << "): " 
              << resp.body.dump() << std::endl;
}
```

---

### ❌ Pitfall: Too-Frequent Group Creation
```cpp
// WRONG - tries to create multiple groups immediately
for (int i = 0; i < 10; i++) {
    client.groups.createGroup(groupData);  // Rate-limited to 1 per 5 min
}
```
**✅ Fix**:
```cpp
#include <thread>
#include <chrono>

// Create with 5-minute gap
for (int i = 0; i < 10; i++) {
    client.groups.createGroup(groupData);
    std::this_thread::sleep_for(std::chrono::minutes(5));
}
```

---

### ❌ Pitfall: Infinite Polling Loop (CPU Spike)
```cpp
// WRONG - busy-waits, uses 100% CPU
while (true) {
    Response notif = client.receiving.receiveNotification(5);
    if (notif.body.contains("receiptId")) {
        processNotification(notif);
    }
    // No delay!
}
```
**✅ Fix**:
```cpp
while (true) {
    Response notif = client.receiving.receiveNotification(5);
    if (notif.body.contains("receiptId")) {
        processNotification(notif);
        client.receiving.deleteNotification(notif.body["receiptId"]);
    }
    // Add small delay even if no notification
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
```

---

## Error Codes

| Code | Meaning | Solution |
|------|---------|----------|
| `401 Unauthorized` | Bad API credentials | Check `idInstance` and `apiTokenInstance` |
| `403 Forbidden` | Invalid instance state | Authorize instance with QR or phone |
| `400 Bad Request` | Missing/invalid field | Check required fields for method |
| `404 Not Found` | Invalid chat/group ID | Verify phone format: `<number>@c.us` or `<number>-<ts>@g.us` |
| `429 Too Many Requests` | Rate limit exceeded | Increase delay between sends |
| `500 Server Error` | API server issue | Retry after delay |

---

## Tips for AI Agent Developers

1. **Always include error handling**: Check `response.success` and status codes
2. **Verify phone formats**: Personal=`@c.us`, Groups=`@g.us`
3. **Respect rate limits**: 900ms minimum delay, 1 group per 5 minutes
4. **Use environment variables** for credentials, never hardcode
5. **Test with real instance**: Simulator not available; use test account from console
6. **Check official docs** for each method: https://green-api.com/en/docs/api/
7. **Review examples**: See `examples/` directory in SDK repository

---

## Building & Testing

```bash
# Clone and build SDK
git clone https://github.com/green-api/whatsapp-api-client-cpp.git
cd whatsapp-api-client-cpp
mkdir build && cd build
cmake ..
make

# Build example with your credentials
export GREEN_API_ID="your_id"
export GREEN_API_TOKEN="your_token"
g++ -std=c++17 -o sendMessage examples/sendMessage.cpp -L./build -lgreenapi -I./include
./sendMessage
```

---

## References

Detailed method documentation:
- [Account Methods](references/account.md)
- [Sending Methods](references/sending.md)
- [Receiving Methods](references/receiving.md)
- [Groups Methods](references/groups.md)
- [Journals Methods](references/journals.md)
- [Statuses Methods](references/statuses.md)
- [Queues Methods](references/queues.md)
- [ReadMark Methods](references/readMark.md)
- [ServiceMethods Methods](references/serviceMethods.md)

Official Documentation: https://green-api.com/en/docs/api/

SDK Repository: https://github.com/green-api/whatsapp-api-client-cpp

---

**Last Updated**: 2024
**SDK Version**: Compatible with latest from https://github.com/green-api/whatsapp-api-client-cpp
**Verification**: All methods and class names verified against official SDK source code
