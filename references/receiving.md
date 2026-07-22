# Receiving Methods Reference

All receiving methods are accessed via `client.receiving.<method>()`.

## receiveNotification

**Purpose**: Receive one incoming notification from the queue (polling mode).

**Signature**:
```cpp
Response Receiving::receiveNotification(const unsigned int receiveTimeout = 5);
```

**Parameters**:
- `receiveTimeout` (integer, default: 5): Wait timeout in seconds (5-60 range recommended)

**Behavior**:
- Blocks until notification arrives or timeout expires
- If timeout expires: response is success but no receiptId
- Up to 100 unprocessed notifications in queue
- Must call `deleteNotification()` to remove from queue

**Response** (on success with message):
```json
{
  "receiptId": 12345,
  "body": {
    "typeWebhook": "incomingMessageReceived",
    "instanceData": {
      "idInstance": "1101000001"
    },
    "timestamp": 1234567890,
    "idMessage": "3EB0C67FA8C3DAF78C40D0C3",
    "senderData": {
      "chatId": "79876543210@c.us",
      "sender": "79876543210",
      "senderName": "John Doe"
    },
    "messageData": {
      "typeMessage": "textMessage",
      "textMessageData": {
        "textMessage": "Hello!"
      }
    }
  }
}
```

**Response** (on timeout - no notification):
```json
{
  "receiptId": 0
}
```

**Notification Types**:
- `incomingMessageReceived`: Text/media message
- `incomingCallReceived`: Incoming call (requires webhook settings)
- `outgoingMessageReceived`: Message from phone
- `outgoingAPIMessageReceived`: Message sent via API
- `messageStatusChanged`: Status update (sent, delivered, read)
- `deviceInfo`: Device status info

**Example - Simple Polling Loop**:
```cpp
#include "greenapi.hpp"
#include <thread>
#include <chrono>

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com", 
                    "1101000001", "your_token");
    
    std::cout << "Listening for messages..." << std::endl;
    
    while (true) {
        // Wait up to 30 seconds for notification
        Response notif = client.receiving.receiveNotification(30);
        
        if (!notif.success) {
            std::cerr << "API Error: " << notif.statusCode << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        
        // Check if we got a notification (receiptId > 0)
        if (!notif.body.contains("receiptId")) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        
        int receiptId = notif.body["receiptId"];
        if (receiptId == 0) {
            // Timeout, no notification
            continue;
        }
        
        // Extract notification details
        nlohmann::json body = notif.body["body"];
        std::string type = body.value("typeWebhook", "");
        
        if (type == "incomingMessageReceived") {
            std::string chatId = body["senderData"]["chatId"];
            std::string text = body["messageData"]["textMessageData"]["textMessage"];
            std::cout << "Message from " << chatId << ": " << text << std::endl;
        }
        
        // Remove notification from queue
        client.receiving.deleteNotification(receiptId);
    }
    
    return 0;
}
```

**Example - Message Type Handling**:
```cpp
Response notif = client.receiving.receiveNotification(5);
if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
    int receiptId = notif.body["receiptId"];
    nlohmann::json body = notif.body["body"];
    std::string type = body["typeWebhook"];
    
    if (type == "incomingMessageReceived") {
        nlohmann::json msgData = body["messageData"];
        std::string msgType = msgData["typeMessage"];
        
        if (msgType == "textMessage") {
            std::string text = msgData["textMessageData"]["textMessage"];
            std::cout << "Text: " << text << std::endl;
        } 
        else if (msgType == "imageMessage") {
            std::string url = msgData["imageMessageData"]["urlFile"];
            std::cout << "Image: " << url << std::endl;
        }
        else if (msgType == "documentMessage") {
            std::string filename = msgData["documentMessageData"]["fileName"];
            std::cout << "Document: " << filename << std::endl;
        }
    }
    
    client.receiving.deleteNotification(receiptId);
}
```

**Error Handling**:
- `401 Unauthorized`: Invalid credentials
- `404 Not Found`: Instance not found
- `500 Server Error`: API server issue (retry with backoff)

**Official Docs**: https://green-api.com/en/docs/api/receiving/technology-http-api/ReceiveNotification/

---

## deleteNotification

**Purpose**: Remove processed notification from queue.

**Signature**:
```cpp
Response Receiving::deleteNotification(const unsigned int receiptId);
```

**Parameters**:
- `receiptId` (integer): Receipt ID from `receiveNotification()` response

**Behavior**:
- Must be called after processing notification
- Prevents duplicate processing on reconnect
- Undeleted notifications stay in queue up to 24 hours

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
Response notif = client.receiving.receiveNotification(5);
if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
    int receiptId = notif.body["receiptId"];
    
    // Process notification...
    
    // Delete from queue
    Response delResp = client.receiving.deleteNotification(receiptId);
    if (delResp.success) {
        std::cout << "Notification deleted" << std::endl;
    }
}
```

**Important**: Always delete after processing to prevent:
- Queue overflow (max 100 notifications)
- Duplicate message processing
- Memory issues in long-running applications

**Official Docs**: https://green-api.com/en/docs/api/receiving/technology-http-api/DeleteNotification/

---

## downloadFile

**Purpose**: Download file from WhatsApp (incoming or outgoing message attachment).

**Signature**:
```cpp
Response Receiving::downloadFile(const nlohmann::json& message);
```

**Parameters**:
- `message` (object): File reference from notification
  - Must contain file metadata from received message

**Getting File URL**:
Files are available from incoming message notifications:

```json
{
  "messageData": {
    "typeMessage": "imageMessage",
    "imageMessageData": {
      "urlFile": "https://media.green-api.com/file123"
    }
  }
}
```

**Example - Download Received Image**:
```cpp
Response notif = client.receiving.receiveNotification(5);
if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
    nlohmann::json msgData = notif.body["body"]["messageData"];
    
    if (msgData["typeMessage"] == "imageMessage") {
        nlohmann::json fileInfo = msgData["imageMessageData"];
        
        // Download file
        Response dlResp = client.receiving.downloadFile(fileInfo);
        if (dlResp.success) {
            std::string fileContent = dlResp.body.dump();
            // Save to disk or process
            std::ofstream file("downloaded_image.jpg", std::ios::binary);
            // file << fileContent;
        }
    }
    
    client.receiving.deleteNotification(notif.body["receiptId"]);
}
```

**Supported File Types**:
- Images (`.jpg`, `.png`, `.gif`)
- Documents (`.pdf`, `.doc`, `.xls`)
- Audio (`.mp3`, `.wav`, `.m4a`)
- Video (`.mp4`, `.mov`)

**File URL Expiration**:
- URLs available for ~4 weeks after message
- Use `sending.getFileSaveTime()` to check expiration
- Download before expiration or upload to your storage

**Official Docs**: https://green-api.com/en/docs/api/receiving/files/DownloadFile/

---

## Webhook Alternative (Incoming Notifications)

Instead of polling, receive real-time notifications via HTTP callback:

**Setup**:
```cpp
nlohmann::json settings = {
    {"webhookUrl", "https://your-server.com/webhook"},
    {"webhookUrlToken", "secret-token"}  // optional auth header
};
client.account.setSettings(settings);
```

**Server Handler** (example):
```cpp
// POST /webhook
// GREEN-API sends notification JSON directly
// No polling needed, real-time delivery

void handleWebhook(const nlohmann::json& notification) {
    std::string type = notification["typeWebhook"];
    if (type == "incomingMessageReceived") {
        std::string text = notification["messageData"]["textMessageData"]["textMessage"];
        std::cout << "Received: " << text << std::endl;
    }
}
```

**Polling vs Webhook**:

| Feature | Polling | Webhook |
|---------|---------|---------|
| Latency | 5-30s | <1s (real-time) |
| Server | Client polls API | Server receives push |
| NAT/Firewall | Works behind NAT | Needs public endpoint |
| Implementation | Simpler | More complex |
| Availability | Always on | Requires uptime |

---

## Message Structure

### Text Message
```json
{
  "typeMessage": "textMessage",
  "textMessageData": {
    "textMessage": "Hello World"
  }
}
```

### Image Message
```json
{
  "typeMessage": "imageMessage",
  "imageMessageData": {
    "urlFile": "https://media.green-api.com/...",
    "caption": "Photo caption"
  }
}
```

### Document Message
```json
{
  "typeMessage": "documentMessage",
  "documentMessageData": {
    "urlFile": "https://media.green-api.com/...",
    "fileName": "document.pdf"
  }
}
```

### Audio Message
```json
{
  "typeMessage": "audioMessage",
  "audioMessageData": {
    "urlFile": "https://media.green-api.com/..."
  }
}
```

### Location Message
```json
{
  "typeMessage": "locationMessage",
  "locationMessageData": {
    "latitude": 55.7558,
    "longitude": 37.6173,
    "nameLocation": "Red Square, Moscow"
  }
}
```

---

## Common Pattern: Message Processing Loop

```cpp
#include "greenapi.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace greenapi;

class MessageProcessor {
    GreenApi client;
    
public:
    MessageProcessor(const std::string& id, const std::string& token)
        : client("https://api.green-api.com", "https://media.green-api.com", id, token) {}
    
    void start() {
        std::cout << "Message listener started" << std::endl;
        
        while (true) {
            try {
                processNotifications();
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
    }
    
private:
    void processNotifications() {
        Response notif = client.receiving.receiveNotification(30);
        
        if (!notif.success) {
            std::cerr << "API error: " << notif.statusCode << std::endl;
            return;
        }
        
        if (!notif.body.contains("receiptId")) return;
        
        int receiptId = notif.body["receiptId"];
        if (receiptId == 0) return;  // Timeout
        
        try {
            handleNotification(notif.body["body"]);
        } catch (const std::exception& e) {
            std::cerr << "Processing error: " << e.what() << std::endl;
        }
        
        // Always delete
        client.receiving.deleteNotification(receiptId);
    }
    
    void handleNotification(const nlohmann::json& body) {
        std::string type = body["typeWebhook"];
        
        if (type == "incomingMessageReceived") {
            handleMessage(body);
        }
        else if (type == "messageStatusChanged") {
            handleStatusChange(body);
        }
        else if (type == "incomingCallReceived") {
            handleCall(body);
        }
    }
    
    void handleMessage(const nlohmann::json& body) {
        std::string chatId = body["senderData"]["chatId"];
        std::string msgType = body["messageData"]["typeMessage"];
        
        std::cout << "[" << chatId << "] " << msgType << std::endl;
        
        if (msgType == "textMessage") {
            std::string text = body["messageData"]["textMessageData"]["textMessage"];
            std::cout << "  Text: " << text << std::endl;
        } else if (msgType == "imageMessage") {
            std::string url = body["messageData"]["imageMessageData"]["urlFile"];
            std::cout << "  Image: " << url << std::endl;
        }
    }
    
    void handleStatusChange(const nlohmann::json& body) {
        std::string status = body["messageData"]["statusMessage"];
        std::cout << "Message status: " << status << std::endl;
    }
    
    void handleCall(const nlohmann::json& body) {
        std::string from = body["senderData"]["chatId"];
        std::cout << "Incoming call from: " << from << std::endl;
    }
};

int main() {
    MessageProcessor processor(
        std::getenv("GREEN_API_ID") ?: "1101000001",
        std::getenv("GREEN_API_TOKEN") ?: ""
    );
    
    processor.start();
    return 0;
}
```

---

**Last Updated**: 2024
**SDK Version**: Latest from github.com/green-api/whatsapp-api-client-cpp
