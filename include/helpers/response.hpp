#pragma once
#ifndef GREEN_API_RESPONSE_H
#define GREEN_API_RESPONSE_H

#include <nlohmann/json.hpp>


namespace greenapi {

	/*
	* API method response headers object.
	* @param contentType - response body type
	* @param currentDate - the current date
	* @param uploadDate - file upload date (methods UploadFile, SendFileByUpload)
	* @param expirationDate - file deletion date (methods UploadFile, SendFileByUpload)
	*/
	struct ResponseHeaders {
		std::string contentType = "application/json";
		std::string currentDate = "";
		std::string uploadDate = "";
		std::string expirationDate = "";
	};

	/*
	* API method response object, be sure to check the error parameter for errors before using it.
	* @param error - there is an error in the method response
	* @param status_code - status API response code
	* @param total_time - API request execution time
	* @param bodyStr - response body, used to display information about API errors
	* @param bodyJson - response body in json format for working with API response
	* @param headers - response header, used in the method for determining the file lifetime
	*/
	struct Response {
		bool error = true;
		unsigned int status_code = 0;
		double total_time = 0.0;
		ResponseHeaders headers;
		std::string bodyStr = "";
		nlohmann::json bodyJson = "";
	};

}// namespace greenapi

#endif // GREEN_API_RESPONSE_H
