#include "../../../whatsapp-api-client-cpp/include/methods/statuses.hpp"

namespace greenapi
{
	Statuses::Statuses()
	{
		Logger::getInstance().log(std::string("Creating Statuses class without parameters"), "error");
	};

	Statuses::Statuses(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Statuses class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Statuses::sendTextStatus(const nlohmann::json& status) {

		Response response;
		nlohmann::json requestMessage{ { "message", "" } };

		// Checking the message
		if (!status.contains("message")) {
			response.bodyStr = "Required message field are missing";
			return response;
		}
		if (status["message"].get<std::string>().size() < 1) {
			response.bodyStr = "message length must be at least 1 character";
			return response;
		}

		requestMessage["message"] = status["message"];

		if (status.contains("backgroundColor")) {
			requestMessage["backgroundColor"] = status["backgroundColor"];
		}
		if (status.contains("font")) {
			requestMessage["font"] = status["font"];
		}
		if (!status.contains("participants") || !status["participants"].is_array()) {
			response.bodyStr = "The key \"participants\" is not an array.";
			return response;
		}

		requestMessage["participants"] = status["participants"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendTextStatus/" + *(this->apiTokenInstance);
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

	Response Statuses::sendVoiceStatus(const nlohmann::json& status) {

		Response response;
		nlohmann::json requestMessage{ { "urlFile", "" }, { "fileName", "" } };

		// Checking the urlFile and fileName
		if (!status.contains("urlFile") || !status.contains("fileName")) {
			response.bodyStr = "Required urlFile field are missing";
			return response;
		}
		if (status["urlFile"].get<std::string>().size() < 8) {
			response.bodyStr = "urlFile must be longer than 8 characters";
			return response;
		}
		if (status["fileName"].get<std::string>().find('.') == std::string::npos) {
			response.bodyStr = "To send a file correctly, fileName must have a dot and an indication of the file extension, for example \"picture.jpg\"";
			return response;
		}
		if (status["fileName"].get<std::string>().size() < 3) {
			response.bodyStr = "To send a file correctly, fileName must have the file name and extension, for example \"picture.jpg\"";
			return response;
		}

		requestMessage["urlFile"] = status["urlFile"];
		requestMessage["fileName"] = status["fileName"];

		if (status.contains("backgroundColor")) {
			requestMessage["backgroundColor"] = status["backgroundColor"];
		}
		if (!status.contains("participants") || !status["participants"].is_array()) {
			response.bodyStr = "The key \"participants\" is not an array.";
			return response;
		}

		requestMessage["participants"] = status["participants"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendVoiceStatus/" + *(this->apiTokenInstance);
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

	Response Statuses::sendMediaStatus(const nlohmann::json& status) {

		Response response;
		nlohmann::json requestMessage{ { "urlFile", "" }, { "fileName", "" } };

		// Checking the urlFile and fileName
		if (!status.contains("urlFile") || !status.contains("fileName")) {
			response.bodyStr = "Required urlFile field are missing";
			return response;
		}
		if (status["urlFile"].get<std::string>().size() < 8) {
			response.bodyStr = "urlFile must be longer than 8 characters";
			return response;
		}
		if (status["fileName"].get<std::string>().find('.') == std::string::npos) {
			response.bodyStr = "To send a file correctly, fileName must have a dot and an indication of the file extension, for example \"picture.jpg\"";
			return response;
		}
		if (status["fileName"].get<std::string>().size() < 3) {
			response.bodyStr = "To send a file correctly, fileName must have the file name and extension, for example \"picture.jpg\"";
			return response;
		}

		requestMessage["urlFile"] = status["urlFile"];
		requestMessage["fileName"] = status["fileName"];

		if (status.contains("caption")) {
			requestMessage["caption"] = status["caption"];
		}
		if (!status.contains("participants") || !status["participants"].is_array()) {
			response.bodyStr = "The key \"participants\" is not an array.";
			return response;
		}

		requestMessage["participants"] = status["participants"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendMediaStatus/" + *(this->apiTokenInstance);
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

	Response Statuses::deleteStatus(const nlohmann::json& status) {

		Response response;
		nlohmann::json requestMessage{ { "idMessage", "" } };

		// Checking the idMessage
		if (!status.contains("idMessage")) {
			response.bodyStr = "Required idMessage field are missing";
			return response;
		}
		if (status["idMessage"].get<std::string>().size() < 5) {
			response.bodyStr = "idMessage must be longer than 5 characters";
			return response;
		}

		requestMessage["idMessage"] = status["idMessage"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/deleteStatus/" + *(this->apiTokenInstance);
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

	Response Statuses::getStatusStatistic(std::string idMessage) {

		Response response;

		if (idMessage.size() < 5) {
			response.bodyStr = "idMessage must be longer than 5 characters";
			return response;
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getStatusStatistic/" + *(this->apiTokenInstance) + "?idMessage=" + idMessage;
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

	Response Statuses::getIncomingStatuses(const unsigned int minutes) {

		Response response;
		unsigned int sendMinutes = 1440;

		if (minutes < 0 || minutes == 0) { sendMinutes = 1440; }

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getIncomingStatuses/" + *(this->apiTokenInstance) + "?minutes=" + std::to_string(sendMinutes);
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

	Response Statuses::getOutgoingStatuses(const unsigned int minutes) {

		Response response;
		unsigned int sendMinutes = 1440;

		if (minutes < 0 || minutes == 0) { sendMinutes = 1440; }

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getOutgoingStatuses/" + *(this->apiTokenInstance) + "?minutes=" + std::to_string(sendMinutes);
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