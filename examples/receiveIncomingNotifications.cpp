#include "../include/greenapi.hpp"

/*
* Example of receiving notifications
*/
int main() {

	/*
	* Example of receiving notifications
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101000001","7f55ef0e432e4374bc4d0b0b96a37e0f5cc30ca123456" };

	while (1) {
		greenapi::Response receiveNotification = instance1101000001.receiving.receiveNotification(5);

		if (receiveNotification.error) {
			std::cout << "receiveNotification error: {status code: " << receiveNotification.status_code << ", request time: " << receiveNotification.total_time << ", body: " << receiveNotification.bodyStr << "}" << "\n" << std::endl;
		}
		else if(receiveNotification.bodyStr == "null") {
			std::cout << "All notifications received" << "\n" << std::endl;
			return 0;
		}
		else {
			std::cout << "\treceiptId: " << receiveNotification.bodyJson["receiptId"] << "\n" << std::endl;
			std::cout << "\tbody: " << receiveNotification.bodyJson["body"] << "\n" << std::endl;
		}

		greenapi::Response deleteNotification = instance1101000001.receiving.deleteNotification(receiveNotification.bodyJson["receiptId"]);

		if (deleteNotification.error) {
			std::cout << "deleteNotification error: {status code: " << deleteNotification.status_code << ", request time: " << deleteNotification.total_time << ", body: " << deleteNotification.bodyStr << "}" << "\n" << std::endl;
		}
		else {
			std::cout << "\tdeleteNotification result: " << deleteNotification.bodyJson["result"] << "\n" << std::endl;
		}
	}

	return 0;
}
