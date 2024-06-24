#include "greenapi.hpp"

/*
* Examples of queues methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/queues/
*/
int main_queues() {

	/*
	* Examples of queues methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the showMessagesQueue method
	* The method is aimed for getting a list of messages in the queue to be sent.
	* https://green-api.com/en/docs/api/queues/ShowMessagesQueue/
	*/
	greenapi::Response showMessagesQueue = instance1101000001.queues.showMessagesQueue();

	if (showMessagesQueue.error) {
		std::cout << "showMessagesQueue error: {status code: " << showMessagesQueue.status_code << ", request time: " << showMessagesQueue.total_time << ", body: " << showMessagesQueue.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresponse body: " << showMessagesQueue.bodyStr << "\n" << std::endl;
	}

	/*
	* Example of using the clearMessagesQueue method
	* The method is aimed for clearing the queue of messages to be sent.
	* https://green-api.com/en/docs/api/queues/ClearMessagesQueue/
	*/
	greenapi::Response clearMessagesQueue = instance1101000001.queues.clearMessagesQueue();

	if (clearMessagesQueue.error) {
		std::cout << "clearMessagesQueue error: {status code: " << clearMessagesQueue.status_code << ", request time: " << clearMessagesQueue.total_time << ", body: " << clearMessagesQueue.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tisCleared: " << clearMessagesQueue.bodyJson["isCleared"] << "\n" << std::endl;
	}

	return 0;
}