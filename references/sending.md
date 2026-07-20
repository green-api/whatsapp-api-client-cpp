# Sending Methods Reference

All sending methods are accessed via `client.sending.<method>()`.

## sendMessage

**Purpose**: Send text message to personal or group chat.

**Signature**:
```cpp
Response Sending::sendMessage(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID (`<number>@c.us` or `<group>@g.us`)
- `message` (string): Message text (max 20,000 characters, UTF-8)

**Optional Parameters**:
- `quotedMessageId` (string): ID of message to quote (must be from same chat)
- `linkPreview` (boolean): Show link preview (default: true)
- `typePreview` (string): Preview size - `large` or `small`
- `customPreview` (object): Custom preview with title, description, link, image
- `typingTime` (integer): Show typing indicator for 1000-20000ms

**Response**:
```json
{
  "idMessage": "3EB0C67FA8C3DAF78C40D0C3_79876543210@c.us"
}
```

**Example**:
```cpp
nlohmann::json msg = {
    {"chatId", "79876543210@c.us"},
    {"message", "Hello! 👋"},
    {"linkPreview", false}
};
Response resp = client.sending.sendMessage(msg);
if (resp.success) {
    std::cout << "Sent: " << resp.body["idMessage"] << std::endl;
}
```

**Error Cases**:
- `400 Bad Request`: Missing chatId or message
- `401 Unauthorized`: Invalid API credentials
- `404 Not Found`: Chat not found (invalid chatId)
- `429 Too Many Requests`: Exceeded send delay (increase delay)

**Official Docs**: https://green-api.com/en/docs/api/sending/SendMessage/

---

## sendFileByUrl

**Purpose**: Send file (image, PDF, video, audio) by URL.

**Signature**:
```cpp
Response Sending::sendFileByUrl(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID
- `urlFile` (string): URL to file (must be publicly accessible)
- `fileName` (string): File name with extension

**Optional Parameters**:
- `caption` (string): Message caption (for media files)
- `mimeType` (string): MIME type (auto-detected if omitted)

**Supported Formats**:
- Images: `.jpg`, `.png`, `.gif`, `.webp` (max 16 MB)
- Documents: `.pdf`, `.doc`, `.xls`, `.ppt` (max 100 MB)
- Audio: `.mp3`, `.wav`, `.m4a`, `.aac` (max 100 MB)
- Video: `.mp4`, `.mov`, `.avi` (max 100 MB)

**Response**:
```json
{
  "idMessage": "3EB0C67FA8C3DAF78C40D0C3_79876543210@c.us"
}
```

**Example**:
```cpp
nlohmann::json fileMsg = {
    {"chatId", "79876543210@c.us"},
    {"urlFile", "https://example.com/document.pdf"},
    {"fileName", "report.pdf"},
    {"caption", "Annual report"}
};
Response resp = client.sending.sendFileByUrl(fileMsg);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendFileByUrl/

---

## sendFileByUpload

**Purpose**: Send file uploaded directly (form-data), with file stored temporarily.

**Signature**:
```cpp
Response Sending::sendFileByUpload(const nlohmann::json file, const nlohmann::json text);
```

**Parameters**:
- `file` (object): File data
  - `urlFile` (string): Path or URL to file being uploaded
- `text` (object): Message metadata
  - `chatId` (string): Recipient chat ID
  - `caption` (string): Optional caption

**Response**:
```json
{
  "idMessage": "3EB0C67FA8C3DAF78C40D0C3_79876543210@c.us"
}
```

**Example**:
```cpp
nlohmann::json fileData = {
    {"urlFile", "/path/to/local/file.pdf"}
};
nlohmann::json textData = {
    {"chatId", "79876543210@c.us"},
    {"caption", "Here is the file"}
};
Response resp = client.sending.sendFileByUpload(fileData, textData);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendFileByUpload/

---

## sendLocation

**Purpose**: Send location/map marker.

**Signature**:
```cpp
Response Sending::sendLocation(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID
- `latitude` (number): Latitude coordinate
- `longitude` (number): Longitude coordinate

**Optional Parameters**:
- `nameLocation` (string): Location name/label

**Example**:
```cpp
nlohmann::json location = {
    {"chatId", "79876543210@c.us"},
    {"latitude", 55.7558},
    {"longitude", 37.6173},
    {"nameLocation", "Red Square, Moscow"}
};
client.sending.sendLocation(location);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendLocation/

---

## sendContact

**Purpose**: Send contact card.

**Signature**:
```cpp
Response Sending::sendContact(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID
- `contactsBase64` (string): vCard data in Base64 format OR
- `vcard` (string): vCard format string

**vCard Example** (RFC 2426):
```
BEGIN:VCARD
VERSION:3.0
FN:John Doe
TEL:+79876543210
EMAIL:john@example.com
END:VCARD
```

**Example**:
```cpp
std::string vcard = "BEGIN:VCARD\nVERSION:3.0\nFN:John Doe\nTEL:+79876543210\nEND:VCARD";
nlohmann::json contact = {
    {"chatId", "79876543210@c.us"},
    {"vcard", vcard}
};
client.sending.sendContact(contact);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendContact/

---

## sendPoll

**Purpose**: Send interactive poll with voting options.

**Signature**:
```cpp
Response Sending::sendPoll(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID
- `textMessage` (string): Poll question
- `options` (array of strings): Poll options (2-10 options)

**Optional Parameters**:
- `multipleAnswers` (boolean): Allow multiple selections (default: false)

**Example**:
```cpp
nlohmann::json poll = {
    {"chatId", "79876543210@c.us"},
    {"textMessage", "What's your favorite language?"},
    {"options", {"C++", "Python", "Go", "Rust"}},
    {"multipleAnswers", false}
};
client.sending.sendPoll(poll);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendPoll/

---

## sendInteractiveButtons

**Purpose**: Send message with clickable button options (copy, call, URL).

**Signature**:
```cpp
Response Sending::sendInteractiveButtons(const nlohmann::json message);
```

**Required Parameters**:
- `chatId` (string): Recipient chat ID
- `body` (object): Message body
  - `text` (string): Main text message (required)
- `buttons` (array): Button definitions (max 3 buttons)
  - `type` (string): `"copy"`, `"call"`, or `"url"`
  - `buttonId` (string): Unique button ID
  - `buttonText` (string): Button label (max 25 chars)
  - `copyCode` (string, for type="copy"): Text to copy
  - `phoneNumber` (string, for type="call"): Phone to dial
  - `url` (string, for type="url"): URL to open

**Optional Parameters**:
- `header` (object): Header section (optional)
- `footer` (object): Footer section (optional)

**Example**:
```cpp
nlohmann::json msg = {
    {"chatId", "79876543210@c.us"},
    {"body", {{"text", "Click a button:"}}},
    {"buttons", nlohmann::json::array({
        {
            {"type", "url"},
            {"buttonId", "btn1"},
            {"buttonText", "Visit Website"},
            {"url", "https://green-api.com"}
        },
        {
            {"type", "call"},
            {"buttonId", "btn2"},
            {"buttonText", "Call Support"},
            {"phoneNumber", "79876543210"}
        },
        {
            {"type", "copy"},
            {"buttonId", "btn3"},
            {"buttonText", "Copy Code"},
            {"copyCode", "ABC123XYZ"}
        }
    })}
};
client.sending.sendInteractiveButtons(msg);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendInteractiveButtons/

---

## forwardMessages

**Purpose**: Forward messages from one chat to another.

**Signature**:
```cpp
Response Sending::forwardMessages(const nlohmann::json message);
```

**Required Parameters**:
- `chatIdFrom` (string): Source chat ID (where message was sent)
- `chatIdTo` (string): Destination chat ID
- `messagesId` (array of strings): Message IDs to forward

**Example**:
```cpp
nlohmann::json forward = {
    {"chatIdFrom", "79876543210@c.us"},
    {"chatIdTo", "79876543211@c.us"},
    {"messagesId", {"3EB0C67FA8C3DAF78C40D0C3_79876543210@c.us"}}
};
client.sending.forwardMessages(forward);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/ForwardMessages/

---

## uploadFile

**Purpose**: Upload file to GREEN-API storage for later sending with sendFileByUrl.

**Signature**:
```cpp
Response Sending::uploadFile(const nlohmann::json file, 
                             const nlohmann::json header = "");
```

**Parameters**:
- `file` (object): File data
  - `urlFile` (string): Local file path or URL
- `header` (object, optional): HTTP headers

**Response**:
```json
{
  "urlFile": "https://media.green-api.com/file123abc"
}
```

**Usage Flow**:
1. Upload file: `uploadFile()` → get URL
2. Send via URL: `sendFileByUrl()` with returned URL

**Example**:
```cpp
nlohmann::json fileData = {
    {"urlFile", "/home/user/documents/report.pdf"}
};
Response uploadResp = client.sending.uploadFile(fileData);
if (uploadResp.success) {
    std::string uploadedUrl = uploadResp.body["urlFile"];
    
    // Now send via URL
    nlohmann::json sendMsg = {
        {"chatId", "79876543210@c.us"},
        {"urlFile", uploadedUrl},
        {"fileName", "report.pdf"}
    };
    client.sending.sendFileByUrl(sendMsg);
}
```

**Official Docs**: https://green-api.com/en/docs/api/sending/UploadFile/

---

## getFileSaveTime

**Purpose**: Check how long file will be stored in GREEN-API cloud.

**Signature**:
```cpp
Response Sending::getFileSaveTime(const std::string url);
```

**Parameters**:
- `url` (string): File URL from uploadFile() or received message

**Response**:
```json
{
  "expireAt": "2024-01-15T12:30:45Z"
}
```

**Example**:
```cpp
Response resp = client.sending.getFileSaveTime("https://media.green-api.com/file123");
if (resp.success) {
    std::string expiry = resp.body["expireAt"];
    std::cout << "File expires at: " << expiry << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/sending/GetFileSaveTime/

---

## sendInteractiveButtonsReply

**Purpose**: Send message with reply buttons (Beta - text buttons for single response).

**Signature**:
```cpp
Response Sending::sendInteractiveButtonsReply(const nlohmann::json message);
```

**Parameters**:
- `chatId` (string): Recipient chat ID
- `body` (object):
  - `text` (string): Message text
- `buttons` (array, max 3):
  - `buttonId` (string): Unique button ID
  - `buttonText` (string): Button label (max 25 chars)
- `header` (object, optional)
- `footer` (object, optional)

**Example**:
```cpp
nlohmann::json msg = {
    {"chatId", "79876543210@c.us"},
    {"body", {{"text", "Select one:"}}},
    {"buttons", nlohmann::json::array({
        {
            {"buttonId", "opt1"},
            {"buttonText", "Option 1"}
        },
        {
            {"buttonId", "opt2"},
            {"buttonText", "Option 2"}
        }
    })}
};
client.sending.sendInteractiveButtonsReply(msg);
```

**Official Docs**: https://green-api.com/en/docs/api/sending/SendInteractiveButtonsReply/

---

## Send Delay Configuration

All sends are rate-limited. Configure delay via account settings:

```cpp
nlohmann::json settings = {
    {"delaySendMessagesMilliseconds", 900}  // 900ms minimum
};
client.account.setSettings(settings);
```

Queue status:
```cpp
Response queue = client.queues.showMessagesQueue();
// Shows pending messages to be sent
```

Clear queue:
```cpp
client.queues.clearMessagesQueue();
```

---

**Last Updated**: 2024
**SDK Version**: Latest from github.com/green-api/whatsapp-api-client-cpp
