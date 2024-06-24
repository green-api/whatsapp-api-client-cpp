#include "../../../whatsapp-api-client-cpp/include/methods/groups.hpp"

namespace greenapi
{
	Groups::Groups()
	{
		Logger::getInstance().log(std::string("Creating Groups class without parameters"), "error");
	};

	Groups::Groups(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Groups class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Groups::createGroup(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupName", "" } };

		// Checking the groupName and chatIds
		if (!group.contains("groupName") || !group.contains("chatIds")) {
			response.bodyStr = "Required groupName or chatIds fields are missing";
			return response;
		}
		if (group["groupName"].get<std::string>().size() < 1) {
			response.bodyStr = "groupName is not correct, the group name must contain more than 1 character";
			return response;
		}
		if (!group["chatIds"].is_array()) {
			response.bodyStr = "The key 'chatIds' does not exist or is not an array.";
			return response;
		}
		if (group["chatIds"].size() < 1) {
			response.bodyStr = "The number of participants to create a group must be more than 1";
			return response;
		}

		requestMessage["groupName"] = group["groupName"];
		requestMessage["chatIds"] = group["chatIds"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/createGroup/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::updateGroupName(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupName", "" }, { "groupId", "" } };

		// Checking the groupName and groupId
		if (!group.contains("groupName") || !group.contains("groupId")) {
			response.bodyStr = "Required groupName or groupId fields are missing";
			return response;
		}
		if (group["groupName"].get<std::string>().size() < 1) {
			response.bodyStr = "groupName is not correct, the group name must contain more than 1 character";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["groupName"] = group["groupName"];
		requestMessage["groupId"] = group["groupId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/updateGroupName/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::getGroupData(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" } };

		// Checking the groupName and groupId
		if ( !group.contains("groupId")) {
			response.bodyStr = "Required groupId field are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getGroupData/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::addGroupParticipant(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" }, { "participantChatId", "" } };

		// Checking the participantChatId and groupId
		if (!group.contains("groupId") || !group.contains("participantChatId")) {
			response.bodyStr = "Required participantChatId or groupId fields are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (group["participantChatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the participantChatId variable";
			return response;
		}
		if (group["participantChatId"].get<std::string>().size() < 11) {
			response.bodyStr = "participantChatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];
		requestMessage["participantChatId"] = group["participantChatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/addGroupParticipant/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::removeGroupParticipant(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" }, { "participantChatId", "" } };

		// Checking the participantChatId and groupId
		if (!group.contains("groupId") || !group.contains("participantChatId")) {
			response.bodyStr = "Required participantChatId or groupId fields are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (group["participantChatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the participantChatId variable";
			return response;
		}
		if (group["participantChatId"].get<std::string>().size() < 11) {
			response.bodyStr = "participantChatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];
		requestMessage["participantChatId"] = group["participantChatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/removeGroupParticipant/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::setGroupAdmin(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" }, { "participantChatId", "" } };

		// Checking the participantChatId and groupId
		if (!group.contains("groupId") || !group.contains("participantChatId")) {
			response.bodyStr = "Required participantChatId or groupId fields are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (group["participantChatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the participantChatId variable";
			return response;
		}
		if (group["participantChatId"].get<std::string>().size() < 11) {
			response.bodyStr = "participantChatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];
		requestMessage["participantChatId"] = group["participantChatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/setGroupAdmin/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::removeAdmin(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" }, { "participantChatId", "" } };

		// Checking the participantChatId and groupId
		if (!group.contains("groupId") || !group.contains("participantChatId")) {
			response.bodyStr = "Required participantChatId or groupId fields are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (group["participantChatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the participantChatId variable";
			return response;
		}
		if (group["participantChatId"].get<std::string>().size() < 11) {
			response.bodyStr = "participantChatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];
		requestMessage["participantChatId"] = group["participantChatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/removeAdmin/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::setGroupPicture(const nlohmann::json file, const nlohmann::json group) {

		Response response;
		nlohmann::json body{ { "groupId","" } };
		nlohmann::json bodyFile{ { "file","" } };

		// Checking the groupId and file fields
		if (!group.contains("groupId") || !file.contains("file")) {
			response.bodyStr = "Required groupId or file fields are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		bodyFile["file"] = file["file"].get<std::string>();

		body["groupId"] = group["groupId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/setGroupPicture/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , body, bodyFile, "data" };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Groups::leaveGroup(const nlohmann::json& group) {

		Response response;
		nlohmann::json requestMessage{ { "groupId", "" } };

		// Checking the groupId
		if (!group.contains("groupId")) {
			response.bodyStr = "Required  groupId field are missing";
			return response;
		}
		if (group["groupId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the groupId variable";
			return response;
		}
		if (group["groupId"].get<std::string>().size() < 11) {
			response.bodyStr = "groupId is not correct, the required chatId format for group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["groupId"] = group["groupId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/leaveGroup/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

}// namespace greenapi