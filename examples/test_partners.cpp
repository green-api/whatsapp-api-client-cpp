#include "greenapi.hpp"

/*
* Examples of partners methods methods working
* Rename the function to main to use
* https://green-api.com/en/docs/partners/
*/
int main_partners() {

	/*
	* Examples of partners methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl parameters specifically for your personal account, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApiPartners partnersMethods{ "https://api.green-api.com","gac.02dff0c4fa944bc882bf207d379d9e3f0123456789","partners@greenapi.com" };

	/*
	* The method is aimed for getting all the account instances created by the partner.
	* https://green-api.com/en/docs/partners/getInstances/
	*/

	greenapi::Response getInstances = partnersMethods.getInstances();

	if (getInstances.error) {
		std::cout << "getInstances error: {status code: " << getInstances.status_code << ", request time: " << getInstances.total_time << ", body: " << getInstances.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tinstances: " << getInstances.bodyStr << "\n" << std::endl;
		std::cout << "\tinstances[0][\"idInstance\"]: " << getInstances.bodyJson[0]["idInstance"] << "\n" << std::endl;
	}

	/*
	* The method is aimed for creating a messenger account instance on the partner's part.
	* https://green-api.com/en/docs/partners/createInstance/
	* @param settings - object with settings parameters for the instance being created
	*/

	nlohmann::json settings{
		{"delaySendMessagesMilliseconds",1000},
		{ "incomingWebhook","yes" },
		{ "name","Test of GREEN API partner methods" }
	};

	greenapi::Response createInstance = partnersMethods.createInstance(settings);

	if (createInstance.error) {
		std::cout << "createInstance error: {status code: " << createInstance.status_code << ", request time: " << createInstance.total_time << ", body: " << createInstance.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		if (createInstance.bodyJson.contains("code")) {
			std::cout << "createInstance error: {status code: " << createInstance.bodyJson["code"] << ", description: " << createInstance.bodyJson["description"] << "}" << "\n" << std::endl;
		}
		else {
			std::cout << "\tidInstance: " << createInstance.bodyJson["idInstance"] << "\n" << std::endl;
			std::cout << "\tapiTokenInstance: " << createInstance.bodyJson["apiTokenInstance"] << "\n" << std::endl;
			std::cout << "\ttypeInstance: " << createInstance.bodyJson["typeInstance"] << "\n" << std::endl;
		}
	}

	/*
	* The method is aimed for deleting an instance of the partners's account.
	* https://green-api.com/en/docs/partners/deleteInstanceAccount/
	* @param idInstance - account instance id
	*/

	const unsigned long long idInstance{ 1101123456 };

	greenapi::Response deleteInstanceAccount = partnersMethods.deleteInstanceAccount(idInstance);

	if (deleteInstanceAccount.error) {
		std::cout << "deleteInstanceAccount error: {status code: " << deleteInstanceAccount.status_code << ", request time: " << deleteInstanceAccount.total_time << ", body: " << deleteInstanceAccount.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		if (deleteInstanceAccount.bodyJson.contains("code")) {
			std::cout << "createInstance error: {status code: " << deleteInstanceAccount.bodyJson["code"] << ", description: " << deleteInstanceAccount.bodyJson["description"] << "}" << "\n" << std::endl;
		}
		else {
			std::cout << "\tdeleteInstanceAccount: " << deleteInstanceAccount.bodyJson["deleteInstanceAccount"] << "\n" << std::endl;
		}
	}

	return 0;
}