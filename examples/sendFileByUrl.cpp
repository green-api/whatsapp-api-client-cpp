#include "../include/greenapi.hpp"

/*
* Example of sending file by link
* https://green-api.com/en/docs/api/sending/SendFileByUrl/
*/
int main() {

	/*
	* Example of sending file by link
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

	/*
	* Example of using the SendFileByUrl method
	* The method is aimed for sending a file uploaded by Url.
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "urlFile","https://storage/1101123456/13238852123456.png" },
	{ "fileName","1.png" },
	{ "caption","I use GREEN-API to send this message to you!" },
	{ "quotedMessageId","" }
	};
	* https://green-api.com/en/docs/api/sending/SendFileByUrl/
	*/

	nlohmann::json SendFileByUrlJson{
	{ "chatId","71234567890@c.us" },
	{ "urlFile","https://sw-media-1101.storage.yandexcloud.net/1101123456s/13238852-be73-4f8c-a973-966d2730ce15.png" },
	{ "fileName","1.png" },
	{ "caption","I use GREEN-API to send this message to you!" }
	};

	greenapi::Response sendFileByUrl = instance1101000001.sending.sendFileByUrl(SendFileByUrlJson);

	if (sendFileByUrl.error) {
		std::cout << "sendFileByUrl error: {status code: " << sendFileByUrl.status_code << ", request time: " << sendFileByUrl.total_time << ", body: " << sendFileByUrl.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendFileByUrl.bodyJson["idMessage"] << std::endl;
	}

	return 0;
}
