#include "greenapi.hpp"

/*
* Examples of Read mark methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/marks/ReadChat/
*/
int main_readMark() {

	/*
	* Examples of Read mark methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the readChat method
	* The method is aimed for marking messages in a chat as read.
	* https://green-api.com/en/docs/api/marks/ReadChat/
	* @param message - chat data to read
	* example json object nlohmann::json message{
	{ "chatId","71234567890@c.us" }
	};
	*/

	nlohmann::json message{
	{ "chatId","71234567890@c.us" }
	};

	greenapi::Response readChat = instance1101000001.readMark.readChat(message);

	if (readChat.error) {
		std::cout << "readChat error: {status code: " << readChat.status_code << ", request time: " << readChat.total_time << ", body: " << readChat.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tsetRead: " << readChat.bodyJson["setRead"] << "\n" << std::endl;
	}

	return 0;
}