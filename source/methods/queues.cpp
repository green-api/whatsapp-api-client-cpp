#include "../../../whatsapp-api-client-cpp/include/methods/queues.hpp"

namespace greenapi
{
	Queues::Queues()
	{
		Logger::getInstance().log(std::string("Creating Queues class without parameters"), "error");
	};

	Queues::Queues(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Queues class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Queues::showMessagesQueue() {

		Response response;

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/showMessagesQueue/" + *(this->apiTokenInstance);
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

	Response Queues::clearMessagesQueue() {

		Response response;

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/clearMessagesQueue/" + *(this->apiTokenInstance);
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