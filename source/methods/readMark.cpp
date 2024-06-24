#include "../../../whatsapp-api-client-cpp/include/methods/readMark.hpp"

namespace greenapi
{
	ReadMark::ReadMark()
	{
		Logger::getInstance().log(std::string("Creating ReadMark class without parameters"), "error");
	};

	ReadMark::ReadMark(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating ReadMark class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response ReadMark::readChat(const nlohmann::json message) {

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

		requestMessage["chatId"] = message["chatId"];

		if (message.contains("idMessage")) {

			if (message["idMessage"].get<std::string>().size() < 10 || message["idMessage"].get<std::string>() == "") {
				response.bodyStr = "idMessage must be longer than 10 characters";
				return response;
			}

			requestMessage["idMessage"] = message["idMessage"];
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/readChat/" + *(this->apiTokenInstance);
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