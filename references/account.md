# Account Methods Reference

All account methods are accessed via `client.account.<method>()`.

## getSettings

**Purpose**: Get current instance settings and phone number.

**Signature**:
```cpp
Response Account::getSettings();
```

**Parameters**: None

**Response**:
```json
{
  "wid": "79876543210@c.us",
  "webhookUrl": "https://your-server.com/webhook",
  "webhookUrlToken": "secret",
  "delaySendMessagesMilliseconds": 900,
  "markIncomingMessagesAsRead": true,
  "markIncomingMessagesReadOnReply": false,
  "outgoingWebhook": true,
  "outgoingMessageWebhook": true,
  "outgoingCallWebhook": false,
  "statusInstance": "authorized",
  "stateInstance": "authorized",
  "incomingWebhook": true
}
```

**Key Fields**:
- `wid`: Phone number ID (use to verify correct account)
- `stateInstance`: `authorized` or `notAuthorized`
- `delaySendMessagesMilliseconds`: Minimum delay between sends (default 900ms)
- `webhookUrl`: Where notifications are sent (if webhook mode enabled)

**Example**:
```cpp
Response resp = client.account.getSettings();
if (resp.success) {
    std::string phone = resp.body["wid"];
    std::string state = resp.body["stateInstance"];
    int delay = resp.body["delaySendMessagesMilliseconds"];
    
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "State: " << state << std::endl;
    std::cout << "Send delay: " << delay << "ms" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetSettings/

---

## setSettings

**Purpose**: Modify instance settings (webhook, delays, notifications).

**Signature**:
```cpp
Response Account::setSettings(const nlohmann::json& settings);
```

**Configurable Parameters**:
- `webhookUrl` (string): Receive incoming notifications at this URL
- `webhookUrlToken` (string): Authorization header for webhook requests
- `delaySendMessagesMilliseconds` (integer): Delay between messages (900+ ms)
- `markIncomingMessagesAsRead` (boolean): Auto-mark as read
- `markIncomingMessagesReadOnReply` (boolean): Mark read only on reply
- `outgoingWebhook` (boolean): Send webhook on outgoing messages
- `incomingWebhook` (boolean): Send webhook on incoming messages
- `outgoingMessageWebhook` (boolean): Detailed webhook for each message
- `outgoingCallWebhook` (boolean): Notify about calls

**Example - Enable Webhook**:
```cpp
nlohmann::json settings = {
    {"webhookUrl", "https://api.example.com/webhook"},
    {"webhookUrlToken", "Bearer secret-token-123"},
    {"incomingWebhook", true}
};
Response resp = client.account.setSettings(settings);
```

**Example - Increase Send Delay**:
```cpp
nlohmann::json settings = {
    {"delaySendMessagesMilliseconds", 5000}  // 5 seconds between messages
};
client.account.setSettings(settings);
```

**Official Docs**: https://green-api.com/en/docs/api/account/SetSettings/

---

## getStateInstance

**Purpose**: Check if account is authorized and ready for messaging.

**Signature**:
```cpp
Response Account::getStateInstance();
```

**Response**:
```json
{
  "stateInstance": "authorized"
}
```

**Possible States**:
- `authorized`: Ready for messaging
- `notAuthorized`: Must scan QR or use phone auth
- `sleeping`: Device in sleep mode

**Example**:
```cpp
Response resp = client.account.getStateInstance();
if (resp.success) {
    std::string state = resp.body["stateInstance"];
    if (state == "authorized") {
        std::cout << "Ready to send messages!" << std::endl;
    } else {
        std::cout << "Instance not authorized" << std::endl;
        // Show QR code or auth method
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetStateInstance/

---

## getStatusInstance

**Purpose**: Check socket connection status with WhatsApp servers.

**Signature**:
```cpp
Response Account::getStatusInstance();
```

**Response**:
```json
{
  "statusInstance": "connected"
}
```

**Possible Statuses**:
- `connected`: Online and ready
- `disconnected`: Not connected to WhatsApp
- `connecting`: In progress

**Example**:
```cpp
Response resp = client.account.getStatusInstance();
if (resp.success) {
    std::string status = resp.body["statusInstance"];
    if (status == "connected") {
        std::cout << "Online!" << std::endl;
    } else {
        std::cout << "Waiting for connection..." << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetStatusInstance/

---

## qr

**Purpose**: Get QR code for account authorization.

**Signature**:
```cpp
Response Account::qr();
```

**Response**:
```json
{
  "qr": "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADIAAABy..."
}
```

**Authorization Flow**:
1. Call `qr()`
2. Decode base64 image (PNG format)
3. Display or save to file
4. Scan with WhatsApp Business app on phone
5. Wait for `stateInstance` to change to `authorized`

**Example**:
```cpp
#include <fstream>
#include <regex>

Response qrResp = client.account.qr();
if (qrResp.success) {
    std::string qrData = qrResp.body["qr"];
    
    // Decode base64 and save as PNG
    std::string base64Data = qrData.substr(qrData.find(",") + 1);
    // Use base64 decoder library to save binary PNG
    
    std::cout << "QR Code generated. Scan to authorize." << std::endl;
    
    // Poll for authorization
    for (int i = 0; i < 60; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        Response stateResp = client.account.getStateInstance();
        if (stateResp.success && stateResp.body["stateInstance"] == "authorized") {
            std::cout << "Authorized!" << std::endl;
            break;
        }
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/QR/

---

## getAuthorizationCode

**Purpose**: Get authorization code for phone number (alternative to QR).

**Signature**:
```cpp
Response Account::getAuthorizationCode(const unsigned long long phoneNumber);
```

**Parameters**:
- `phoneNumber` (long long): Phone number without prefix (e.g., `79876543210` for +7-987-654-3210)

**Response**:
```json
{
  "code": "123-456"
}
```

**Authorization Flow**:
1. Call with phone number
2. WhatsApp sends authorization code to phone via SMS or WhatsApp
3. User enters code in WhatsApp Business app
4. Instance becomes authorized

**Example**:
```cpp
Response codeResp = client.account.getAuthorizationCode(79876543210LL);
if (codeResp.success) {
    std::string code = codeResp.body["code"];
    std::cout << "Authorization code sent. Code: " << code << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetAuthorizationCode/

---

## scanqrcode

**Purpose**: Get QR code via WebSocket (real-time updates).

**Signature**:
```cpp
Response Account::scanqrcode();
```

**Response**: Similar to `qr()`, but via persistent WebSocket connection.

**Use Case**: Applications needing real-time QR code updates without polling.

**Example**:
```cpp
Response wsResp = client.account.scanqrcode();
// Connect to WebSocket URL in response
// Receive real-time QR code updates
```

**Official Docs**: https://green-api.com/en/docs/api/account/Scanqrcode/

---

## getWaSettings

**Purpose**: Get WhatsApp account information.

**Signature**:
```cpp
Response Account::getWaSettings();
```

**Response**:
```json
{
  "name": "John Doe",
  "phone": "79876543210",
  "waId": "79876543210@c.us",
  "status": "available",
  "profilePicUrl": "https://..."
}
```

**Example**:
```cpp
Response resp = client.account.getWaSettings();
if (resp.success) {
    std::string name = resp.body["name"];
    std::string phone = resp.body["phone"];
    std::cout << "Account: " << name << " (" << phone << ")" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetWaSettings/

---

## getStateInstanceHistory

**Purpose**: Get history of instance state changes.

**Signature**:
```cpp
Response Account::getStateInstanceHistory(const unsigned int count = 100);
```

**Parameters**:
- `count` (integer, default 100): Number of records to return (max 100)

**Response**:
```json
{
  "data": [
    {
      "stateInstance": "authorized",
      "timestamp": 1234567890
    },
    {
      "stateInstance": "notAuthorized",
      "timestamp": 1234567800
    }
  ]
}
```

**Example**:
```cpp
Response resp = client.account.getStateInstanceHistory(50);
if (resp.success) {
    nlohmann::json data = resp.body["data"];
    for (auto& entry : data) {
        std::string state = entry["stateInstance"];
        long timestamp = entry["timestamp"];
        std::cout << state << " @ " << timestamp << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/GetStateInstanceHistory/

---

## reboot

**Purpose**: Restart the instance (temporary disconnect/reconnect).

**Signature**:
```cpp
Response Account::reboot();
```

**Response**:
```json
{
  "result": true
}
```

**Use Cases**:
- Fix connection issues
- Reset state after errors
- Force reconnection to WhatsApp

**Example**:
```cpp
std::cout << "Rebooting instance..." << std::endl;
Response resp = client.account.reboot();
if (resp.success) {
    std::cout << "Reboot initiated" << std::endl;
    // Wait a moment for reconnection
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/Reboot/

---

## logout

**Purpose**: Logout account (deauthorize).

**Signature**:
```cpp
Response Account::logout();
```

**Response**:
```json
{
  "result": true
}
```

**Effect**:
- Instance becomes unauthorized
- Must re-scan QR or use phone auth
- Phone will disconnect from WhatsApp in this instance

**Example**:
```cpp
Response resp = client.account.logout();
if (resp.success) {
    std::cout << "Logged out" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/account/Logout/

---

## Account Authorization Flow

```cpp
#include "greenapi.hpp"
#include <thread>

using namespace greenapi;

class AccountAuth {
    GreenApi client;
    
public:
    AccountAuth(const std::string& id, const std::string& token)
        : client("https://api.green-api.com", "https://media.green-api.com", id, token) {}
    
    bool ensureAuthorized() {
        // Check current state
        Response stateResp = client.account.getStateInstance();
        if (!stateResp.success) {
            std::cerr << "Failed to check state" << std::endl;
            return false;
        }
        
        std::string state = stateResp.body["stateInstance"];
        if (state == "authorized") {
            std::cout << "Already authorized" << std::endl;
            return true;
        }
        
        // Not authorized, request QR code
        Response qrResp = client.account.qr();
        if (!qrResp.success) {
            std::cerr << "Failed to get QR" << std::endl;
            return false;
        }
        
        std::string qrData = qrResp.body["qr"];
        // Save/display QR
        std::cout << "QR Code ready. Scan to authorize." << std::endl;
        
        // Wait for authorization (max 5 minutes)
        for (int i = 0; i < 300; i++) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            
            Response checkResp = client.account.getStateInstance();
            if (checkResp.success && checkResp.body["stateInstance"] == "authorized") {
                std::cout << "Authorization successful!" << std::endl;
                return true;
            }
        }
        
        std::cerr << "Authorization timeout" << std::endl;
        return false;
    }
};
```

---

**Last Updated**: 2024
**SDK Version**: Latest from github.com/green-api/whatsapp-api-client-cpp
