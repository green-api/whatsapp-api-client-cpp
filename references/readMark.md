# ReadMark Methods Reference

All read mark methods are accessed via `client.readMark.<method>()`.

Control read status of messages in chats.

---

## readChat

**Purpose**: Mark all messages in a chat as read.

**Signature**:
```cpp
Response ReadMark::readChat(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Chat ID in `<phone>@c.us` or `<group>@g.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json mark = {
    {"chatId", "79876543210@c.us"}
};

Response resp = client.readMark.readChat(mark);
if (resp.success) {
    std::cout << "Chat marked as read" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/marks/ReadChat/

---

**Last Updated**: 2024
