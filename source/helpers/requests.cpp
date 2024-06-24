#include "../../../whatsapp-api-client-cpp/include/helpers/requests.hpp"


namespace greenapi {

	size_t inline WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	size_t headerCallback(char* buffer, size_t size, size_t nitems, std::map<std::string, std::string>* headers) {
		size_t totalSize = size * nitems;
		std::string header(buffer, totalSize);

		size_t colonPos = header.find(':');
		if (colonPos != std::string::npos) {
			std::string key = header.substr(0, colonPos);
			std::string value = header.substr(colonPos + 1);

			key.erase(0, key.find_first_not_of(" \t\r\n"));
			key.erase(key.find_last_not_of(" \t\r\n") + 1);
			value.erase(0, value.find_first_not_of(" \t\r\n"));
			value.erase(value.find_last_not_of(" \t\r\n") + 1);

			headers->emplace(key, value);
		}
		return totalSize;
	}

	std::string readFileToString(const std::string& filePath) {
		std::ifstream file(filePath, std::ios::binary);
		std::ostringstream oss;
		oss << file.rdbuf();
		return oss.str();
	}

	Response request(const Request& request) {

		Response response;

		if (request.protocol == "HTTP") {

			if (request.headers.contentType == "json") {
				return httpRequestJson(request);
			}
			else if (request.headers.contentType == "data") {
				return httpRequestData(request);
			}
			else if (request.headers.contentType == "binary") {
				return httpRequestBinary(request);

			}
			else {
				response.bodyStr = "Unsupported request body (application/json, multipart/form-data, binary)";
				Logger::getInstance().log(std::string(response.bodyStr), "error");
				throw std::runtime_error(response.bodyStr);
				return response;
			}

		}
		else {
			response.bodyStr = "Unsupported protocol type (http only)";
			Logger::getInstance().log(std::string(response.bodyStr), "error");
			throw std::runtime_error(response.bodyStr);
			return response;
		}

	}

	Response httpRequestJson(const Request& request) {

		CURL* curl;
		CURLcode res;
		Response response;

		if (request.type == "GET" || request.type == "DELETE") {

			curl = curl_easy_init();

			if (!curl) {
				response.bodyStr = "Failed to initialize cURL";
				Logger::getInstance().log(std::string(response.bodyStr), "error");
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.type.c_str());
			// Установка URL для GET-запроса
			curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());

			// Установка заголовков для JSON
			struct curl_slist* headers = nullptr;
			headers = curl_slist_append(headers, "Content-Type: application/json");
			headers = curl_slist_append(headers, ("User-Agent: " + request.headers.userAgent).c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			// Установка функции обратного вызова для записи данных
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.bodyStr);

			// Установка времени ожидания
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, GA_CURLOPT_TIMEOUT);
			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, GA_CURLOPT_CONNECTTIMEOUT);

			// Выполнение запроса
			res = curl_easy_perform(curl);

			// Проверка на ошибки
			if (res != CURLE_OK) {
				response.bodyStr = std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res);
				Logger::getInstance().log(response.bodyStr, "error");
				curl_slist_free_all(headers);
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}

			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response.total_time);

			Logger::getInstance().log(std::string(request.type + " " + request.url + " request body: " + request.body.dump() + " response state: {status_code: "\
				+ std::to_string(response.status_code) + ", total_time: " + std::to_string(response.total_time) + ", body: " + response.bodyStr + "};"), response.status_code >= 400 ? "error" : "debug");

			// Очистка ресурсов
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);

			if (response.status_code < 400) {
				response.error = false;
				if (response.bodyStr != "") { response.bodyJson = nlohmann::json::parse(response.bodyStr); }
			}

			return response;
		}
		else if (request.type == "POST") {

			curl = curl_easy_init();

			if (!curl) {
				response.bodyStr = "Failed to initialize cURL";
				Logger::getInstance().log(std::string(response.bodyStr), "error");
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}

			curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());

			struct curl_slist* headers = nullptr;
			headers = curl_slist_append(headers, "Content-Type: application/json");
			headers = curl_slist_append(headers, ("User-Agent: " + request.headers.userAgent).c_str());
			headers = curl_slist_append(headers, "Connection: keep-alive");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			std::string body = request.body.dump();
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.bodyStr);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, GA_CURLOPT_TIMEOUT);
			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, GA_CURLOPT_CONNECTTIMEOUT);

			res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				curl_easy_cleanup(curl);
				response.bodyStr = std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res);
				Logger::getInstance().log(response.bodyStr, "error");
				curl_slist_free_all(headers);
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}

			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response.total_time);

			Logger::getInstance().log(std::string(request.type + " " + request.url + " request body: " + request.body.dump() + " response state: {status_code: "\
				+ std::to_string(response.status_code) + ", total_time: " + std::to_string(response.total_time) + ", body: " + response.bodyStr + "};"), response.status_code >= 400 ? "error" : "debug");

			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);

			if (response.status_code < 400) {
				response.error = false;
				if (response.bodyStr != "") { response.bodyJson = nlohmann::json::parse(response.bodyStr); }
			}

			return response;
		}
		else if (request.type == "HEAD") {

			curl = curl_easy_init();
			std::map<std::string, std::string> responseHeaders;

			if (!curl) {
				response.bodyStr = "Failed to initialize cURL";
				Logger::getInstance().log(std::string(response.bodyStr), "error");
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}
			curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());
			curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeaders);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, GA_CURLOPT_TIMEOUT);
			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, GA_CURLOPT_CONNECTTIMEOUT);

			res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				response.bodyStr = std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res);
				Logger::getInstance().log(response.bodyStr, "error");
				curl_easy_cleanup(curl);
				throw std::runtime_error(response.bodyStr);
				return response;
			}

			if (responseHeaders.find("Date") != responseHeaders.end()) {
				response.headers.currentDate = responseHeaders["Date"];
			}
			if (responseHeaders.find("date") != responseHeaders.end()) {
				response.headers.currentDate = responseHeaders["date"];
			}
			if (responseHeaders.find("Last-Modified") != responseHeaders.end()) {
				response.headers.uploadDate = responseHeaders["Last-Modified"];
			}
			if (responseHeaders.find("last-modified") != responseHeaders.end()) {
				response.headers.uploadDate = responseHeaders["last-modified"];
			}
			if (responseHeaders.find("X-Amz-Expiration") != responseHeaders.end()) {
				response.headers.expirationDate = responseHeaders["X-Amz-Expiration"];
				std::regex dateRegex(R"(expiry-date=\"([^\"]+)\"(?:,|$))");
				std::smatch match;
				if (std::regex_search(response.headers.expirationDate, match, dateRegex) && match.size() > 1) { response.headers.expirationDate = match.str(1); }
			}
			if (responseHeaders.find("x-amz-expiration") != responseHeaders.end()) {
				response.headers.expirationDate = responseHeaders["x-amz-expiration"];
				std::regex dateRegex(R"(expiry-date=\"([^\"]+)\"(?:,|$))");
				std::smatch match;
				if (std::regex_search(response.headers.expirationDate, match, dateRegex) && match.size() > 1) { response.headers.expirationDate = match.str(1); }
			}

			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response.total_time);

			Logger::getInstance().log(std::string(request.type + " " + request.url + " response state: {status_code: "\
				+ std::to_string(response.status_code) + ", total_time: " + std::to_string(response.total_time) + ", body: "\
				+ response.bodyStr + ", currentDate: " + response.headers.currentDate + ", uploadDate: " + response.headers.uploadDate\
				+ ", expirationDate: " + response.headers.expirationDate + "};"), response.status_code >= 400 ? "error" : "debug");

			curl_easy_cleanup(curl);

			if (response.status_code < 400) {
				response.error = false;
			}

			return response;
		}
		else {
			response.bodyStr = "Unsupported request type (GET, POST, HEAD, DELETE only)";
			Logger::getInstance().log(response.bodyStr, "error");
			throw std::runtime_error(response.bodyStr);
			return response;
		}
	}

	Response httpRequestData(const Request& request) {

		CURL* curl;
		CURLcode res;
		curl_mime* mime;
		Response response;

		curl = curl_easy_init();

		if (!curl) {
			response.bodyStr = "Failed to initialize cURL";
			Logger::getInstance().log(std::string(response.bodyStr), "error");
			curl_easy_cleanup(curl);
			throw std::runtime_error(response.bodyStr);
			return response;
		}

		curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());

		mime = curl_mime_init(curl);

		if (!request.body.empty()) {
			for (auto i = request.body.begin(); i != request.body.end(); ++i) {
				std::cout << "Field name: " << i.key() << ", Field value: " << i.value().dump() << std::endl;

				std::string key = i.key();
				std::string value = i.value();

				curl_mimepart* part = curl_mime_addpart(mime);
				curl_mime_name(part, key.c_str());
				curl_mime_data(part, value.c_str(), CURL_ZERO_TERMINATED);
			}
		}
		if (!request.bodyFile.empty()) {
			for (auto i = request.bodyFile.begin(); i != request.bodyFile.end(); ++i) {
				std::cout << "Field name: " << i.key() << ", Field value: " << i.value().dump() << std::endl;

				std::string key = i.key();
				std::string value = i.value();

				curl_mimepart* part = curl_mime_addpart(mime);
				curl_mime_name(part, key.c_str());
				curl_mime_filedata(part, value.c_str());
			}
		}
		else {
			response.bodyStr = "Failed bodyFile is missing";
			Logger::getInstance().log(std::string(response.bodyStr), "error");
			curl_easy_cleanup(curl);
			curl_mime_free(mime);
			throw std::runtime_error(response.bodyStr);
			return response;
		}

		curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.bodyStr);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, GA_CURLOPT_TIMEOUT);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, GA_CURLOPT_CONNECTTIMEOUT);

		if (CURL_LOG) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			curl_easy_cleanup(curl);
			response.bodyStr = std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res);
			Logger::getInstance().log(response.bodyStr, "error");
			curl_easy_cleanup(curl);
			curl_mime_free(mime);
			throw std::runtime_error(response.bodyStr);
			return response;
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

		curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response.total_time);

		Logger::getInstance().log(std::string(request.type + " " + request.url + " request body: " + request.body.dump() + " response state: {status_code: "\
			+ std::to_string(response.status_code) + ", total_time: " + std::to_string(response.total_time) + ", body: " + response.bodyStr + "};"), response.status_code >= 400 ? "error" : "debug");

		curl_easy_cleanup(curl);
		curl_mime_free(mime);

		if (response.status_code < 400) {
			response.error = false;
			response.bodyJson = nlohmann::json::parse(response.bodyStr);
		}

		return response;
	}

	Response httpRequestBinary(const Request& request) {
		CURL* curl;
		CURLcode res;
		Response response;

		curl = curl_easy_init();

		if (!curl) {
			response.bodyStr = "Failed to initialize cURL";
			Logger::getInstance().log(response.bodyStr, "error");
			throw std::runtime_error(response.bodyStr);
		}

		curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());

		struct curl_slist* headers = nullptr;

		std::string contentType = "Content-Type: " + request.body["Content-Type"].get<std::string>();
		std::string gaFilename = "GA-Filename: " + request.body["GA-Filename"].get<std::string>();

		headers = curl_slist_append(headers, ("User-Agent: " + request.headers.userAgent).c_str());
		headers = curl_slist_append(headers, contentType.c_str());
		headers = curl_slist_append(headers, gaFilename.c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		std::string bodyFile = request.bodyFile["file"].get<std::string>();
		std::string fileContents = readFileToString(bodyFile);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fileContents.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fileContents.size());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.bodyStr);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, GA_CURLOPT_TIMEOUT);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, GA_CURLOPT_CONNECTTIMEOUT);

		if (CURL_LOG) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			response.bodyStr = "curl_easy_perform() failed: " + std::string(curl_easy_strerror(res));
			Logger::getInstance().log(response.bodyStr, "error");
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);
			throw std::runtime_error(response.bodyStr);
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

		curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response.total_time);

		Logger::getInstance().log(
			request.type + " " + request.url + ", request body file: " + request.bodyFile.dump() + ", request body: " + request.body.dump() + ", response state: {status_code: " +
			std::to_string(response.status_code) + ", total_time: " + std::to_string(response.total_time) + ", body: " + response.bodyStr + "};",
			response.status_code >= 400 ? "error" : "debug");

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);

		if (response.status_code < 400) {
			response.error = false;
			response.bodyJson = nlohmann::json::parse(response.bodyStr);
		}

		return response;
	}
};// namespace greenapi