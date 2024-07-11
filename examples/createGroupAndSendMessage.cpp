#include "../include/greenapi.hpp"

/*
* Example of create group and sending message
*/
int main() {

    greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

    nlohmann::json groupCreateGroup{
        {"groupName","GREEN API test group"},
        {"chatIds", {
            "71234567890@c.us",
            "71234567891@c.us"
            }
        }
    };

    greenapi::Response createGroup = instance1101000001.groups.createGroup(groupCreateGroup);

    if (createGroup.error) {
        std::cout << "createGroup error: {status code: " << createGroup.status_code << ", request time: " << createGroup.total_time << ", body: " << createGroup.bodyStr << "}" << "\n" << std::endl;
        return 1;
    }
    else {
        std::cout << "\tcreated: " << createGroup.bodyJson["created"] << "\n" << std::endl;
        std::cout << "\tchatId: " << createGroup.bodyJson["chatId"] << "\n" << std::endl;
        std::cout << "\tgroupInviteLink: " << createGroup.bodyJson["groupInviteLink"] << "\n" << std::endl;
    }

    nlohmann::json sendMessageJson{
        { "chatId", createGroup.bodyJson["chatId"] },
        { "message","I use GREEN-API to send this message to you!" }
    };
    greenapi::Response sendMessage = instance1101000001.sending.sendMessage(sendMessageJson);

    if (sendMessage.error) {
        std::cout << "sendMessage error: {status code: " << sendMessage.status_code << ", request time: " << sendMessage.total_time << ", body: " << sendMessage.bodyStr << "}" << "\n" << std::endl;
    }
    else {
        std::cout << "\tidMessage: " << sendMessage.bodyJson["idMessage"] << "\n" << std::endl;
    }

    return 0;
}
