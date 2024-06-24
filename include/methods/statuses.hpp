#pragma once
#ifndef GREEN_API_STATUSES_H
#define GREEN_API_STATUSES_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class Statuses
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Statuses();

		Statuses(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);


		/*
		* The method is aimed for sending a text status. 
		* https://green-api.com/en/docs/api/statuses/SendTextStatus/
		* @param status - data for publishing status
		*/
		Response sendTextStatus(const nlohmann::json& status);

		/*
		* The method is aimed for sending a voice status. 
		* https://green-api.com/en/docs/api/statuses/SendVoiceStatus/
		* @param status - data for publishing status
		*/
		Response sendVoiceStatus(const nlohmann::json& status);

		/*
		* The method is aimed for sending a pictures or video status. 
		* https://green-api.com/en/docs/api/statuses/SendMediaStatus/
		* @param status - data for publishing status
		*/
		Response sendMediaStatus(const nlohmann::json& status);

		/*
		* The method for deleting status.
		* https://green-api.com/en/docs/api/statuses/DeleteStatus/
		* @param status - data for deleting status
		*/
		Response deleteStatus(const nlohmann::json& status);

		/*
		* The method returns an array of recipients marked sent/delivered/read for a given status.
		* https://green-api.com/en/docs/api/statuses/GetStatusStatistic/
		*  @param idMessage -  Status message ID
		*/
		Response getStatusStatistic(std::string idMessage);

		/*
		* The method returns the incoming status messages of the account. In the default mode the incoming status messages for 24 hours are returned.
		* https://green-api.com/en/docs/api/statuses/GetIncomingStatuses/
		*  @param minutes - time in minutes for which the status messages should be displayed (default is 1440 minutes)
		*/
		Response getIncomingStatuses(const unsigned int minutes = 1440);

		/*
		* The method returns the outgoing statuses of the account. In the default mode the outgoing status messages for 24 hours are returned.
		* https://green-api.com/en/docs/api/statuses/GetOutgoingStatuses/
		*  @param minutes - time in minutes for which the status messages should be displayed (default is 1440 minutes)
		*/
		Response getOutgoingStatuses(const unsigned int minutes = 1440);

	};
} // namespace greenapi

#endif // GREEN_API_STATUSES_H
