#pragma once
#ifndef GREEN_API_SENDING_H
#define GREEN_API_SENDING_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/mimeTypes.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi
{
	class Sending
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

		std::string getAfterDot(const std::string& input);

	public:

		Sending();

		Sending(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method is aimed for sending a text message to a personal or a group chat.
		* https://green-api.com/docs/api/sending/SendMessage/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response sendMessage(const nlohmann::json message);

		/*
		* This method is intended for sending messages with a poll to a private or group chat.
		* https://green-api.com/en/docs/api/sending/SendPoll/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response sendPoll(const nlohmann::json message);

		/*
		* The method is aimed for sending a file uploaded by form (form-data). The message will be added to the send queue, in the response you will receive a link to the downloaded file.
		* https://green-api.com/en/docs/api/sending/SendFileByUpload/
		* @param file - nlohmann::json obj containing file fields
		* @param text - nlohmann::json obj containing text fields
		*/
		Response sendFileByUpload(const nlohmann::json file, const nlohmann::json text);

		/*
		* The method is aimed for sending a file uploaded by Url.
		* https://green-api.com/en/docs/api/sending/SendFileByUrl/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response sendFileByUrl(const nlohmann::json message);

		/*
		* The method is designed to upload a file to the cloud storage, which can be sent using the sendFileByUrl method.
		* https://green-api.com/en/docs/api/sending/UploadFile/
		* @param file - nlohmann::json obj containing file fields
		* @param header - nlohmann::json obj containing header fields
		*/
		Response uploadFile(const nlohmann::json file, const nlohmann::json header = "");

		/*
		* Example of using the getFileSaveTime method
		* The method allows you to get the time of uploading a file to the GREEN API storage and its deletion
		* @param url - GREEN API link to the downloaded file
		*/
		Response getFileSaveTime(const std::string url);

		/*
		* The method is aimed for sending location message.
		* https://green-api.com/en/docs/api/sending/SendLocation/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response sendLocation(const nlohmann::json message);

		/*
		* The method is aimed for sending a contact message.
		* https://green-api.com/en/docs/api/sending/SendContact/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response sendContact(const nlohmann::json message);

		/*
		* The method is intended for forwarding messages to a personal or group chat. 
		* https://green-api.com/en/docs/api/sending/ForwardMessages/
		* @param message - nlohmann::json obj containing body fields
		*/
		Response forwardMessages(const nlohmann::json message);

	};

} // namespace greenapi

#endif // GREEN_API_SENDING_H
