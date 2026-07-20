# Statuses Methods Reference

All status methods are accessed via `client.statuses.<method>()`.

WhatsApp Statuses (Stories) are temporary 24-hour media posts visible to your contacts.

---

## sendTextStatus

**Purpose**: Post text-only status.

**Signature**:
```cpp
Response Statuses::sendTextStatus(const nlohmann::json& status);
```

**Required Parameters**:
- `text` (string): Status text

**Optional Parameters**:
- `backgroundColor` (string): Hex color code
- `font` (integer): Font style

**Response**:
```json
{
  "idMessage": "3EB0C67FA8C3DAF78C40D0C3"
}
```

**Example**:
```cpp
nlohmann::json status = {
    {"text", "Working on new features!"},
    {"backgroundColor", "#FF5733"}
};

client.statuses.sendTextStatus(status);
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/SendTextStatus/

---

## sendVoiceStatus

**Purpose**: Post audio/voice status.

**Signature**:
```cpp
Response Statuses::sendVoiceStatus(const nlohmann::json& status);
```

**Required Parameters**:
- `urlFile` (string): Audio file URL

**Optional Parameters**:
- `caption` (string): Optional caption

**Example**:
```cpp
nlohmann::json status = {
    {"urlFile", "https://example.com/audio.mp3"}
};

client.statuses.sendVoiceStatus(status);
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/SendVoiceStatus/

---

## sendMediaStatus

**Purpose**: Post image or video status.

**Signature**:
```cpp
Response Statuses::sendMediaStatus(const nlohmann::json& status);
```

**Required Parameters**:
- `urlFile` (string): Image or video URL

**Optional Parameters**:
- `caption` (string): Status caption

**Supported Formats**:
- Images: `.jpg`, `.png`, `.webp`
- Videos: `.mp4`, `.mov`

**Example**:
```cpp
nlohmann::json status = {
    {"urlFile", "https://example.com/photo.jpg"},
    {"caption", "Beautiful sunset! 🌅"}
};

client.statuses.sendMediaStatus(status);
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/SendMediaStatus/

---

## deleteStatus

**Purpose**: Delete published status.

**Signature**:
```cpp
Response Statuses::deleteStatus(const nlohmann::json& status);
```

**Required Parameters**:
- `idMessage` (string): Status message ID

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json deleteReq = {
    {"idMessage", "3EB0C67FA8C3DAF78C40D0C3"}
};

client.statuses.deleteStatus(deleteReq);
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/DeleteStatus/

---

## getStatusStatistic

**Purpose**: Get views/interactions for published status.

**Signature**:
```cpp
Response Statuses::getStatusStatistic(std::string idMessage);
```

**Parameters**:
- `idMessage` (string): Status message ID

**Response**:
```json
{
  "sent": 150,
  "delivered": 148,
  "read": 125
}
```

**Example**:
```cpp
Response resp = client.statuses.getStatusStatistic("3EB0C67FA8C3DAF78C40D0C3");
if (resp.success) {
    int read = resp.body["read"];
    int sent = resp.body["sent"];
    std::cout << "Status read by " << read << "/" << sent << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/GetStatusStatistic/

---

## getIncomingStatuses

**Purpose**: Get statuses from contacts (default: 24 hours).

**Signature**:
```cpp
Response Statuses::getIncomingStatuses(const unsigned int minutes = 1440);
```

**Parameters**:
- `minutes` (integer, default 1440): Time window in minutes

**Response**:
```json
{
  "statuses": [
    {
      "idMessage": "...",
      "timestamp": 1234567890,
      "senderName": "John",
      "text": "Hello everyone!",
      "media": {
        "type": "image",
        "url": "https://..."
      }
    }
  ]
}
```

**Example**:
```cpp
Response resp = client.statuses.getIncomingStatuses();
for (auto& status : resp.body["statuses"]) {
    std::cout << status["senderName"] << ": " << status["text"] << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/GetIncomingStatuses/

---

## getOutgoingStatuses

**Purpose**: Get statuses posted by this account.

**Signature**:
```cpp
Response Statuses::getOutgoingStatuses(const unsigned int minutes = 1440);
```

**Parameters**:
- `minutes` (integer, default 1440): Time window in minutes

**Example**:
```cpp
// Last 24 hours
Response resp = client.statuses.getOutgoingStatuses();

// Last 12 hours
Response resp = client.statuses.getOutgoingStatuses(720);
```

**Official Docs**: https://green-api.com/en/docs/api/statuses/GetOutgoingStatuses/

---

**Last Updated**: 2024
