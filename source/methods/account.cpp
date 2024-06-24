#include "../../../whatsapp-api-client-cpp/include/methods/account.hpp"

namespace greenapi
{
	Account::Account()
	{
		Logger::getInstance().log(std::string("Creating Account class without parameters"), "error");
	};

	Account::Account(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Account class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Account::getSettings() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getSettings/" + *(this->apiTokenInstance);
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

	Response Account::setSettings(const nlohmann::json& settings) {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/setSettings/" + *(this->apiTokenInstance);
		Request req{ url, "HTTP", "POST" , settings };

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

	Response Account::getStateInstance() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getStateInstance/" + *(this->apiTokenInstance);

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
	};

	Response Account::getStatusInstance() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getStatusInstance/" + *(this->apiTokenInstance);
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

	Response Account::reboot() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/reboot/" + *(this->apiTokenInstance);
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

	Response Account::logout() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/logout/" + *(this->apiTokenInstance);
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

	Response Account::qr() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/qr/" + *(this->apiTokenInstance);
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

	Response Account::scanqrcode() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/scanqrcode/" + *(this->apiTokenInstance);
		Request req{ url, "WS" };

		try {
			return Response();
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Account::getAuthorizationCode(const unsigned long long phoneNumber) {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getAuthorizationCode/" + *(this->apiTokenInstance);
		nlohmann::json body = { { "phoneNumber", phoneNumber } };
		Request req{ url, "HTTP", "POST", body };

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

	Response Account::setProfilePicture(const nlohmann::json file) {

		Response response;
		nlohmann::json bodyFile{ { "file","" } };

		// Checking the chatId, message or options fields
		if (!file.contains("file")) {
			response.bodyStr = "Required chatId or file fields are missing";
			return response;
		}

		bodyFile["file"] = file["file"].get<std::string>();

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/setProfilePicture/" + *(this->apiTokenInstance);
		nlohmann::json body = nlohmann::json::object();

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

	Response Account::getWaSettings() {

		Response response;
		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/getWaSettings/" + *(this->apiTokenInstance);
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