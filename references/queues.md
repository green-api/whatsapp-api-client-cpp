# Queues Methods Reference

All queue methods are accessed via `client.queues.<method>()`.

Message queue stores unsent messages when instance is offline. Automatically processes when back online.

---

## showMessagesQueue

**Purpose**: Get list of pending messages in send queue.

**Signature**:
```cpp
Response Queues::showMessagesQueue();
```

**Response**:
```json
{
  "data": [
    {
      "chatId": "79876543210@c.us",
      "message": "Hello",
      "idMessage": "3EB0C67FA8C3DAF78C40D0C3"
    }
  ]
}
```

**Example**:
```cpp
Response resp = client.queues.showMessagesQueue();
if (resp.success) {
    std::cout << "Queue size: " << resp.body["data"].size() << std::endl;
    for (auto& msg : resp.body["data"]) {
        std::cout << "To: " << msg["chatId"] << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/queues/ShowMessagesQueue/

---

## clearMessagesQueue

**Purpose**: Clear all pending messages from queue.

**Signature**:
```cpp
Response Queues::clearMessagesQueue();
```

**Response**:
```json
{
  "result": true
}
```

**Warning**: This deletes ALL unsent messages!

**Example**:
```cpp
Response resp = client.queues.clearMessagesQueue();
if (resp.success) {
    std::cout << "Queue cleared" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/queues/ClearMessagesQueue/

---

**Last Updated**: 2024
