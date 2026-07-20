# ServiceMethods Reference

All service methods are accessed via `client.serviceMethods.<method>()`.

Miscellaneous utility methods for contacts, chats, and account operations.

---

## checkWhatsapp

**Purpose**: Verify if phone number has active WhatsApp account.

**Signature**:
```cpp
Response ServiceMethods::checkWhatsapp(const unsigned long long phoneNumber);
```

**Parameters**:
- `phoneNumber` (long long): Phone without prefix (e.g., `79876543210`)

**Response**:
```json
{
  "numberExists": true
}
```

**Example**:
```cpp
Response resp = client.serviceMethods.checkWhatsapp(79876543210LL);
if (resp.success && resp.body["numberExists"]) {
    std::cout << "WhatsApp account exists!" << std::endl;
} else {
    std::cout << "No WhatsApp account" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/service/CheckWhatsapp/

---

## getAvatar

**Purpose**: Download user or group profile picture.

**Signature**:
```cpp
Response ServiceMethods::getAvatar(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID in `<phone>@c.us` or `<group>@g.us` format

**Response**:
```json
{
  "urlFile": "https://media.green-api.com/avatar_...",
  "type": "image/jpeg"
}
```

**Example**:
```cpp
nlohmann::json query = {
    {"chatId", "79876543210@c.us"}
};

Response resp = client.serviceMethods.getAvatar(query);
if (resp.success) {
    std::string avatarUrl = resp.body["urlFile"];
    std::cout << "Avatar: " << avatarUrl << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/service/GetAvatar/

---

## getContacts

**Purpose**: Get list of all saved contacts.

**Signature**:
```cpp
Response ServiceMethods::getContacts();
```

**Response**:
```json
{
  "contacts": [
    {
      "id": "79876543210@c.us",
      "name": "John Doe",
      "shortName": "John"
    },
    {
      "id": "79876543211@c.us",
      "name": "Jane Smith"
    }
  ]
}
```

**Example**:
```cpp
Response resp = client.serviceMethods.getContacts();
if (resp.success) {
    for (auto& contact : resp.body["contacts"]) {
        std::string name = contact.value("name", "Unknown");
        std::string id = contact["id"];
        std::cout << name << ": " << id << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/service/GetContacts/

---

## getContactInfo

**Purpose**: Get detailed information about specific contact.

**Signature**:
```cpp
Response ServiceMethods::getContactInfo(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Contact ID in `<phone>@c.us` format

**Response**:
```json
{
  "id": "79876543210@c.us",
  "name": "John Doe",
  "shortName": "John",
  "wa": true,
  "statusText": "At work",
  "profilePicUrl": "https://..."
}
```

**Example**:
```cpp
nlohmann::json query = {
    {"chatId", "79876543210@c.us"}
};

Response resp = client.serviceMethods.getContactInfo(query);
if (resp.success) {
    std::string name = resp.body["name"];
    std::string status = resp.body["statusText"];
    std::cout << name << " - " << status << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/service/GetContactInfo/

---

## editMessage

**Purpose**: Edit already-sent message.

**Signature**:
```cpp
Response ServiceMethods::editMessage(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID
- `idMessage` (string): ID of message to edit
- `message` (string): New message text

**Response**:
```json
{
  "result": true
}
```

**Constraints**:
- Can only edit text messages
- Can only edit your own messages
- Limited time window to edit (typically ~15 minutes)

**Example**:
```cpp
nlohmann::json edit = {
    {"chatId", "79876543210@c.us"},
    {"idMessage", "3EB0C67FA8C3DAF78C40D0C3"},
    {"message", "Fixed typo: the correct answer is..."}
};

Response resp = client.serviceMethods.editMessage(edit);
```

**Official Docs**: https://green-api.com/en/docs/api/service/editMessage/

---

## deleteMessage

**Purpose**: Delete message from chat.

**Signature**:
```cpp
Response ServiceMethods::deleteMessage(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID
- `idMessage` (string): ID of message to delete

**Response**:
```json
{
  "result": true
}
```

**Constraints**:
- Can only delete your own messages
- Limited time window to delete (typically ~1 hour)
- Message appears as "[deleted]" for others

**Example**:
```cpp
nlohmann::json del = {
    {"chatId", "79876543210@c.us"},
    {"idMessage", "3EB0C67FA8C3DAF78C40D0C3"}
};

client.serviceMethods.deleteMessage(del);
```

**Official Docs**: https://green-api.com/en/docs/api/service/deleteMessage/

---

## archiveChat

**Purpose**: Archive a chat (hide from main list).

**Signature**:
```cpp
Response ServiceMethods::archiveChat(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID

**Constraints**:
- Chat must have at least one message to archive

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json archive = {
    {"chatId", "79876543210@c.us"}
};

client.serviceMethods.archiveChat(archive);
```

**Official Docs**: https://green-api.com/en/docs/api/service/archiveChat/

---

## unarchiveChat

**Purpose**: Restore archived chat to main list.

**Signature**:
```cpp
Response ServiceMethods::unarchiveChat(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json unarchive = {
    {"chatId", "79876543210@c.us"}
};

client.serviceMethods.unarchiveChat(unarchive);
```

**Official Docs**: https://green-api.com/en/docs/api/service/unarchiveChat/

---

## setDisappearingChat

**Purpose**: Set disappearing messages timer for chat.

**Signature**:
```cpp
Response ServiceMethods::setDisappearingChat(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID
- `expiration` (integer): Timer in seconds

**Valid Values**:
- `0` - Off (default)
- `86400` - 24 hours
- `604800` - 7 days
- `7776000` - 90 days

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
// Set disappearing messages to 24 hours
nlohmann::json setting = {
    {"chatId", "79876543210@c.us"},
    {"expiration", 86400}
};

client.serviceMethods.setDisappearingChat(setting);
```

**Official Docs**: https://green-api.com/en/docs/api/service/SetDisappearingChat/

---

## getChats

**Purpose**: Get list of all chats (personal and group).

**Signature**:
```cpp
Response ServiceMethods::getChats(const unsigned int count = 100);
```

**Parameters**:
- `count` (integer, default 100): Number of chats to return (0 = all chats)

**Response**:
```json
{
  "chats": [
    {
      "id": "79876543210@c.us",
      "name": "John Doe",
      "isGroup": false,
      "isArchived": false,
      "unreadMessages": 5,
      "lastMessage": {
        "timestamp": 1234567890,
        "textMessage": "See you later!"
      }
    },
    {
      "id": "79876543210-1581234048@g.us",
      "name": "Project Team",
      "isGroup": true,
      "isArchived": false
    }
  ]
}
```

**Note**: Updates at most once per minute

**Example**:
```cpp
// Get last 50 chats
Response resp = client.serviceMethods.getChats(50);
if (resp.success) {
    for (auto& chat : resp.body["chats"]) {
        std::string name = chat["name"];
        int unread = chat.value("unreadMessages", 0);
        std::cout << name << " (" << unread << " unread)" << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/service/GetChats/

---

## sendTyping

**Purpose**: Show "typing..." or "recording audio" indicator in chat.

**Signature**:
```cpp
Response ServiceMethods::sendTyping(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID

**Optional Parameters**:
- `typingTime` (integer): Duration in milliseconds (1000-20000, default 5000)
- `typingType` (string): `"recording"` for audio, omit for typing

**Response**:
```json
{
  "result": true
}
```

**Example - Show Typing**:
```cpp
nlohmann::json typing = {
    {"chatId", "79876543210@c.us"},
    {"typingTime", 3000}  // Show for 3 seconds
};

client.serviceMethods.sendTyping(typing);
```

**Example - Show Recording**:
```cpp
nlohmann::json recording = {
    {"chatId", "79876543210@c.us"},
    {"typingType", "recording"},
    {"typingTime", 5000}
};

client.serviceMethods.sendTyping(recording);
```

**Official Docs**: https://green-api.com/en/docs/api/service/SendTyping/

---

## Common Patterns

### Chat Management Example

```cpp
#include "greenapi.hpp"

using namespace greenapi;

class ChatManager {
    GreenApi client;
    
public:
    ChatManager(const std::string& id, const std::string& token)
        : client("https://api.green-api.com", "https://media.green-api.com", id, token) {}
    
    void listAllChats() {
        Response resp = client.serviceMethods.getChats(0);  // 0 = all chats
        if (resp.success) {
            for (auto& chat : resp.body["chats"]) {
                std::string name = chat["name"];
                bool isGroup = chat["isGroup"];
                std::cout << (isGroup ? "[G] " : "[P] ") << name << std::endl;
            }
        }
    }
    
    void archiveOldChats() {
        Response resp = client.serviceMethods.getChats(100);
        if (resp.success) {
            for (auto& chat : resp.body["chats"]) {
                if (!chat.value("isArchived", false)) {
                    nlohmann::json archive = {
                        {"chatId", chat["id"]}
                    };
                    client.serviceMethods.archiveChat(archive);
                }
            }
        }
    }
    
    void setupDisappearingMessages(const std::string& chatId, int seconds) {
        nlohmann::json setting = {
            {"chatId", chatId},
            {"expiration", seconds}
        };
        client.serviceMethods.setDisappearingChat(setting);
    }
};
```

---

**Last Updated**: 2024
**SDK Version**: Latest from github.com/green-api/whatsapp-api-client-cpp
