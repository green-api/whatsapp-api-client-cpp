# Using GREEN-API C++ SDK Skill

This guide explains how to use the GREEN-API C++ SDK skill with AI agents (Claude, Cursor, etc.).

## Installation

1. **Copy skill files to your AI agent's context:**
   - `SKILL.md` - Main skill file
   - `references/` - Detailed method documentation
   
2. **Add to agent instructions/prompts:**
   ```
   When writing C++ code for GREEN-API WhatsApp SDK:
   1. Read SKILL.md for initialization and patterns
   2. Check references/*.md for specific methods
   3. Always verify method names against SDK source code
   4. Test with real credentials before deployment
   ```

## What's Included

### Main Files
- **SKILL.md** - Entry point with:
  - Client initialization patterns
  - 5 common scenarios with full code
  - Best practices and pitfalls
  - Quick method index
  - Error handling guide

### Reference Documentation (in `references/`)
- **sending.md** - 11 sending methods (messages, files, media)
- **receiving.md** - 3 receiving methods (polling, notifications, downloads)
- **account.md** - 11 account methods (auth, settings, state)
- **groups.md** - 9 group management methods
- **journals.md** - 6 history/audit methods
- **statuses.md** - 7 WhatsApp Stories methods
- **queues.md** - 2 queue management methods
- **readMark.md** - 1 read status method
- **serviceMethods.md** - 11 utility methods (contacts, chats, etc.)

**Total: 61 methods documented**

## How AI Agents Use This Skill

### Example: Agent Writes Message Sending Code

**User Query:**
```
Write C++ code to send "Hello" to phone +79876543210 using GREEN-API
```

**Agent Process:**
1. Reads SKILL.md → finds "Scenario 1: Sending Text Message"
2. Uses template code as basis
3. Checks `references/sending.md` for `sendMessage()` details
4. Generates working code with error handling
5. Ensures credentials aren't hardcoded

**Output Code:**
```cpp
#include "greenapi.hpp"
#include <nlohmann/json.hpp>

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", 
                    "https://media.green-api.com",
                    std::getenv("GREEN_API_ID") ?: "",
                    std::getenv("GREEN_API_TOKEN") ?: "");
    
    Response auth = client.account.getStateInstance();
    if (!auth.success || auth.body["stateInstance"] != "authorized") {
        std::cerr << "Not authorized" << std::endl;
        return 1;
    }
    
    nlohmann::json msg = {
        {"chatId", "79876543210@c.us"},
        {"message", "Hello"}
    };
    
    Response resp = client.sending.sendMessage(msg);
    if (resp.success) {
        std::cout << "Sent: " << resp.body["idMessage"] << std::endl;
    }
    
    return 0;
}
```

### Example: Agent Builds Message Polling Loop

**User Query:**
```
Write a program that listens for incoming WhatsApp messages and prints them
```

**Agent Process:**
1. Reads SKILL.md → "Scenario 2: Receiving Messages (Polling)"
2. References `receiving.md` for detailed API
3. Implements proper notification handling
4. Adds error recovery

**Output Code:**
```cpp
#include "greenapi.hpp"
#include <thread>
#include <iostream>

using namespace greenapi;

int main() {
    GreenApi client("https://api.green-api.com", "https://media.green-api.com",
                    std::getenv("GREEN_API_ID") ?: "",
                    std::getenv("GREEN_API_TOKEN") ?: "");
    
    while (true) {
        Response notif = client.receiving.receiveNotification(30);
        
        if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
            int receiptId = notif.body["receiptId"];
            auto body = notif.body["body"];
            
            if (body["typeWebhook"] == "incomingMessageReceived") {
                std::string from = body["senderData"]["chatId"];
                std::string text = body["messageData"]["textMessageData"]["textMessage"];
                std::cout << from << ": " << text << std::endl;
            }
            
            client.receiving.deleteNotification(receiptId);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}
```

## Verification Checklist

When agent generates code, ensure:

- ✓ All method names match SDK exactly (see 61 verified methods in verify summary)
- ✓ Class names correct: `Sending`, `Receiving`, `Account`, `Groups`, etc.
- ✓ Chat ID format: `<phone>@c.us` (personal) or `<phone>-<timestamp>@g.us` (group)
- ✓ `Response` object checked with `.success` before accessing `.body`
- ✓ No hardcoded credentials (use env vars)
- ✓ Error handling for HTTP status codes
- ✓ Respects rate limits (900ms delay, 1 group per 5 min)

## Common Patterns Agent Should Use

### 1. Initialization
```cpp
GreenApi client(
    "https://api.green-api.com",
    "https://media.green-api.com",
    std::getenv("GREEN_API_ID") ?: "1101000001",
    std::getenv("GREEN_API_TOKEN") ?: ""
);
```

### 2. Auth Check
```cpp
Response auth = client.account.getStateInstance();
if (!auth.success || auth.body["stateInstance"] != "authorized") {
    // Handle not authorized
}
```

### 3. Send with Error Handling
```cpp
Response resp = client.sending.sendMessage(msg);
if (resp.success) {
    // Use resp.body["idMessage"]
} else {
    std::cerr << "Error " << resp.statusCode << ": " << resp.body << std::endl;
}
```

### 4. Receive Loop
```cpp
while (true) {
    Response notif = client.receiving.receiveNotification(30);
    if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
        // Process notification
        client.receiving.deleteNotification(notif.body["receiptId"]);
    }
}
```

### 5. JSON Parameter Building
```cpp
nlohmann::json params = {
    {"chatId", "79876543210@c.us"},
    {"message", "Hello"},
    {"optionalField", value}
};
Response resp = client.sending.sendMessage(params);
```

## Testing Generated Code

After agent generates code:

1. **Check compilation:**
   ```bash
   g++ -std=c++17 -o test_msg your_code.cpp -L./build -lgreenapi -I./include
   ```

2. **Set credentials:**
   ```bash
   export GREEN_API_ID="your_id"
   export GREEN_API_TOKEN="your_token"
   ```

3. **Run test:**
   ```bash
   ./test_msg
   ```

4. **Verify output:**
   - No compilation errors
   - No runtime crashes
   - Message sent (check console output)

## Skill Maintenance

When SDK updates:

1. **Run verification script:**
   ```bash
   /tmp/verify_methods.sh
   ```

2. **If new methods added:**
   - Add to SKILL.md quick index
   - Create reference in appropriate `references/*.md`
   - Update method count in summary

3. **If methods renamed/removed:**
   - Update SKILL.md scenarios
   - Update references
   - Re-run verification

## API Documentation Links

- Official API Docs: https://green-api.com/en/docs/api/
- SDK Repository: https://github.com/green-api/whatsapp-api-client-cpp
- Console (credentials): https://console.green-api.com

## Support & Issues

If agent generates code that doesn't work:

1. Check method name against SKILL.md index
2. Verify chat ID format (`@c.us` or `@g.us`)
3. Confirm instance is authorized
4. Check rate limits (delay, group creation)
5. Review error code in official docs

---

**Skill Version**: 1.0.0
**Last Verified**: 2024
**Methods Verified**: 61/61 ✓
