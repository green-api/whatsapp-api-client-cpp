# Groups Methods Reference

All group methods are accessed via `client.groups.<method>()`.

## Important Constraints

- **Group creation rate limit**: Maximum 1 group per 5 minutes (anti-spam)
- **Group ID format**: `<creator_phone>-<timestamp>@g.us`
  - Example: `79876543210-1581234048@g.us`
- **Phone format in arrays**: Always use `<phone>@c.us` suffix for participants

---

## createGroup

**Purpose**: Create new WhatsApp group chat.

**Signature**:
```cpp
Response Groups::createGroup(const nlohmann::json& group);
```

**Required Parameters**:
- `groupName` (string): Group name (max 100 characters)
- `participants` (array of strings): Initial members in `<phone>@c.us` format

**Optional Parameters**:
- `picture` (string): Group profile picture (base64 or URL)

**Response**:
```json
{
  "chatId": "79876543210-1581234048@g.us"
}
```

**Rate Limit**: **Maximum 1 group per 5 minutes**

**Example**:
```cpp
#include <thread>
#include <chrono>

nlohmann::json groupData = {
    {"groupName", "Development Team"},
    {"participants", nlohmann::json::array({
        "79876543210@c.us",
        "79876543211@c.us",
        "79876543212@c.us"
    })}
};

Response resp = client.groups.createGroup(groupData);
if (resp.success) {
    std::string groupId = resp.body["chatId"];
    std::cout << "Group created: " << groupId << std::endl;
} else {
    std::cerr << "Error: " << resp.statusCode << std::endl;
}

// If creating multiple groups, wait 5 minutes between each
std::this_thread::sleep_for(std::chrono::minutes(5));
```

**Error Handling**:
- `400 Bad Request`: Invalid group name or participants
- `429 Too Many Requests`: Exceeded 1-group-per-5-minutes limit

**Official Docs**: https://green-api.com/en/docs/api/groups/CreateGroup/

---

## updateGroupName

**Purpose**: Change group chat name.

**Signature**:
```cpp
Response Groups::updateGroupName(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format
- `groupName` (string): New group name

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json update = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"groupName", "Marketing Team 2024"}
};

Response resp = client.groups.updateGroupName(update);
if (resp.success) {
    std::cout << "Group name updated" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/groups/UpdateGroupName/

---

## getGroupData

**Purpose**: Retrieve group information (members, creation date, admin, etc.).

**Signature**:
```cpp
Response Groups::getGroupData(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format

**Response**:
```json
{
  "groupId": "79876543210-1581234048@g.us",
  "groupName": "Development Team",
  "participants": [
    {
      "id": "79876543210@c.us",
      "isAdmin": true,
      "isSuperAdmin": true
    },
    {
      "id": "79876543211@c.us",
      "isAdmin": false,
      "isSuperAdmin": false
    }
  ],
  "creation": 1581234048
}
```

**Example**:
```cpp
nlohmann::json query = {
    {"groupId", "79876543210-1581234048@g.us"}
};

Response resp = client.groups.getGroupData(query);
if (resp.success) {
    std::string name = resp.body["groupName"];
    int creation = resp.body["creation"];
    std::cout << "Group: " << name << " (created: " << creation << ")" << std::endl;
    
    for (auto& member : resp.body["participants"]) {
        std::string memberId = member["id"];
        bool isAdmin = member["isAdmin"];
        std::cout << "  - " << memberId << (isAdmin ? " (admin)" : "") << std::endl;
    }
}
```

**Official Docs**: https://green-api.com/en/docs/api/groups/GetGroupData/

---

## addGroupParticipant

**Purpose**: Add member to group chat.

**Signature**:
```cpp
Response Groups::addGroupParticipant(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format
- `participantChatId` (string): New member in `<phone>@c.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json addMember = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"participantChatId", "79876543213@c.us"}
};

Response resp = client.groups.addGroupParticipant(addMember);
if (resp.success) {
    std::cout << "Member added" << std::endl;
}
```

**Constraints**:
- Member must have WhatsApp account
- Group must have at least 1 participant
- Only admins can add members

**Official Docs**: https://green-api.com/en/docs/api/groups/AddGroupParticipant/

---

## removeGroupParticipant

**Purpose**: Remove member from group chat.

**Signature**:
```cpp
Response Groups::removeGroupParticipant(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format
- `participantChatId` (string): Member to remove in `<phone>@c.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json removeMember = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"participantChatId", "79876543213@c.us"}
};

Response resp = client.groups.removeGroupParticipant(removeMember);
if (resp.success) {
    std::cout << "Member removed" << std::endl;
}
```

**Official Docs**: https://green-api.com/en/docs/api/groups/RemoveGroupParticipant/

---

## setGroupAdmin

**Purpose**: Grant admin rights to group member.

**Signature**:
```cpp
Response Groups::setGroupAdmin(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format
- `participantChatId` (string): Member to promote in `<phone>@c.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json makeAdmin = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"participantChatId", "79876543211@c.us"}
};

Response resp = client.groups.setGroupAdmin(makeAdmin);
if (resp.success) {
    std::cout << "Admin rights granted" << std::endl;
}
```

**Constraints**:
- Only group admins can grant admin rights
- Cannot make yourself admin if already admin

**Official Docs**: https://green-api.com/en/docs/api/groups/SetGroupAdmin/

---

## removeAdmin

**Purpose**: Revoke admin rights from group member.

**Signature**:
```cpp
Response Groups::removeAdmin(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format
- `participantChatId` (string): Member to demote in `<phone>@c.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json removeAdminRights = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"participantChatId", "79876543211@c.us"}
};

client.groups.removeAdmin(removeAdminRights);
```

**Official Docs**: https://green-api.com/en/docs/api/groups/RemoveAdmin/

---

## leaveGroup

**Purpose**: Leave group chat (current account).

**Signature**:
```cpp
Response Groups::leaveGroup(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format

**Response**:
```json
{
  "result": true
}
```

**Example**:
```cpp
nlohmann::json leave = {
    {"groupId", "79876543210-1581234048@g.us"}
};

client.groups.leaveGroup(leave);
```

**Effect**:
- Current account leaves the group
- Cannot receive messages from this group anymore
- Cannot rejoin without being added again

**Official Docs**: https://green-api.com/en/docs/api/groups/LeaveGroup/

---

## updateGroupSettings

**Purpose**: Modify group permissions (Beta).

**Signature**:
```cpp
Response Groups::updateGroupSettings(const nlohmann::json& group);
```

**Required Parameters**:
- `groupId` (string): Group ID in `@g.us` format

**Optional Parameters** (at least one required):
- `allowParticipantsEditGroupSettings` (boolean): Allow members to change name, picture, description, timer
- `allowParticipantsSendMessages` (boolean): Allow members to send messages

**Response**:
```json
{
  "result": true
}
```

**Example - Allow Members to Change Settings**:
```cpp
nlohmann::json settings = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"allowParticipantsEditGroupSettings", true}
};

client.groups.updateGroupSettings(settings);
```

**Example - Restrict Members from Messaging**:
```cpp
nlohmann::json settings = {
    {"groupId", "79876543210-1581234048@g.us"},
    {"allowParticipantsSendMessages", false}
};

client.groups.updateGroupSettings(settings);
```

**Official Docs**: https://green-api.com/en/docs/api/groups/UpdateGroupSettings/

---

## Group Management Example

```cpp
#include "greenapi.hpp"
#include <thread>
#include <chrono>

using namespace greenapi;

class GroupManager {
    GreenApi client;
    
public:
    GroupManager(const std::string& id, const std::string& token)
        : client("https://api.green-api.com", "https://media.green-api.com", id, token) {}
    
    std::string createTeamGroup(const std::vector<std::string>& members, 
                                const std::string& teamName) {
        nlohmann::json groupData = {
            {"groupName", teamName},
            {"participants", nlohmann::json::array()}
        };
        
        // Add all members with @c.us suffix
        for (const auto& member : members) {
            std::string memberId = member;
            if (memberId.find("@c.us") == std::string::npos) {
                memberId += "@c.us";
            }
            groupData["participants"].push_back(memberId);
        }
        
        Response resp = client.groups.createGroup(groupData);
        if (resp.success) {
            std::string groupId = resp.body["chatId"];
            std::cout << "Group created: " << groupId << std::endl;
            return groupId;
        }
        
        return "";
    }
    
    bool addMember(const std::string& groupId, const std::string& phone) {
        std::string memberId = phone;
        if (memberId.find("@c.us") == std::string::npos) {
            memberId += "@c.us";
        }
        
        nlohmann::json data = {
            {"groupId", groupId},
            {"participantChatId", memberId}
        };
        
        Response resp = client.groups.addGroupParticipant(data);
        return resp.success;
    }
    
    void listMembers(const std::string& groupId) {
        nlohmann::json query = {
            {"groupId", groupId}
        };
        
        Response resp = client.groups.getGroupData(query);
        if (resp.success) {
            for (auto& member : resp.body["participants"]) {
                std::cout << member["id"] << std::endl;
            }
        }
    }
    
    bool makeAdmin(const std::string& groupId, const std::string& phone) {
        std::string memberId = phone;
        if (memberId.find("@c.us") == std::string::npos) {
            memberId += "@c.us";
        }
        
        nlohmann::json data = {
            {"groupId", groupId},
            {"participantChatId", memberId}
        };
        
        Response resp = client.groups.setGroupAdmin(data);
        return resp.success;
    }
};

int main() {
    GroupManager mgr("1101000001", "token");
    
    // Create group (wait 5 min before creating another)
    std::vector<std::string> members = {"79876543210", "79876543211"};
    std::string groupId = mgr.createTeamGroup(members, "My Team");
    
    if (!groupId.empty()) {
        // Add another member
        std::this_thread::sleep_for(std::chrono::seconds(30));
        mgr.addMember(groupId, "79876543212");
        
        // Make someone admin
        std::this_thread::sleep_for(std::chrono::seconds(30));
        mgr.makeAdmin(groupId, "79876543211");
        
        // List members
        mgr.listMembers(groupId);
    }
    
    return 0;
}
```

---

## Group Chat ID Extraction

From incoming message, extract group ID:

```cpp
Response notif = client.receiving.receiveNotification(5);
if (notif.body.contains("receiptId") && notif.body["receiptId"] > 0) {
    std::string chatId = notif.body["body"]["senderData"]["chatId"];
    
    bool isGroup = chatId.find("@g.us") != std::string::npos;
    if (isGroup) {
        std::cout << "Message from group: " << chatId << std::endl;
        // Use chatId with group methods
    }
}
```

---

**Last Updated**: 2024
**SDK Version**: Latest from github.com/green-api/whatsapp-api-client-cpp
