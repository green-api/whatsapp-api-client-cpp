#include "../../../whatsapp-api-client-cpp/include/methods/journals.hpp"

namespace greenapi
{
	Journals::Journals()
	{
		Logger::getInstance().log(std::string("Creating Journals class without parameters"), "error");
	};

	Journals::Journals(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Journals class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Journals::getChatHistory(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" } };

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
		// Checking the count
		if (!message.contains("count")) {
			if (message["count"] < 0) { requestMessage["count"] = 100; }
			else if (message["count"] > 2147483647) { requestMessage["count"] = 2147483647; }
			else { requestMessage["count"] = message["count"]; }
		}

		requestMessage["chatId"] = message["chatId"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getChatHistory/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , message };

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

	Response Journals::getMessage(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" }, { "idMessage","" } };

		// Checking the chatId
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

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getMessage/" + *(this->apiTokenInstance);
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

	Response Journals::lastIncomingMessages(const unsigned int minutes) {

		Response response;
		unsigned int sendMinutes = 1440;

		if (minutes < 0 || minutes == 0) { sendMinutes = 1440; }

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/lastIncomingMessages/" + *(this->apiTokenInstance) + "?minutes=" + std::to_string(sendMinutes);
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

	Response Journals::lastOutgoingMessages(const unsigned int minutes) {

		Response response;
		unsigned int sendMinutes = 1440;

		if (minutes < 0 || minutes == 0) { sendMinutes = 1440; }

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/lastOutgoingMessages/" + *(this->apiTokenInstance) + "?minutes=" + std::to_string(sendMinutes);
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

}// namespace greenapi