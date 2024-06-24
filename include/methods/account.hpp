#pragma once
#ifndef GREEN_API_ACCOUNT_H
#define GREEN_API_ACCOUNT_H

#include <string>
#include <iostream>

#include "../helpers/requests.hpp"
#include "../helpers/logger.hpp"


namespace greenapi
{

	class Account
	{
	private:
		const std::string* apiUrl{};
		const std::string* mediaUrl{};
		const std::string* idInstance{};
		const std::string* apiTokenInstance{};

	public:

		Account();

		Account(const std::string& apiUrl,
			const std::string& mediaUrl,
			const std::string& idInstance,
			const std::string& apiTokenInstance);

		/*
		* The method is aimed for getting the current account settings.
		* https://green-api.com/en/docs/api/account/GetSettings/
		*/
		Response getSettings();

		/*
		* The method is aimed for setting account settings.
		* https://green-api.com/en/docs/api/account/SetSettings/
		* @param settings - object with account settings parameters
		*/
		Response setSettings(const nlohmann::json& settings);

		/*
		* The method is aimed for getting the account state.
		* https://green-api.com/en/docs/api/account/GetStateInstance/
		*/
		Response getStateInstance();

		/*
		* The method is aimed for getting the status of the account instance socket connection with WhatsApp.
		* https://green-api.com/en/docs/api/account/GetStatusInstance/
		*/
		Response getStatusInstance();

		/*
		* The method is aimed for rebooting an instance.
		* https://green-api.com/en/docs/api/account/Reboot/
		*/
		Response reboot();

		/*
		* The method is aimed for logging out an account.
		* https://green-api.com/en/docs/api/account/Logout/
		*/
		Response logout();

		/*
		* The method is aimed for getting QR code. To authorize your account, you have to scan a QR code from application WhatsApp Business on your phone.
		* https://green-api.com/en/docs/api/account/QR/
		*/
		Response qr();

		/*
		* Along with getting a QR code using QR method, it is possible to get a QR code via websocket connection.
		* The QR code will be updated as quickly as possible.
		* https://green-api.com/en/docs/api/account/Scanqrcode/
		*/
		Response scanqrcode();

		/*
		* The method is intended to authorize an instance by phone number. The method is used as an alternative to the QR method.
		* https://green-api.com/en/docs/api/account/GetAuthorizationCode/
		* @param settings - phone number in the format 71234567890
		* To get an example of the phone number format, use the getSettings method
		*/
		Response getAuthorizationCode(const unsigned long long phoneNumber);

		/*
		* The method is aimed for setting an account picture.
		* https://green-api.com/en/docs/api/account/SetProfilePicture/
		* @param path - path to the final file
		*/
		Response setProfilePicture(const nlohmann::json file);

		/*
		* The method is aimed to get information about the WhatsApp account
		* https://green-api.com/en/docs/api/account/GetWaSettings/
		*/
		Response getWaSettings();
	};

} // namespace greenapi

#endif // GREEN_API_ACCOUNT_H
