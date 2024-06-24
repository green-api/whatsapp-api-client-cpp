#include "../../whatsapp-api-client-cpp/include/greenapi.hpp"

namespace greenapi
{

	unsigned int GreenApi::countInstances{ 0 };

	GreenApi::GreenApi(
		const std::string apiUrl,
		const std::string mediaUrl,
		const std::string idInstance,
		const std::string apiTokenInstance)
		: apiUrl(apiUrl), mediaUrl(mediaUrl), idInstance(idInstance), apiTokenInstance(apiTokenInstance),
		account(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		sending(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		receiving(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		journals(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		queues(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		groups(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		statuses(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		readMark(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance),
		serviceMethods(this->apiUrl, this->mediaUrl, this->idInstance, this->apiTokenInstance)
	{
		GreenApi::countInstances++;

		Logger::getInstance().log("Creating Instance " + std::to_string(this->countInstances) + " with Parameters: {" + this->apiUrl + \
			", mediaUrl : " + this->mediaUrl + ", idInstance : " + this->idInstance + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(this->apiTokenInstance, 0, 10) + "}", "info");

	};

	GreenApi::~GreenApi()
	{
		Logger::getInstance().log("Deleting Instance " + std::to_string(this->countInstances) + " with Parameters: {" + this->apiUrl + \
			", mediaUrl : " + this->mediaUrl + ", idInstance : " + this->idInstance + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(this->apiTokenInstance, 0, 10) + "}", "info");
		countInstances--;
	};

	unsigned int GreenApi::getNumberOfInstances() {
		return this->countInstances;
	};

	//------------- GREEN API partner methods

	unsigned int GreenApiPartners::countAccount{ 0 };

	GreenApiPartners::GreenApiPartners(
		const std::string apiUrl,
		const std::string partnerToken,
		const std::string accountName)
		: apiUrl(apiUrl), partnerToken(partnerToken), accountName(accountName)
	{
		GreenApiPartners::countAccount++;

		Logger::getInstance().log("Creating partners account " + std::to_string(this->countAccount) + " with Parameters: {" + this->apiUrl + \
			", partnerToken : " + Logger::getInstance().hideStringPart(this->partnerToken, 0, 20) + ", accountName : " + this->accountName + "}", "info");

	};

	GreenApiPartners::~GreenApiPartners()
	{
		Logger::getInstance().log("Deleting partners account " + std::to_string(this->countAccount) + " with Parameters: {" + this->apiUrl + \
			", partnerToken : " + Logger::getInstance().hideStringPart(this->partnerToken, 0, 20) + ", accountName : " + this->accountName + "}", "info");
		countAccount--;
	};

	unsigned int GreenApiPartners::getNumberOfAccounts() {
		return this->countAccount;
	};

	Response GreenApiPartners::getInstances() {

		Response response;
		std::string url = this->apiUrl + "/partner/getInstances/" + this->partnerToken;
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

	Response GreenApiPartners::createInstance(const nlohmann::json& settings)
	{
		Response response;
		std::string url = this->apiUrl + "/partner/createInstance/" + this->partnerToken;
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

	Response GreenApiPartners::deleteInstanceAccount(const unsigned long long idInstance)
	{
		Response response;
		nlohmann::json data{ {"idInstance", idInstance} };

		std::string url = this->apiUrl + "/partner/deleteInstanceAccount/" + this->partnerToken;
		Request req{ url, "HTTP", "POST" , data };

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