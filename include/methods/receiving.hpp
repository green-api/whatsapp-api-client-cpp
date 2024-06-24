#pragma once
#ifndef GREEN_API_RECEIVING_H
#define GREEN_API_RECEIVING_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class Receiving
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Receiving();

		Receiving(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method is aimed for receiving one incoming notification from the notifications queue.
		* https://green-api.com/en/docs/api/receiving/technology-http-api/ReceiveNotification/
		*  @param receiveTimeout - Notification waiting timeout, takes a value from 5 to 60 seconds (default 5 seconds)
		*/
		Response receiveNotification(const unsigned int receiveTimeout = 5);

		/*
		* The method is aimed for deleting an incoming notification from the notification queue. 
		* https://green-api.com/en/docs/api/receiving/technology-http-api/DeleteNotification/
		* @param receiptId - Receipt Id for deleting an incoming notification received by ReceiveNotification method
		*/
		Response deleteNotification(const unsigned int receiptId);

		/*
		* The method is aimed for downloading incoming and outgoing files.
		* https://green-api.com/en/docs/api/receiving/files/DownloadFile/
		* @param message - data to receive the file
		*/
		Response downloadFile(const nlohmann::json& message);

	};

} // namespace greenapi

#endif // GREEN_API_RECEIVING_H
