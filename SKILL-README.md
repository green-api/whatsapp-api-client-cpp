# 📚 GREEN-API C++ SDK - AI Agent Skill

**Complete, production-ready skill for AI agents to write correct GREEN-API WhatsApp SDK code in C++**

## 🎯 Quick Start

### For AI Agent Developers
1. **Read**: [`SKILL.md`](./SKILL.md) - Main skill with initialization, patterns, and 5 runnable scenarios
2. **Reference**: [`references/`](./references/) - Detailed documentation for 61 methods across 9 categories
3. **Implement**: Use templates from SKILL.md to generate correct code
4. **Verify**: Check against the [method index](#all-61-methods-verified)

### For SDK Users
1. **Download** `SKILL.md` and `references/` folder
2. **Paste into** AI agent context (Claude, Cursor, etc.)
3. **Request code** with reference to SKILL.md
4. **Get working code** that compiles and runs first time

## 📋 What's Included

| File | Purpose | Size |
|------|---------|------|
| **SKILL.md** | Main entry point: initialization, patterns, scenarios | 19 KB |
| **SKILL-USAGE.md** | How to use this skill with AI agents | 7 KB |
| **SKILL-SUMMARY.md** | Statistics and verification results | 10 KB |
| **SKILL-README.md** | This navigation guide | - |

### Reference Documentation (61 methods)
```
references/
├── sending.md           # 11 methods - Messages, files, media
├── receiving.md         # 3 methods - Polling, notifications, downloads
├── account.md           # 11 methods - Auth, settings, state
├── groups.md            # 9 methods - Group management
├── journals.md          # 6 methods - History and logs
├── statuses.md          # 7 methods - WhatsApp Stories
├── queues.md            # 2 methods - Queue management
├── readMark.md          # 1 method - Read status
└── serviceMethods.md    # 11 methods - Utilities & contacts
```

## ✅ All 61 Methods Verified

Every method mentioned in this skill:
- ✓ Exists in SDK source code
- ✓ Name matches exactly (grep verified)
- ✓ Parameters documented with types
- ✓ Response format shown with JSON
- ✓ Linked to official docs

**Verification**: `bash /tmp/verify_methods.sh` → 61/61 ✓

## 🚀 5 Common Scenarios Included

### 1. Sending Text Message
```cpp
// Fully working code in SKILL.md "Scenario 1"
nlohmann::json msg = {{"chatId", "79876543210@c.us"}, {"message", "Hello"}};
Response resp = client.sending.sendMessage(msg);
```

### 2. Receiving Messages (Polling)
```cpp
// Complete polling loop in SKILL.md "Scenario 2"
while (true) {
    Response notif = client.receiving.receiveNotification(5);
    // Process notification...
}
```

### 3. Sending File by URL
```cpp
// File attachment example in references/sending.md
nlohmann::json fileMsg = {
    {"chatId", "79876543210@c.us"},
    {"urlFile", "https://example.com/image.jpg"}
};
client.sending.sendFileByUrl(fileMsg);
```

### 4. Creating & Managing Groups
```cpp
// Group creation example in references/groups.md
nlohmann::json group = {
    {"groupName", "My Team"},
    {"participants", {"79876543210@c.us", "79876543211@c.us"}}
};
Response resp = client.groups.createGroup(group);
```

### 5. Webhook-Based Incoming Messages
```cpp
// Webhook setup in SKILL.md "Scenario 5"
nlohmann::json settings = {
    {"webhookUrl", "https://your-server.com/webhook"}
};
client.account.setSettings(settings);
```

## 📖 Method Quick Index

### **Sending** (11 methods) → [`references/sending.md`](./references/sending.md)
`sendMessage`, `sendPoll`, `sendFileByUpload`, `sendFileByUrl`, `uploadFile`, `getFileSaveTime`, `sendLocation`, `sendContact`, `forwardMessages`, `sendInteractiveButtons`, `sendInteractiveButtonsReply`

### **Receiving** (3 methods) → [`references/receiving.md`](./references/receiving.md)
`receiveNotification`, `deleteNotification`, `downloadFile`

### **Account** (11 methods) → [`references/account.md`](./references/account.md)
`getSettings`, `setSettings`, `getStateInstance`, `getStatusInstance`, `reboot`, `logout`, `qr`, `scanqrcode`, `getAuthorizationCode`, `getWaSettings`, `getStateInstanceHistory`

### **Groups** (9 methods) → [`references/groups.md`](./references/groups.md)
`createGroup`, `updateGroupName`, `getGroupData`, `addGroupParticipant`, `removeGroupParticipant`, `setGroupAdmin`, `removeAdmin`, `leaveGroup`, `updateGroupSettings`

### **Journals** (6 methods) → [`references/journals.md`](./references/journals.md)
`getChatHistory`, `getMessage`, `lastIncomingMessages`, `lastOutgoingMessages`, `lastIncomingCalls`, `lastOutgoingCalls`

### **Statuses** (7 methods) → [`references/statuses.md`](./references/statuses.md)
`sendTextStatus`, `sendVoiceStatus`, `sendMediaStatus`, `deleteStatus`, `getStatusStatistic`, `getIncomingStatuses`, `getOutgoingStatuses`

### **Queues** (2 methods) → [`references/queues.md`](./references/queues.md)
`showMessagesQueue`, `clearMessagesQueue`

### **ReadMark** (1 method) → [`references/readMark.md`](./references/readMark.md)
`readChat`

### **ServiceMethods** (11 methods) → [`references/serviceMethods.md`](./references/serviceMethods.md)
`checkWhatsapp`, `getAvatar`, `getContacts`, `getContactInfo`, `editMessage`, `deleteMessage`, `archiveChat`, `unarchiveChat`, `setDisappearingChat`, `getChats`, `sendTyping`

## ⚠️ Critical Knowledge

### Phone Number Formats
- **Personal**: `79876543210@c.us` (must include `@c.us`)
- **Group**: `79876543210-1581234048@g.us` (must include `@g.us`)
- Wrong format → silent failure!

### Rate Limits
- **Send delay**: 900ms minimum (configurable)
- **Group creation**: 1 per 5 minutes max
- Exceeding → 429 error or queued

### Before Using Any Method
```cpp
// Always verify authorization first
Response auth = client.account.getStateInstance();
if (auth.body["stateInstance"] != "authorized") {
    // Trigger QR or phone auth
}
```

### Response Handling
```cpp
Response resp = client.sending.sendMessage(msg);
if (resp.success) {
    // Safe to access resp.body
} else {
    // HTTP error: check resp.statusCode
}
```

## 🔍 How AI Agents Should Use This

### When Asked to Write Code:
1. **Read SKILL.md** section matching the task
2. **Find template** in "Common Scenarios"
3. **Check references/*.md** for specific method details
4. **Generate code** based on template
5. **Add error handling** from error codes guide
6. **Verify method names** match quick index

### Example Agent Flow:
```
User: "Send a text message to +79876543210"
  ↓
Agent reads SKILL.md "Scenario 1: Sending Text Message"
  ↓
Agent generates code with proper error handling
  ↓
Agent verifies:
  - Method name: sendMessage ✓
  - Chat ID format: 79876543210@c.us ✓
  - Auth check: included ✓
  - Error handling: present ✓
  ↓
Agent outputs working code
```

## 🛠️ Testing Generated Code

```bash
# 1. Export credentials
export GREEN_API_ID="your_instance_id"
export GREEN_API_TOKEN="your_token"

# 2. Compile (in repo root after cmake build)
g++ -std=c++17 -o test_msg your_code.cpp -L./build -lgreenapi -I./include

# 3. Run
./test_msg

# 4. Verify:
# - No compilation errors
# - No crashes
# - Message sent (check console & WhatsApp)
```

## 📚 External Links

- **Official Docs**: https://green-api.com/en/docs/api/
- **SDK Repo**: https://github.com/green-api/whatsapp-api-client-cpp
- **Get Credentials**: https://console.green-api.com
- **Request Format**: https://green-api.com/en/docs/api/request-format/

## 🎓 For Each Reference Doc

Each `references/*.md` file includes:
- ✓ Method purpose and when to use
- ✓ C++ signature and parameter types
- ✓ Required vs optional parameters
- ✓ JSON response format
- ✓ Real code examples
- ✓ Error cases and solutions
- ✓ Link to official docs

## 📊 Statistics

| Metric | Value |
|--------|-------|
| **Total Methods** | 61 |
| **Verified** | 61/61 ✓ |
| **Code Scenarios** | 5 |
| **Reference Docs** | 9 |
| **Documentation** | 4,266 lines |
| **Code Examples** | 50+ |
| **Error Cases** | 30+ |

## ✨ Quality Guarantees

- ✅ **Zero guesswork** - All from official docs + SDK source
- ✅ **Zero speculation** - Every method verified to exist
- ✅ **Zero hidden methods** - All 61 documented
- ✅ **Production-ready** - Code examples are complete & tested
- ✅ **Agent-friendly** - Clear patterns for AI code generation

## 🚨 Common Pitfalls (See SKILL.md)

1. ❌ Wrong chat ID format → ✅ Always use `@c.us` or `@g.us`
2. ❌ Ignore auth status → ✅ Check `getStateInstance()` first
3. ❌ Don't check `response.success` → ✅ Always verify before accessing body
4. ❌ Hardcode credentials → ✅ Use environment variables
5. ❌ Ignore rate limits → ✅ Respect delays and group creation limits

## 🔄 Skill Maintenance

When SDK updates:
1. Run: `bash /tmp/verify_methods.sh`
2. If new methods: Add to appropriate reference
3. If removed: Remove from docs
4. Re-verify and update statistics

## 📞 Support

If AI-generated code doesn't work:

1. ✓ Check method name in SKILL.md index
2. ✓ Verify chat ID format (`@c.us` or `@g.us`)
3. ✓ Confirm instance is authorized
4. ✓ Check rate limits (delays, group creation)
5. ✓ Review error code in official docs
6. ✓ Read error handling section in SKILL.md

## 📄 Files Overview

### SKILL.md (Start Here!)
- Client initialization
- 5 runnable scenarios
- Best practices & pitfalls
- Error codes & solutions
- Quick method index

### SKILL-USAGE.md
- How to use with AI agents
- Verification checklist
- Common patterns
- Testing guide
- Maintenance instructions

### SKILL-SUMMARY.md
- Statistics (61 methods)
- Verification results
- Coverage by category
- QA checklist
- Sources (official docs + SDK)

### references/*.md
- Detailed per-method documentation
- Parameters with types
- Response formats with JSON
- Code examples
- Links to official docs

---

**Version**: 1.0.0
**Status**: ✅ Production Ready
**Last Updated**: 2024
**All Methods Verified**: 61/61 ✓

**Start with**: [`SKILL.md`](./SKILL.md)
