#include "greenapi.hpp"

/*
* Example of sending message
* https://green-api.com/en/docs/api/sending/SendMessage/
*/
int main() {

	/*
	* Example of sending message
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the sendMessage method
	* The method is aimed for sending a text message to a personal or a group chat.
	* @param message - nlohmann::json object with message parameters
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "message","I use GREEN-API to send this message to you!" },
	{ "quotedMessageId","3EB0C767D097B7C7C030" },
	{ "linkPreview",true }
	};
	* https://green-api.com/en/docs/api/sending/SendMessage/
	*/

	nlohmann::json sendMessageJson{
		{ "chatId","71234567890@c.us" },
		{ "message","I use GREEN-API to send this message to you!" }
	};
	greenapi::Response sendMessage = instance1101000001.sending.sendMessage(sendMessageJson);

	if (sendMessage.error) {
		std::cout << "sendMessage error: {status code: " << sendMessage.status_code << ", request time: " << sendMessage.total_time << ", body: " << sendMessage.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendMessage.bodyJson["idMessage"] << "\n" << std::endl;
	}

	return 0;
}
