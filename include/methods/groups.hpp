#pragma once
#ifndef GREEN_API_GROUPS_H
#define GREEN_API_GROUPS_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class Groups
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Groups();

		Groups(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);


		/*
		* The method is aimed for creating a group chat. When creating a group, it is required to simulate human work. 
		* It is required to create a group no more often than 1 group every 5 minutes.
		* https://green-api.com/en/docs/api/groups/CreateGroup/
		* @param group - parameters of the created group
		*/
		Response createGroup(const nlohmann::json& group);

		/*
		* The method changes a group chat name.
		* https://green-api.com/en/docs/api/groups/UpdateGroupName/
		* @param group - parameters of the update group
		*/
		Response updateGroupName(const nlohmann::json& group);

		/*
		* The method gets group chat data.
		* https://green-api.com/en/docs/api/groups/GetGroupData/
		* @param group - parameters of the id group
		*/
		Response getGroupData(const nlohmann::json& group);

		/*
		* The method adds a participant to a group chat.
		* https://green-api.com/en/docs/api/groups/AddGroupParticipant/
		* @param group - parameters of participants added to the group
		*/
		Response addGroupParticipant(const nlohmann::json& group);

		/*
		* The method removes a participant from a group chat.
		* https://green-api.com/en/docs/api/groups/RemoveGroupParticipant/
		* @param group - parameters of participants removed from the group
		*/
		Response removeGroupParticipant(const nlohmann::json& group);

		/*
		* The method sets a group chat participant as an administrator.
		* https://green-api.com/en/docs/api/groups/SetGroupAdmin/
		* @param group - parameters of participant assigned by the administrator
		*/
		Response setGroupAdmin(const nlohmann::json& group);

		/*
		* The method removes a participant from group chat administration rights.
		* https://green-api.com/en/docs/api/groups/RemoveAdmin/
		* @param group - parameters of the participant whose administrator rights are taken away
		*/
		Response removeAdmin(const nlohmann::json& group);

		/*
		* The method sets a group picture.
		* https://green-api.com/en/docs/api/groups/SetGroupPicture/
		* @param group - parameters for setting the group picture
		*/
		Response setGroupPicture(const nlohmann::json file, const nlohmann::json group);

		/*
		* The method makes the current account user leave the group chat.
		* https://green-api.com/en/docs/api/groups/LeaveGroup/
		* @param group - group parameters for exit
		*/
		Response leaveGroup(const nlohmann::json& group);

	};

} // namespace greenapi

#endif // GREEN_API_GROUPS_H
