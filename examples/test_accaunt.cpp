#include "greenapi.hpp"

/*
* Examples of account methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/account/
*/
int main_account() {

	/*
	* Examples of account methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","123456789632c49748f2a44b92" };

	/*
	* Example of using the getSettings method
	* The method is aimed for getting the current account settings.
	* https://green-api.com/en/docs/api/account/GetSettings/
	*/
	greenapi::Response getSettings = instance1101000001.account.getSettings();

	if (getSettings.error) {
		std::cout << "getSettings error: {status code: " << getSettings.status_code << ", request time: " << getSettings.total_time << ", body: " << getSettings.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " settings:" << std::endl;
		std::cout << "\twid: " << getSettings.bodyJson["wid"] << std::endl;
		std::cout << "\tcountryInstance: " << getSettings.bodyJson["countryInstance"] << std::endl;
		std::cout << "\ttypeAccount: " << getSettings.bodyJson["typeAccount"] << std::endl;
		std::cout << "\twebhookUrl: " << getSettings.bodyJson["webhookUrl"] << std::endl;
		std::cout << "\twebhookUrlToken: " << getSettings.bodyJson["webhookUrlToken"] << std::endl;
		std::cout << "\tdelaySendMessagesMilliseconds: " << getSettings.bodyJson["delaySendMessagesMilliseconds"] << std::endl;
		std::cout << "\tmarkIncomingMessagesReaded: " << getSettings.bodyJson["markIncomingMessagesReaded"] << std::endl;
		std::cout << "\tsharedSession: " << getSettings.bodyJson["sharedSession"] << std::endl;
		std::cout << "\toutgoingWebhook: " << getSettings.bodyJson["outgoingWebhook"] << std::endl;
		std::cout << "\toutgoingMessageWebhook: " << getSettings.bodyJson["outgoingMessageWebhook"] << std::endl;
		std::cout << "\toutgoingAPIMessageWebhook: " << getSettings.bodyJson["outgoingAPIMessageWebhook"] << std::endl;
		std::cout << "\tincomingWebhook: " << getSettings.bodyJson["incomingWebhook"] << std::endl;
		std::cout << "\tdeviceWebhook: " << getSettings.bodyJson["deviceWebhook"] << std::endl;
		std::cout << "\tstatusInstanceWebhook: " << getSettings.bodyJson["statusInstanceWebhook"] << std::endl;
		std::cout << "\tstateWebhook: " << getSettings.bodyJson["stateWebhook"] << std::endl;
		std::cout << "\tenableMessagesHistory: " << getSettings.bodyJson["enableMessagesHistory"] << std::endl;
		std::cout << "\tkeepOnlineStatus: " << getSettings.bodyJson["keepOnlineStatus"] << std::endl;
		std::cout << "\tpollMessageWebhook: " << getSettings.bodyJson["pollMessageWebhook"] << std::endl;
		std::cout << "\tincomingBlockWebhook: " << getSettings.bodyJson["incomingBlockWebhook"] << std::endl;
		std::cout << "\tincomingCallWebhook: " << getSettings.bodyJson["incomingCallWebhook"] << "\n" << std::endl;
	}

	/*
	* Example of using the setSettings method
	* The method is aimed for setting account settings.
	* https://green-api.com/en/docs/api/account/SetSettings/
	* @param settings - nlohmann::json object with account settings parameters
	*/
	nlohmann::json settings{
		{"delaySendMessagesMilliseconds",1000},
		{ "incomingWebhook","yes" }
	};

	greenapi::Response setSettings = instance1101000001.account.setSettings(settings);

	if (setSettings.error) {
		std::cout << "setSettings error: {status code: " << setSettings.status_code << ", request time: " << setSettings.total_time << ", body: " << setSettings.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " setSettings: " << setSettings.bodyJson["saveSettings"] << "\n" << std::endl;
	}

	/*
	* Example of using the setSettings method
	* The method is aimed for getting the account state.
	* https://green-api.com/en/docs/api/account/GetStateInstance/
	*/
	greenapi::Response stateInstance = instance1101000001.account.getStateInstance();

	if (stateInstance.error) {
		std::cout << "stateInstance error: {status code: " << stateInstance.status_code << ", request time: " << stateInstance.total_time << ", body: " << stateInstance.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " stateInstance: " << stateInstance.bodyJson["stateInstance"] << "\n" << std::endl;
	}

	/*
	* Example of using the reboot method
	* The method is aimed for rebooting an instance.
	* https://green-api.com/en/docs/api/account/Reboot/
	*/
	greenapi::Response reboot = instance1101000001.account.reboot();

	if (reboot.error) {
		std::cout << "reboot error: {status code: " << reboot.status_code << ", request time: " << reboot.total_time << ", body: " << reboot.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " isReboot: " << reboot.bodyJson["isReboot"] << "\n" << std::endl;
	}

	/*
	* Example of using the logout method
	* The example is commented out to prevent your account from being logged out by mistake.
	* The method is aimed for logging out an account.
	* https://green-api.com/en/docs/api/account/Logout/
	*/
	greenapi::Response logout = instance1101000001.account.logout();

	if (logout.error) {
		std::cout << "logout error: {status code: " << logout.status_code << ", request time: " << logout.total_time << ", body: " << logout.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " isLogout: " << logout.bodyJson["isLogout"] << "\n" << std::endl;
	}

	/*
	* Example of using the qr method
	* The method is aimed for getting QR code. To authorize your account, you have to scan a QR code from application WhatsApp Business on your phone.
	* https://green-api.com/en/docs/api/account/QR/
	*/
	greenapi::Response qr = instance1101000001.account.qr();

	if (qr.error) {
		std::cout << "qr error: {status code: " << qr.status_code << ", request time: " << qr.total_time << ", body: " << qr.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " get QR:" << std::endl;
		std::cout << "\ttype: " << qr.bodyJson["type"] << std::endl;
		std::cout << "\tmessage: " << qr.bodyJson["message"] << "\n" << std::endl;
	}

	/*
	* Example of using the getAuthorizationCode method
	* The method is intended to authorize an instance by phone number. The method is used as an alternative to the QR method.
	* https://green-api.com/en/docs/api/account/GetAuthorizationCode/
	* @param settings - phone number in the format 71234567890
	* To get an example of the phone number format, use the getSettings method
	*/
	greenapi::Response authorizationCode = instance1101000001.account.getAuthorizationCode(71234567890);

	if (authorizationCode.error) {
		std::cout << "authorizationCode error: {status code: " << authorizationCode.status_code << ", request time: " << authorizationCode.total_time << ", body: " << authorizationCode.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " getAuthorizationCode:" << std::endl;
		std::cout << "\tstatus: " << authorizationCode.bodyJson["status"] << std::endl;
		std::cout << "\tcode: " << authorizationCode.bodyJson["code"] << "\n" << std::endl;
	}

	/*
	* Example of using the setProfilePicture method
	* The method is aimed for setting an account picture.
	* https://green-api.com/en/docs/api/account/SetProfilePicture/
	* @param path - nlohmann::json obj path to the final file
	*/
	nlohmann::json setProfilePictureJson{
		{ "file","C:/1.png" }
	};

	greenapi::Response setProfilePicture = instance1101000001.account.setProfilePicture(setProfilePictureJson);

	if (setProfilePicture.error) {
		std::cout << "setProfilePicture error: {status code: " << setProfilePicture.status_code << ", request time: " << setProfilePicture.total_time << ", body: " << setProfilePicture.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "instance " + instance1101000001.idInstance + " setProfilePicture:" << std::endl;
		std::cout << "\turlAvatar: " << setProfilePicture.bodyJson["urlAvatar"] << std::endl;
		std::cout << "\tsetProfilePicture: " << setProfilePicture.bodyJson["setProfilePicture"] << std::endl;
		std::cout << "\treason: " << setProfilePicture.bodyJson["reason"] << "\n" << std::endl;
	}

	return 0;
}