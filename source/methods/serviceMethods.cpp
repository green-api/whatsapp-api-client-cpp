#include "../../../whatsapp-api-client-cpp/include/methods/serviceMethods.hpp"

namespace greenapi
{
	ServiceMethods::ServiceMethods()
	{
		Logger::getInstance().log(std::string("Creating ServiceMethods class without parameters"), "error");
	};

	ServiceMethods::ServiceMethods(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating ServiceMethods class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response ServiceMethods::checkWhatsapp(const unsigned long long phoneNumber) {

		Response response;
		nlohmann::json requestMessage{ { "phoneNumber", 71234567890 } };

		// Checking the phoneNumber
		if (phoneNumber < 10) {
			response.bodyStr = "The phone number must be longer than 10 characters; to enter the phone number correctly, see the getSettings method";
			return response;
		}

		requestMessage["phoneNumber"] = phoneNumber;

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/checkWhatsapp/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::getAvatar(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" } };

		// Checking the chatId
		if (!message.contains("chatId")) {
			response.bodyStr = "Required chatId field are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getAvatar/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::getContacts() {

		Response response;

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getContacts/" + *(this->apiTokenInstance);
		Request req{ url };

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

	Response ServiceMethods::getContactInfo(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" } };

		// Checking the chatId
		if (!message.contains("chatId")) {
			response.bodyStr = "Required chatId field are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getContactInfo/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::deleteMessage(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" }, {"idMessage", ""} };

		// Checking the chatId and idMessage
		if (!message.contains("chatId") || !message.contains("idMessage")) {
			response.bodyStr = "Required chatId or idMessage fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (message["idMessage"].get<std::string>().size() < 10 || message["idMessage"].get<std::string>() == "") {
			response.bodyStr = "idMessage must be longer than 10 characters";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["idMessage"] = message["idMessage"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/deleteMessage/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::editMessage(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" }, {"idMessage", ""}, {"message", ""} };

		// Checking the chatId and idMessage
		if (!message.contains("chatId") || !message.contains("idMessage" || !message.contains("message"))) {
			response.bodyStr = "Required chatId, idMessage or message fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (message["idMessage"].get<std::string>().size() < 10 || message["idMessage"].get<std::string>() == "") {
			response.bodyStr = "idMessage must be longer than 10 characters";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["idMessage"] = message["idMessage"];
		requestMessage["message"] = message["message"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/editMessage/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::archiveChat(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" } };

		// Checking the chatId
		if (!message.contains("chatId")) {
			response.bodyStr = "Required chatId field are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/archiveChat/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::unarchiveChat(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" } };

		// Checking the chatId
		if (!message.contains("chatId")) {
			response.bodyStr = "Required chatId field are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/unarchiveChat/" + *(this->apiTokenInstance);
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

	Response ServiceMethods::setDisappearingChat(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId", "" }, {"ephemeralExpiration", 0} };

		// Checking the chatId and ephemeralExpiration
		if (!message.contains("chatId") || !message.contains("ephemeralExpiration")) {
			response.bodyStr = "Required chatId or ephemeralExpiration fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (message["ephemeralExpiration"].get<int>() < 0) {
			response.bodyStr = "ephemeralExpiration can only be greater than zero";
			return response;
		}
		if (message["ephemeralExpiration"].get<int>() > 7776000) {
			requestMessage["ephemeralExpiration"] = 7776000;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["ephemeralExpiration"] = message["ephemeralExpiration"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/setDisappearingChat/" + *(this->apiTokenInstance);
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