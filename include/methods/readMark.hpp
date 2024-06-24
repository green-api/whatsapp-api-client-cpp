#pragma once
#ifndef GREEN_API_READMARK_H
#define GREEN_API_READMARK_H

#include <string>
#include <iostream>

#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"
#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"


namespace greenapi {

	class ReadMark
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		ReadMark();

		ReadMark(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method is aimed for marking messages in a chat as read.
		* https://green-api.com/en/docs/api/marks/ReadChat/
		*/
		Response readChat(const nlohmann::json message);

	};

} // namespace greenapi

#endif // GREEN_API_READMARK_H
