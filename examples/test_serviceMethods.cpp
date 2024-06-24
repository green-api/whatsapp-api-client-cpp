#include "greenapi.hpp"

/*
* Examples of service methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/service/
*/
int main_serviceMethods() {

	/*
	* Examples of service methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the checkWhatsapp method
	* The method checks WhatsApp account availability on a phone number.
	* https://green-api.com/en/docs/api/service/CheckWhatsapp/
	* @param settings - phone number in the format 71234567890
	*/

	const unsigned long long phoneNumber = 71234567890;

	greenapi::Response checkWhatsapp = instance1101000001.serviceMethods.checkWhatsapp(phoneNumber);

	if (checkWhatsapp.error) {
		std::cout << "checkWhatsapp error: {status code: " << checkWhatsapp.status_code << ", request time: " << checkWhatsapp.total_time << ", body: " << checkWhatsapp.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\texistsWhatsapp: " << checkWhatsapp.bodyJson["existsWhatsapp"] << "\n" << std::endl;
	}

	/*
	* The method returns a user or a group chat avatar.
	* https://green-api.com/en/docs/api/service/GetAvatar/
	* @param message - data with chat number
	*/

	nlohmann::json messageGetAvatar{ {"chatId","71234567890@c.us"} };

	greenapi::Response getAvatar = instance1101000001.serviceMethods.getAvatar(messageGetAvatar);

	if (getAvatar.error) {
		std::cout << "getAvatar error: {status code: " << getAvatar.status_code << ", request time: " << getAvatar.total_time << ", body: " << getAvatar.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\turlAvatar: " << getAvatar.bodyJson["urlAvatar"] << "\n" << std::endl;
		std::cout << "\tavailable: " << getAvatar.bodyJson["available"] << "\n" << std::endl;
	}

	/*
	* The method is aimed for getting a list of the current account contacts.
	* https://green-api.com/en/docs/api/service/GetContacts/
	*/

	greenapi::Response getContacts = instance1101000001.serviceMethods.getContacts();

	if (getContacts.error) {
		std::cout << "getContacts error: {status code: " << getContacts.status_code << ", request time: " << getContacts.total_time << ", body: " << getContacts.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		if (getContacts.bodyJson.is_array() && getContacts.bodyJson[0].contains("name") && getContacts.bodyJson[0].contains("id")) {
			std::cout << "\tid: " << getContacts.bodyJson[0]["id"].get<std::string>() << "\n" << std::endl;
			std::cout << "\tname: " << getContacts.bodyJson[0]["name"].get<std::string>() << "\n" << std::endl;
		}
		else {
			std::cerr << "JSON is not an array or the first object does not contain 'name' or 'id'." << std::endl;
		}
	}

	/*
	* The method is aimed for getting information on a contact.
	* https://green-api.com/en/docs/api/service/GetContactInfo/
	* @param message - data with chat number
	*/

	nlohmann::json messageGetContactInfo{ {"chatId","71234567890@c.us"} };

	greenapi::Response getContactInfo = instance1101000001.serviceMethods.getContactInfo(messageGetContactInfo);

	if (getContactInfo.error) {
		std::cout << "getContactInfo error: {status code: " << getContactInfo.status_code << ", request time: " << getContactInfo.total_time << ", body: " << getContactInfo.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tgetContactInfoStr: " << getContactInfo.bodyStr << "\n" << std::endl;
		std::cout << "\tavatar: " << getContactInfo.bodyJson["avatar"] << "\n" << std::endl;
	}

	/*
	* The method deletes a message from a chat.
	* https://green-api.com/en/docs/api/service/deleteMessage/
	* @param message - data with chat number and message
	*/

	nlohmann::json messageDeleteMessage{ {"chatId","71234567890@c.us"}, {"idMessage","BAE5F4886F6F2D05"} };

	greenapi::Response deleteMessage = instance1101000001.serviceMethods.deleteMessage(messageDeleteMessage);

	if (deleteMessage.error) {
		std::cout << "deleteMessage error: {status code: " << deleteMessage.status_code << ", request time: " << deleteMessage.total_time << ", body: " << deleteMessage.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tdeleteMessage: true" << "\n" << std::endl;
	}

	/*
	* The method archives a chat. One can archive chats that have at least one incoming message.
	* https://green-api.com/en/docs/api/service/archiveChat/
	* @param message - data with chat number
	*/

	nlohmann::json messageaAchiveChat{ {"chatId","71234567890@c.us"} };

	greenapi::Response archiveChat = instance1101000001.serviceMethods.archiveChat(messageaAchiveChat);

	if (archiveChat.error) {
		std::cout << "archiveChat error: {status code: " << archiveChat.status_code << ", request time: " << archiveChat.total_time << ", body: " << archiveChat.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tarchiveChat: true" << "\n" << std::endl;
	}

	/*
	* The method archives a chat. One can archive chats that have at least one incoming message.
	* https://green-api.com/en/docs/api/service/archiveChat/
	* @param message - data with chat number
	*/

	nlohmann::json messageaUnarchiveChat{ {"chatId","71234567890@c.us"} };

	greenapi::Response unarchiveChat = instance1101000001.serviceMethods.unarchiveChat(messageaUnarchiveChat);

	if (unarchiveChat.error) {
		std::cout << "unarchiveChat error: {status code: " << unarchiveChat.status_code << ", request time: " << unarchiveChat.total_time << ", body: " << unarchiveChat.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tunarchiveChat: true" << "\n" << std::endl;
	}

	/*
	* The method is aimed for changing settings of disappearing messages in chats.
	* The standard settings of the application are to be used: 0 (off), 86400 (24 hours), 604800 (7 days), 7776000 (90 days).
	* https://green-api.com/en/docs/api/service/SetDisappearingChat/
	* @param message - data with chat number and time
	*/

	nlohmann::json messageaSetDisappearingChat{ {"chatId","71234567890@c.us"}, {"ephemeralExpiration", 0} };

	greenapi::Response setDisappearingChat = instance1101000001.serviceMethods.setDisappearingChat(messageaSetDisappearingChat);

	if (setDisappearingChat.error) {
		std::cout << "setDisappearingChat error: {status code: " << setDisappearingChat.status_code << ", request time: " << setDisappearingChat.total_time << ", body: " << setDisappearingChat.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tchatId: " << getContactInfo.bodyJson["chatId"] << "\n" << std::endl;
		std::cout << "\tephemeralExpiration: " << getContactInfo.bodyJson["ephemeralExpiration"] << "\n" << std::endl;
		std::cout << "\tdisappearingMessagesInChat: " << getContactInfo.bodyJson["disappearingMessagesInChat"] << "\n" << std::endl;
	}

	return 0;
}