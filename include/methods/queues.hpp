#pragma once
#ifndef GREEN_API_QUEUES_H
#define GREEN_API_QUEUES_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class Queues
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Queues();

		Queues(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method is aimed for getting a list of messages in the queue to be sent.
		* https://green-api.com/en/docs/api/queues/ShowMessagesQueue/
		*/
		Response showMessagesQueue();

		/*
		* The method is aimed for clearing the queue of messages to be sent. 
		* https://green-api.com/en/docs/api/queues/ClearMessagesQueue/
		*/
		Response clearMessagesQueue();

	};

} // namespace greenapi

#endif // GREEN_API_QUEUES_H
