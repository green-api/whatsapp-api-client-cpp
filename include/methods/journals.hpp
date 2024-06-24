#pragma once
#ifndef GREEN_API_JOURNALS_H
#define GREEN_API_JOURNALS_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class Journals
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Journals();

		Journals(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method returns the chat message history.
		* https://green-api.com/en/docs/api/journals/GetChatHistory/
		*  @param message - data to get chat history
		*/
		Response getChatHistory(const nlohmann::json& message);

		/*
		* The method returns the chat message.
		* https://green-api.com/en/docs/api/journals/GetMessage/
		*  @param message - data for receiving chat message
		*/
		Response getMessage(const nlohmann::json& message);

		/*
		* The method returns the last incoming messages of the account. In the default mode the incoming messages for 24 hours are returned.
		* https://green-api.com/en/docs/api/journals/LastIncomingMessages/
		*  @param minutes - time in minutes for which the messages should be displayed (default is 1440 minutes)
		*/
		Response lastIncomingMessages(const unsigned int minutes = 1440);

		/*
		* The method returns the last outgoing messages of the account. In the default mode the last messages for 24 hours are returned.
		* https://green-api.com/en/docs/api/journals/LastOutgoingMessages/
		*  @param minutes - time in minutes for which the messages should be displayed (default is 1440 minutes)
		*/
		Response lastOutgoingMessages(const unsigned int minutes = 1440);

	};

} // namespace greenapi

#endif // GREEN_API_JOURNALS_H
