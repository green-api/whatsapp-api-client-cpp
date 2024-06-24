#include "greenapi.hpp"

/*
* Examples of journals methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/journals/
*/
int main_journals() {

	/*
	* Examples of journals methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the lastIncomingMessages method
	* The method returns the last incoming messages of the account. In the default mode the incoming messages for 24 hours are returned.
	* https://green-api.com/en/docs/api/journals/LastIncomingMessages/
	*  @param minutes - time in minutes for which the messages should be displayed (default is 1440 minutes)
	*/
	greenapi::Response lastIncomingMessages = instance1101000001.journals.lastIncomingMessages();

	if (lastIncomingMessages.error) {
		std::cout << "receiveNotification error: {status code: " << lastIncomingMessages.status_code << ", request time: " << lastIncomingMessages.total_time << ", body: " << lastIncomingMessages.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresponse body: " << lastIncomingMessages.bodyStr << "\n" << std::endl;
	}

	/*
	* Example of using the lastOutgoingMessages method
	* The method returns the last outgoing messages of the account. In the default mode the last messages for 24 hours are returned.
	* https://green-api.com/en/docs/api/journals/LastOutgoingMessages/
	*  @param minutes - time in minutes for which the messages should be displayed (default is 1440 minutes)
	*/
	greenapi::Response lastOutgoingMessages = instance1101000001.journals.lastOutgoingMessages();

	if (lastOutgoingMessages.error) {
		std::cout << "receiveNotification error: {status code: " << lastOutgoingMessages.status_code << ", request time: " << lastOutgoingMessages.total_time << ", body: " << lastOutgoingMessages.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresponse body: " << lastOutgoingMessages.bodyStr << "\n" << std::endl;
	}

	/*
	* Example of using the getChatHistory method
	* The method returns the chat message history.
	* https://green-api.com/en/docs/api/journals/GetChatHistory/
	*  @param message - data to get chat history
	* example json object nlohmann::json message{
	{ "chatId","71234567890@c.us" },
	{ "count", 1 }
	};
	*/

	nlohmann::json getChatHistoryMessage{
	{ "chatId","71234567890@c.us" },
	{ "count", 1 }
	};

	greenapi::Response getChatHistory = instance1101000001.journals.getChatHistory(getChatHistoryMessage);

	if (getChatHistory.error) {
		std::cout << "receiveNotification error: {status code: " << getChatHistory.status_code << ", request time: " << getChatHistory.total_time << ", body: " << getChatHistory.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresponse body: " << getChatHistory.bodyStr << "\n" << std::endl;
	}

	/*
	* Example of using the getMessage method
	* The method returns the chat message.
	* https://green-api.com/en/docs/api/journals/GetMessage/
	*  @param message - data for receiving chat message
	* example json object nlohmann::json message{
	{ "chatId","71234567890@c.us" },
	{ "idMessage", "BAE51C6F128E2780" }
	};
	*/

	nlohmann::json getMessageMessage{
	{ "chatId","71234567890@c.us" },
	{ "idMessage", "BAE51C6F128E2780" }
	};

	greenapi::Response getMessage = instance1101000001.journals.getMessage(getMessageMessage);

	if (getMessage.error) {
		std::cout << "receiveNotification error: {status code: " << getMessage.status_code << ", request time: " << getMessage.total_time << ", body: " << getMessage.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresponse body: " << getMessage.bodyStr << "\n" << std::endl;
	}

	return 0;
}