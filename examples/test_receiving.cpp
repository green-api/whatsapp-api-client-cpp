#include "../include/greenapi.hpp"

/*
* Examples of receiving methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/receiving/
*/
int main_receiving() {

	/*
	* Examples of receiving methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the receiveNotification method
	* The method is aimed for receiving one incoming notification from the notifications queue.
	* @param receiveTimeout - Notification waiting timeout, takes a value from 5 to 60 seconds (default 5 seconds)
	* https://green-api.com/en/docs/api/receiving/technology-http-api/ReceiveNotification/
	*/
	greenapi::Response receiveNotification = instance1101000001.receiving.receiveNotification(5);

	if (receiveNotification.error) {
		std::cout << "receiveNotification error: {status code: " << receiveNotification.status_code << ", request time: " << receiveNotification.total_time << ", body: " << receiveNotification.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\treceiptId: " << receiveNotification.bodyJson["receiptId"] << "\n" << std::endl;
		std::cout << "\tbody: " << receiveNotification.bodyJson["body"] << "\n" << std::endl;
	}

	/*
	* Example of using the deleteNotification method
	* The method is aimed for deleting an incoming notification from the notification queue.
	* https://green-api.com/en/docs/api/receiving/technology-http-api/DeleteNotification/
	* @param receiptId - Receipt Id for deleting an incoming notification received by ReceiveNotification method
	*/
	greenapi::Response deleteNotification = instance1101000001.receiving.deleteNotification(receiveNotification.bodyJson["receiptId"]);

	if (deleteNotification.error) {
		std::cout << "deleteNotification error: {status code: " << deleteNotification.status_code << ", request time: " << deleteNotification.total_time << ", body: " << deleteNotification.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tresult: " << deleteNotification.bodyJson["result"] << "\n" << std::endl;
	}

	/*
	* Example of using the downloadFile method
	* The method is aimed for downloading incoming and outgoing files.
	* https://green-api.com/en/docs/api/receiving/files/DownloadFile/
	* @param message - data to receive the file
	* example json object nlohmann::json message{
	{ "chatId","71234567890@c.us" },
	{ "idMessage","3EB0C767D097B7C7C030" }
	};
	*/

	nlohmann::json message{
	{ "chatId","71234567890@c.us" },
	{ "idMessage","B509C2E79B21E66F80" }
	};

	greenapi::Response downloadFile = instance1101000001.receiving.downloadFile(message);

	if (downloadFile.error) {
		std::cout << "downloadFile error: {status code: " << downloadFile.status_code << ", request time: " << downloadFile.total_time << ", body: " << downloadFile.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tdownloadUrl: " << downloadFile.bodyJson["downloadUrl"] << "\n" << std::endl;
	}

	return 0;
}