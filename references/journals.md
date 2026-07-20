# Journals Methods Reference

All journal methods are accessed via `client.journals.<method>()`.

These methods retrieve message history, call logs, and archived conversations.

## getChatHistory

**Purpose**: Get message history from a specific chat.

**Signature**:
```cpp
Response Journals::getChatHistory(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID in `<phone>@c.us` or `<group>@g.us` format

**Optional Parameters**:
- `count` (integer): Number of messages to retrieve (default 100)
- `lastMessageNumber` (integer): Start from message number (for pagination)

**Response**:
```json
{
  "messages": [
    {
      "idMessage": "3EB0C67FA8C3DAF78C40D0C3",
      "timestamp": 1234567890,
      "type": "textMessage",
      "textMessage": "Hello",
      "fromMe": true,
      "chatId": "79876543210@c.us"
    }
  ]
}
```

**Example**:
```cpp
nlohmann::json query = {
    {"chatId", "79876543210@c.us"},
    {"count", 50}
};

Response resp = client.journals.getChatHistory(query);
if (resp.success) {
    for (auto& msg : resp.body["messages"]) {
        std::cout << msg["textMessage"] << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/journals/GetChatHistory/

---

## getMessage

**Purpose**: Get specific message details by ID.

**Signature**:
```cpp
Response Journals::getMessage(const nlohmann::json& message);
```

**Required Parameters**:
- `chatId` (string): Chat ID
- `idMessage` (string): Message ID

**Response**:
```json
{
  "message": {
    "idMessage": "3EB0C67FA8C3DAF78C40D0C3",
    "timestamp": 1234567890,
    "type": "textMessage",
    "textMessage": "Hello"
  }
}
```

**Example**:
```cpp
nlohmann::json query = {
    {"chatId", "79876543210@c.us"},
    {"idMessage", "3EB0C67FA8C3DAF78C40D0C3"}
};

Response resp = client.journals.getMessage(query);
```

**Official Docs**: https://green-api.com/en/docs/api/journals/GetMessage/

---

## lastIncomingMessages

**Purpose**: Get last incoming messages (default: 24 hours).

**Signature**:
```cpp
Response Journals::lastIncomingMessages(const unsigned int minutes = 1440);
```

**Parameters**:
- `minutes` (integer, default 1440 = 24 hours): Time window in minutes

**Response**:
```json
{
  "messages": [
    {
      "idMessage": "...",
      "timestamp": 1234567890,
      "type": "textMessage",
      "textMessage": "Hi there!",
      "senderName": "John",
      "chatId": "79876543210@c.us"
    }
  ]
}
```

**Example**:
```cpp
// Last 24 hours (default)
Response resp = client.journals.lastIncomingMessages();

// Last 12 hours
Response resp = client.journals.lastIncomingMessages(720);

// Last 1 hour
Response resp = client.journals.lastIncomingMessages(60);
```

**Official Docs**: https://green-api.com/en/docs/api/journals/LastIncomingMessages/

---

## lastOutgoingMessages

**Purpose**: Get last outgoing messages sent from this account.

**Signature**:
```cpp
Response Journals::lastOutgoingMessages(const unsigned int minutes = 1440);
```

**Parameters**:
- `minutes` (integer, default 1440): Time window in minutes

**Response**: Similar to `lastIncomingMessages()`

**Example**:
```cpp
// Messages sent in last 24 hours
Response resp = client.journals.lastOutgoingMessages();

for (auto& msg : resp.body["messages"]) {
    std::cout << "Sent to " << msg["chatId"] << ": " << msg["textMessage"] << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/journals/LastOutgoingMessages/

---

## lastIncomingCalls

**Purpose**: Get incoming calls history.

**Signature**:
```cpp
Response Journals::lastIncomingCalls(const unsigned int minutes = 1440);
```

**Parameters**:
- `minutes` (integer, default 1440): Time window in minutes

**Requires**: Enable `incomingCallWebhook` in settings

**Response**:
```json
{
  "calls": [
    {
      "idCall": "...",
      "timestamp": 1234567890,
      "callerId": "79876543210@c.us",
      "callType": "voice",
      "duration": 120
    }
  ]
}
```

**Official Docs**: https://green-api.com/en/docs/api/journals/LastIncomingCalls/

---

## lastOutgoingCalls

**Purpose**: Get outgoing calls history.

**Signature**:
```cpp
Response Journals::lastOutgoingCalls(const unsigned int minutes = 1440);
```

**Requires**: Enable `outgoingCallWebhook` in settings

**Official Docs**: https://green-api.com/en/docs/api/journals/LastOutgoingCalls/

---

**Last Updated**: 2024
