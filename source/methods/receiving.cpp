#include "../../../whatsapp-api-client-cpp/include/methods/receiving.hpp"

namespace greenapi
{
	Receiving::Receiving()
	{
		Logger::getInstance().log(std::string("Creating Receiving class without parameters"), "error");
	};

	Receiving::Receiving(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Receiving class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Receiving::receiveNotification(const unsigned int receiveTimeout) {

		Response response;
		unsigned int sendReceiveTimeout = 5;

		if (receiveTimeout < 5) { sendReceiveTimeout = 5; }
		if (receiveTimeout > 60) { sendReceiveTimeout = 60; }

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/receiveNotification/" + *(this->apiTokenInstance) + "?" + std::to_string(sendReceiveTimeout);
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

	Response Receiving::deleteNotification(const unsigned int receiptId) {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/deleteNotification/" + *(this->apiTokenInstance) + "/" + std::to_string(receiptId);
		Request req{ url, "HTTP", "DELETE" };

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
	};

	Response Receiving::downloadFile(const nlohmann::json& message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "idMessage","" } };

		// Checking the chatId, idMessage or options fields
		if (!message.contains("chatId") || !message.contains("idMessage")) {
			response.bodyStr = "Required chatId, idMessage fields are missing";
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

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/downloadFile/" + *(this->apiTokenInstance);
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