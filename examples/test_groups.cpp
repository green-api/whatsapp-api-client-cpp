#include "greenapi.hpp"

/*
* Examples of groups methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/groups/
*/
int main_groups() {

	/*
	* Examples of groups methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* The method is aimed for creating a group chat. When creating a group, it is required to simulate human work.
	* It is required to create a group no more often than 1 group every 5 minutes.
	* https://green-api.com/en/docs/api/groups/CreateGroup/
	* @param group - parameters of the created group
	*/

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
	}
	else {
		std::cout << "\tcreated: " << createGroup.bodyJson["created"] << "\n" << std::endl;
		std::cout << "\tchatId: " << createGroup.bodyJson["chatId"] << "\n" << std::endl;
		std::cout << "\tgroupInviteLink: " << createGroup.bodyJson["groupInviteLink"] << "\n" << std::endl;
	}

	/*
	* The method changes a group chat name.
	* https://green-api.com/en/docs/api/groups/UpdateGroupName/
	* @param group - parameters of the update group
	*/

	nlohmann::json groupUpdateGroupName{
		{"groupId","120363294532719629@g.us"},
		{"groupName","GREEN API rename group"},
	};

	greenapi::Response updateGroupName = instance1101000001.groups.updateGroupName(groupUpdateGroupName);

	if (updateGroupName.error) {
		std::cout << "updateGroupName error: {status code: " << updateGroupName.status_code << ", request time: " << updateGroupName.total_time << ", body: " << updateGroupName.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tupdateGroupName: " << updateGroupName.bodyJson["updateGroupName"] << "\n" << std::endl;
	}

	/*
	* The method gets group chat data.
	* https://green-api.com/en/docs/api/groups/GetGroupData/
	* @param group - parameters of the id group
	*/

	nlohmann::json groupGetGroupData{
	{"groupId","120363294532719629@g.us"}
	};

	greenapi::Response getGroupData = instance1101000001.groups.getGroupData(groupGetGroupData);

	if (getGroupData.error) {
		std::cout << "getGroupData error: {status code: " << getGroupData.status_code << ", request time: " << getGroupData.total_time << ", body: " << getGroupData.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tgroupData: " << getGroupData.bodyStr << "\n" << std::endl;
		std::cout << "\tgroupInviteLink: " << getGroupData.bodyJson["groupInviteLink"] << "\n" << std::endl;
	}

	/*
	* The method removes a participant from a group chat.
	* https://green-api.com/en/docs/api/groups/RemoveGroupParticipant/
	* @param group - parameters of participants removed from the group
	*/

	nlohmann::json groupRemoveGroupParticipant{
	{"groupId","120363294532719629@g.us"},
	{"participantChatId","71234567890@c.us"}
	};

	greenapi::Response removeGroupParticipant = instance1101000001.groups.removeGroupParticipant(groupRemoveGroupParticipant);

	if (removeGroupParticipant.error) {
		std::cout << "removeGroupParticipant error: {status code: " << removeGroupParticipant.status_code << ", request time: " << removeGroupParticipant.total_time << ", body: " << removeGroupParticipant.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tremoveParticipant: " << removeGroupParticipant.bodyJson["removeParticipant"] << "\n" << std::endl;
	}

	/*
	* The method adds a participant to a group chat.
	* https://green-api.com/en/docs/api/groups/AddGroupParticipant/
	* @param group - parameters of participants added to the group
	*/

	nlohmann::json groupAddGroupParticipant{
	{"groupId","120363294532719629@g.us"},
	{"participantChatId","71234567890@c.us"}
	};

	greenapi::Response addGroupParticipant = instance1101000001.groups.addGroupParticipant(groupAddGroupParticipant);

	if (addGroupParticipant.error) {
		std::cout << "addGroupParticipant error: {status code: " << addGroupParticipant.status_code << ", request time: " << addGroupParticipant.total_time << ", body: " << addGroupParticipant.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\taddParticipant: " << addGroupParticipant.bodyJson["addParticipant"] << "\n" << std::endl;
	}

	/*
	* The method sets a group chat participant as an administrator.
	* https://green-api.com/en/docs/api/groups/SetGroupAdmin/
	* @param group - parameters of participant assigned by the administrator
	*/

	nlohmann::json groupSetGroupAdmin{
	{"groupId","120363294532719629@g.us"},
	{"participantChatId","71234567890@c.us"}
	};

	greenapi::Response setGroupAdmin = instance1101000001.groups.setGroupAdmin(groupSetGroupAdmin);

	if (setGroupAdmin.error) {
		std::cout << "setGroupAdmin error: {status code: " << setGroupAdmin.status_code << ", request time: " << setGroupAdmin.total_time << ", body: " << setGroupAdmin.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tsetGroupAdmin: " << setGroupAdmin.bodyJson["setGroupAdmin"] << "\n" << std::endl;
	}

	/*
	* The method removes a participant from group chat administration rights.
	* https://green-api.com/en/docs/api/groups/RemoveAdmin/
	* @param group - parameters of the participant whose administrator rights are taken away
	*/

	nlohmann::json groupRemoveAdmin{
	{"groupId","120363294532719629@g.us"},
	{"participantChatId","71234567890@c.us"}
	};

	greenapi::Response removeAdmin = instance1101000001.groups.removeAdmin(groupRemoveAdmin);

	if (removeAdmin.error) {
		std::cout << "removeAdmin error: {status code: " << removeAdmin.status_code << ", request time: " << removeAdmin.total_time << ", body: " << removeAdmin.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tremoveAdmin: " << removeAdmin.bodyJson["removeAdmin"] << "\n" << std::endl;
	}

	/*
	* The method sets a group picture.
	* https://green-api.com/en/docs/api/groups/SetGroupPicture/
	* @param group - parameters for setting the group picture
	*/

	nlohmann::json file{
		{ "file","C:/1.jpg" }
	};
	nlohmann::json group{
		{"groupId","120363294532719629@g.us"}
	};

	greenapi::Response setGroupPicture = instance1101000001.groups.setGroupPicture(file, group);

	if (setGroupPicture.error) {
		std::cout << "setGroupPicture error: {status code: " << setGroupPicture.status_code << ", request time: " << setGroupPicture.total_time << ", body: " << setGroupPicture.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tsetGroupPicture: " << setGroupPicture.bodyJson["setGroupPicture"] << "\n" << std::endl;
		std::cout << "\turlAvatar: " << setGroupPicture.bodyJson["urlAvatar"] << "\n" << std::endl;
		std::cout << "\treason: " << setGroupPicture.bodyJson["reason"] << "\n" << std::endl;
	}

	/*
	* The method makes the current account user leave the group chat.
	* https://green-api.com/en/docs/api/groups/LeaveGroup/
	* @param group - group parameters for exit
	*/

	nlohmann::json groupLeaveGroup{
		{"groupId","120363294532719629@g.us"}
	};

	greenapi::Response leaveGroup = instance1101000001.groups.leaveGroup(groupLeaveGroup);

	if (leaveGroup.error) {
		std::cout << "leaveGroup error: {status code: " << leaveGroup.status_code << ", request time: " << leaveGroup.total_time << ", body: " << leaveGroup.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tleaveGroup: " << leaveGroup.bodyStr << "\n" << std::endl;
	}

	return 0;
}