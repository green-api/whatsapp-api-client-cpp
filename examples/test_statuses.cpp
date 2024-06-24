#include "greenapi.hpp"

/*
* Examples of statuses methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/statuses/
*/
int main_statuses() {

	/*
	* Examples of statuses methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","9903780796","32c574a141a84892b256799420cd3e9de49fbe98164f43cb98" };

	/*
	* The method is aimed for sending a text status.
	* https://green-api.com/en/docs/api/statuses/SendTextStatus/
	* @param status - data for publishing status
	*/

	nlohmann::json statusSendTextStatus{
		{"message","Hello"},
		{"participants", {
			"79876716790@c.us",
			"77761759054@c.us"
			}
		}
	};

	greenapi::Response sendTextStatus = instance1101000001.statuses.sendTextStatus(statusSendTextStatus);

	if (sendTextStatus.error) {
		std::cout << "sendTextStatus error: {status code: " << sendTextStatus.status_code << ", request time: " << sendTextStatus.total_time << ", body: " << sendTextStatus.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendTextStatus.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* The method is aimed for sending a voice status.
	* https://green-api.com/en/docs/api/statuses/SendVoiceStatus/
	* @param status - data for publishing status
	*/

	nlohmann::json statusSendVoiceStatus{
		{"urlFile","https://sw-mediaout-1103.storage.yandexcloud.net/1103900032/7851c23b-fb9b-4026-b476-8b0d46de0a54.mpga"},
		{"fileName","test.mp3"},
		{"participants", {
			"79876716790@c.us",
			"77761759054@c.us"
			}
		}
	};

	greenapi::Response sendVoiceStatus = instance1101000001.statuses.sendVoiceStatus(statusSendVoiceStatus);

	if (sendVoiceStatus.error) {
		std::cout << "sendVoiceStatus error: {status code: " << sendVoiceStatus.status_code << ", request time: " << sendVoiceStatus.total_time << ", body: " << sendVoiceStatus.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendVoiceStatus.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* The method is aimed for sending a pictures or video status.
	* https://green-api.com/en/docs/api/statuses/SendMediaStatus/
	* @param status - data for publishing status
	*/

	nlohmann::json statusSendMediaStatus{
		{"urlFile","https://sw-mediaout-1103.storage.yandexcloud.net/1103900032/1bed2d59-ecb2-4090-bcbe-95f70f83d54c.mp4"},
		{"fileName","test.mp4"},
		{"caption","Hello"},
		{"participants", {
			"79876716790@c.us",
			"77761759054@c.us"
			}
		}
	};

	greenapi::Response sendMediaStatus = instance1101000001.statuses.sendMediaStatus(statusSendMediaStatus);

	if (sendMediaStatus.error) {
		std::cout << "sendMediaStatus error: {status code: " << sendMediaStatus.status_code << ", request time: " << sendMediaStatus.total_time << ", body: " << sendMediaStatus.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendMediaStatus.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* The method for deleting status.
	* https://green-api.com/en/docs/api/statuses/DeleteStatus/
	* @param status - data for deleting status
	*/

	nlohmann::json statusDeleteStatus{
	{"idMessage","BAE557AF27F73A1B"}
	};

	greenapi::Response deleteStatus = instance1101000001.statuses.deleteStatus(statusDeleteStatus);

	if (deleteStatus.error) {
		std::cout << "deleteStatus error: {status code: " << deleteStatus.status_code << ", request time: " << deleteStatus.total_time << ", body: " << deleteStatus.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tdeleteStatus: true" << "\n" << std::endl;
	}

	/*
	* The method returns an array of recipients marked sent/delivered/read for a given status.
	* https://green-api.com/en/docs/api/statuses/GetStatusStatistic/
	*  @param idMessage -  Status message ID
	*/

	std::string idMessage{ "BAE557AF27F73A1B" };

	greenapi::Response getStatusStatistic = instance1101000001.statuses.getStatusStatistic(idMessage);

	if (getStatusStatistic.error) {
		std::cout << "getStatusStatistic error: {status code: " << getStatusStatistic.status_code << ", request time: " << getStatusStatistic.total_time << ", body: " << getStatusStatistic.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tgetStatusStatistic: " << getStatusStatistic.bodyStr << "\n" << std::endl;
	}

	/*
	* The method returns the incoming status messages of the account. In the default mode the incoming status messages for 24 hours are returned.
	* https://green-api.com/en/docs/api/statuses/GetIncomingStatuses/
	*  @param minutes - time in minutes for which the status messages should be displayed (default is 1440 minutes)
	*/

	unsigned int minutesGetIncomingStatuses{ 1440 };

	greenapi::Response getIncomingStatuses = instance1101000001.statuses.getIncomingStatuses(minutesGetIncomingStatuses);

	if (getIncomingStatuses.error) {
		std::cout << "getStatusStatistic error: {status code: " << getIncomingStatuses.status_code << ", request time: " << getIncomingStatuses.total_time << ", body: " << getIncomingStatuses.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tgetIncomingStatuses: " << getIncomingStatuses.bodyStr << "\n" << std::endl;
	}

	/*
	* The method returns the outgoing statuses of the account. In the default mode the outgoing status messages for 24 hours are returned.
	* https://green-api.com/en/docs/api/statuses/GetOutgoingStatuses/
	*  @param minutes - time in minutes for which the status messages should be displayed (default is 1440 minutes)
	*/

	unsigned int minutesGetOutgoingStatuses{ 1440 };

	greenapi::Response getOutgoingStatuses = instance1101000001.statuses.getOutgoingStatuses(minutesGetOutgoingStatuses);

	if (getOutgoingStatuses.error) {
		std::cout << "getOutgoingStatuses error: {status code: " << getOutgoingStatuses.status_code << ", request time: " << getOutgoingStatuses.total_time << ", body: " << getOutgoingStatuses.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tgetIncomingStatuses: " << getOutgoingStatuses.bodyStr << "\n" << std::endl;
	}

	return 0;
}