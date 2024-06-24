#pragma once
#ifndef GREEN_API_SERVICE_METHODS_H
#define GREEN_API_SERVICE_METHODS_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class ServiceMethods
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		ServiceMethods();

		ServiceMethods(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);


		/*
		* The method checks WhatsApp account availability on a phone number.
		* https://green-api.com/en/docs/api/service/CheckWhatsapp/
		* @param phoneNumber - phone number in the format 71234567890
		*/
		Response checkWhatsapp(const unsigned long long phoneNumber);

		/*
		* The method returns a user or a group chat avatar.
		* https://green-api.com/en/docs/api/service/GetAvatar/
		* @param message - data with chat number
		*/
		Response getAvatar(const nlohmann::json& message);

		/*
		* The method is aimed for getting a list of the current account contacts.
		* https://green-api.com/en/docs/api/service/GetContacts/
		*/
		Response getContacts();

		/*
		* The method is aimed for getting information on a contact.
		* https://green-api.com/en/docs/api/service/GetContactInfo/
		* @param message - data with chat number
		*/
		Response getContactInfo(const nlohmann::json& message);

		/*
		* The method deletes a message from a chat.
		* https://green-api.com/en/docs/api/service/deleteMessage/
		* @param message - data with chat number and message
		*/
		Response deleteMessage(const nlohmann::json& message);

		/*
		* The method archives a chat. One can archive chats that have at least one incoming message.
		* https://green-api.com/en/docs/api/service/archiveChat/
		* @param message - data with chat number
		*/
		Response archiveChat(const nlohmann::json& message);

		/*
		* The method unarchives a chat.
		* https://green-api.com/en/docs/api/service/unarchiveChat/
		* @param message - data with chat number
		*/
		Response unarchiveChat(const nlohmann::json& message);

		/*
		* The method is aimed for changing settings of disappearing messages in chats. 
		* The standard settings of the application are to be used: 0 (off), 86400 (24 hours), 604800 (7 days), 7776000 (90 days).
		* https://green-api.com/en/docs/api/service/SetDisappearingChat/
		* @param message - data with chat number and time
		*/
		Response setDisappearingChat(const nlohmann::json& message);

	};

} // namespace greenapi

#endif // GREEN_API_SERVICE_METHODS_H
