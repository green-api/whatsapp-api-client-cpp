#pragma once
#ifndef GREEN_API_H
#define GREEN_API_H

#include <string>
#include <iostream>

#include "config.hpp"
#include "helpers.hpp"


namespace greenapi
{
	/*
	* Class for working with the GREEN API instance
	* https://green-api.com/en/docs/api/
	*/
	class GreenApi
	{

	public:
		const std::string apiUrl;
		const std::string mediaUrl;
		const std::string idInstance;
		const std::string apiTokenInstance;
		static unsigned int countInstances; // Active instance counter

		Account account;
		Sending sending;
		Receiving receiving;
		Journals journals;
		Queues queues;
		Groups groups;
		Statuses statuses;
		ReadMark readMark;
		ServiceMethods serviceMethods;

		/*
		* To make HTTP API requests to the GREEN API servers, you must use the parameters specified in your instance settings on your account:
		* @param apiUrl - link to GREEN API host to execute methods
		* @param mediaUrl - link to GREEN API host for sending files (methods UploadFile, SendFileByUpload)
		* @param idInstance - unique number of your sequence
		* @param apiTokenInstance - your instance access key
		* When executing requests with parameters from console it guarantees a minimum request execution time and a high probability of successful request completion.
		*/
		GreenApi(const std::string apiUrl = "https://api.green-api.com",
			const std::string mediaUrl = "https://media.green-api.com",
			const std::string idInstance = "1101000001",
			const std::string apiTokenInstance = "apiTokenInstance");

		~GreenApi();

		/*
		* Getting the number of created instances of a class
		*/
		unsigned int getNumberOfInstances();
	};

	/*
	* Class for working with GREEN API partner methods
	* https://green-api.com/en/docs/partners/
	*/
	class GreenApiPartners
	{

	public:
		const std::string apiUrl;
		const std::string partnerToken;
		const std::string accountName;
		static unsigned int countAccount; // Active account counter

		/*
		* To make HTTP API requests to the GREEN API servers, you must use the parameters specified in your instance settings on your account:
		* @param apiUrl - link to GREEN API host for executing partner methods
		* @param partnerToken - issued to the partner after agreeing on the terms of the partnership.
		* @param accountName - account name, convenient if you have several affiliate accounts
		*/
		GreenApiPartners(const std::string apiUrl = "https://api.green-api.com",
			const std::string partnerToken = "gac.123456789",
			const std::string accountName = "partners@greenapi.com");

		~GreenApiPartners();

		/*
		* Getting the number of created instances of a class
		*/
		unsigned int getNumberOfAccounts();

		/*
		* The method is aimed for getting all the account instances created by the partner.
		* https://green-api.com/en/docs/partners/getInstances/
		*/
		Response getInstances();

		/*
		* The method is aimed for creating a messenger account instance on the partner's part.
		* https://green-api.com/en/docs/partners/createInstance/
		* @param settings - object with settings parameters for the instance being created
		*/
		Response createInstance(const nlohmann::json& settings);

		/*
		* The method is aimed for deleting an instance of the partners's account.
		* https://green-api.com/en/docs/partners/deleteInstanceAccount/
		* @param idInstance - account instance id
		*/
		Response deleteInstanceAccount(const unsigned long long idInstance);


	};
} // namespace greenapi
#endif // GREEN_API_H
