#pragma once
#ifndef GREEN_API_REQUESTS_H
#define GREEN_API_REQUESTS_H

#include <iostream>
#include <stdexcept>
#include <map>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <regex>

#include "../config.hpp"
#include "logger.hpp"
#include "response.hpp"


namespace greenapi {

	struct RequestHeaders {
		std::string contentType = "json"; // json (application/json), data (multipart/form-data), binary
		std::string userAgent = "GREEN-API_SDK_CPP/1.0";
	};

	struct Request {
		std::string url = "";
		std::string protocol = "HTTP"; // HTTP
		std::string type = "GET"; // GET, POST, DELETE, HEAD
		nlohmann::json body = "";
		nlohmann::json bodyFile = "";
		RequestHeaders headers;
	};

	/*
	* Internal functions for working with requests
	*/
	Response request(const Request& req);

	Response httpRequestJson(const Request& req);
	Response httpRequestData(const Request& req);
	Response httpRequestBinary(const Request& req);

}// namespace greenapi

#endif // GREEN_API_REQUESTS_H
