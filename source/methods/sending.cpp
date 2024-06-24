#include "../../../whatsapp-api-client-cpp/include/methods/sending.hpp"

namespace greenapi
{

	Sending::Sending() {
		Logger::getInstance().log(std::string("Creating Sending class without parameters"), "error");
	};

	Sending::Sending(
		const std::string& apiUrl,
		const std::string& mediaUrl,
		const std::string& idInstance,
		const std::string& apiTokenInstance)
		: apiUrl(&apiUrl), mediaUrl(&mediaUrl), idInstance(&idInstance), apiTokenInstance(&apiTokenInstance) {

		Logger::getInstance().log(std::string("Creating Sending class with parameters {apiUrl:" + *(this->apiUrl) + ", mediaUrl : " + *(this->mediaUrl)\
			+ ", idInstance : " + *(this->idInstance) + ", apiTokenInstance : " + Logger::getInstance().hideStringPart(*(this->apiTokenInstance), 0, 10) + "}"), "info");
	};

	Response Sending::sendMessage(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "message","" } };

		// Checking the chatId and message fields
		if (!message.contains("chatId") || !message.contains("message")) {
			response.bodyStr = "Required chatId or message fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		requestMessage["chatId"] = message["chatId"];
		requestMessage["message"] = message["message"];

		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				requestMessage["quotedMessageId"] = message["quotedMessageId"];
			}
		}

		// Checking the linkPreview
		if (message.contains("linkPreview")) {
			requestMessage["linkPreview"] = message["linkPreview"];
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendMessage/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::sendPoll(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "message","" }, { "options","" } };

		// Checking the chatId, message or options fields
		if (!message.contains("chatId") || !message.contains("message") || !message.contains("options")) {
			response.bodyStr = "Required chatId, message or options fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (!message["options"].is_array()) {
			response.bodyStr = "The key 'options' does not exist or is not an array.";
			return response;
		}
		if (message["options"].size() > 12 || message["options"].size() < 2) {
			response.bodyStr = "The number of options cannot exceed 12 and more than 1";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["message"] = message["message"];
		requestMessage["options"] = message["options"];

		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				requestMessage["quotedMessageId"] = message["quotedMessageId"];
			}
		}

		// Checking the multipleAnswers
		if (message.contains("multipleAnswers")) {
			requestMessage["multipleAnswers"] = message["multipleAnswers"];
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendPoll/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::sendFileByUpload(const nlohmann::json file, const nlohmann::json message) {

		Response response;
		nlohmann::json body{ { "chatId","" } };
		nlohmann::json bodyFile{ { "file","" } };

		// Checking the chatId, message or options fields
		if (!message.contains("chatId") || !file.contains("file")) {
			response.bodyStr = "Required chatId or file fields are missing";
			return response;
		}

		bodyFile["file"] = file["file"].get<std::string>();

		body["chatId"] = message["chatId"];

		if (message.contains("caption")) {
			body["caption"] = message["caption"];
		}
		if (message.contains("fileName")) {
			body["fileName"] = message["fileName"];
		}
		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				body["quotedMessageId"] = message["quotedMessageId"];
			}
		}

		std::string url = *(this->mediaUrl) + "/waInstance" + *(this->idInstance) + "/sendFileByUpload/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , body, bodyFile, "data" };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::sendFileByUrl(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "urlFile","" }, { "fileName","" } };

		// Checking the chatId, message or options fields
		if (!message.contains("chatId") || !message.contains("urlFile") || !message.contains("fileName")) {
			response.bodyStr = "Required chatId, urlFile or fileName fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (message["urlFile"].get<std::string>().size() < 8) {
			response.bodyStr = "urlFile must be longer than 8 characters";
			return response;
		}
		if (message["fileName"].get<std::string>().find('.') == std::string::npos) {
			response.bodyStr = "To send a file correctly, fileName must have a dot and an indication of the file extension, for example \"picture.jpg\"";
			return response;
		}
		if (message["fileName"].get<std::string>().size() < 3) {
			response.bodyStr = "To send a file correctly, fileName must have the file name and extension, for example \"picture.jpg\"";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["urlFile"] = message["urlFile"];
		requestMessage["fileName"] = message["fileName"];

		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				requestMessage["quotedMessageId"] = message["quotedMessageId"];
			}
		}

		// Checking the caption
		if (message.contains("caption")) {
			requestMessage["caption"] = message["caption"];
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendFileByUrl/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}

	}

	Response Sending::uploadFile(const nlohmann::json file, const nlohmann::json header) {

		Response response;
		nlohmann::json bodyHeader;
		nlohmann::json bodyFile{ { "file","" } };

		// Checking the file field
		if (!file.contains("file")) {
			response.bodyStr = "Required file field are missing";
			return response;
		}

		bodyFile["file"] = file["file"].get<std::string>();

		if (header.contains("Content-Type")) {
			bodyHeader["Content-Type"] = header["Content-Type"];
		}
		else {
			bodyHeader["Content-Type"] = getMimeTypes("." + Sending::getAfterDot(file["file"].get<std::string>()));
		}
		if (header.contains("GA-Filename")) {
			bodyHeader["GA-Filename"] = header["GA-Filename"];
		}
		else {
			bodyHeader["GA-Filename"] = "name." + Sending::getAfterDot(file["file"].get<std::string>());
		}

		std::string url = *(this->mediaUrl) + "/waInstance" + *(this->idInstance) + "/uploadFile/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , bodyHeader, bodyFile, "binary" };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::getFileSaveTime(const std::string url) {

		Response response;

		if (url =="") {
			response.bodyStr = "The link to the file in the GREEN API repository is not specified";
			return response;
		}

		Request req{ url, "HTTP", "HEAD" };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::sendLocation(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "latitude",0.0 },  { "longitude",0.0 } };

		// Checking the chatId, contact fields
		if (!message.contains("chatId") || !message.contains("latitude") || !message.contains("longitude")) {
			response.bodyStr = "Required chatId, latitude or longitude fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["latitude"] = message["latitude"];
		requestMessage["longitude"] = message["longitude"];

		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				requestMessage["quotedMessageId"] = message["quotedMessageId"];
			}
		}
		// Checking the nameLocation field
		if (message.contains("nameLocation")) {
			requestMessage["nameLocation"] = message["nameLocation"];
		}
		// Checking the address field
		if (message.contains("address")) {
			requestMessage["address"] = message["address"];
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendLocation/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::sendContact(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "contact","" } };

		// Checking the chatId, contact fields
		if (!message.contains("chatId") || !message.contains("contact")) {
			response.bodyStr = "Required chatId, contact fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (!message["contact"].contains("phoneContact")) {
			response.bodyStr = "Required phoneContact field are missing";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["contact"] = message["contact"];

		// Checking the quotedMessageId field
		if (message.contains("quotedMessageId")) {

			if (message["quotedMessageId"].get<std::string>().size() < 5) {
				response.bodyStr = "Filed quotedMessageId field are missing or incorrect format";
				return response;
			}
			if (message["quotedMessageId"].get<std::string>() != "") {
				requestMessage["quotedMessageId"] = message["quotedMessageId"];
			}
		}

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/sendContact/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	Response Sending::forwardMessages(const nlohmann::json message) {

		Response response;
		nlohmann::json requestMessage{ { "chatId","" },  { "chatIdFrom","" }, { "messages","" } };

		// Checking the chatId, message or options fields
		if (!message.contains("chatId") || !message.contains("chatIdFrom") || !message.contains("messages")) {
			response.bodyStr = "Required chatId, chatIdFrom or messages fields are missing";
			return response;
		}
		if (message["chatId"].get<std::string>().find('@') == std::string::npos) {
			response.bodyStr = "The required @ symbol is lost in the chatId variable";
			return response;
		}
		if (message["chatId"].get<std::string>().size() < 11) {
			response.bodyStr = "chatId is not correct, the required chatId format for individual chat is XXXXXXXXXXX@c.us, group chatId XXXXXXXXXX-XXXXXXXXXX@g.us or XXXXXXXXXXXXXXXXX@g.us";
			return response;
		}
		if (!message["messages"].is_array()) {
			response.bodyStr = "The key 'messages' does not exist or is not an array.";
			return response;
		}
		if (message["messages"].size() < 1) {
			response.bodyStr = "The number of messages must be more than 1";
			return response;
		}

		requestMessage["chatId"] = message["chatId"];
		requestMessage["chatIdFrom"] = message["chatIdFrom"];
		requestMessage["messages"] = message["messages"];

		std::string url = *(this->apiUrl) + "/waInstance" + *(this->idInstance) + "/forwardMessages/" + *(this->apiTokenInstance);

		Request req{ url, "HTTP", "POST" , requestMessage };

		try {
			return request(req);
		}
		catch (const std::runtime_error& e) {

			std::cerr << "Error: " << e.what() << std::endl;
			Logger::getInstance().log(std::string(e.what()), "error");
			response.error = true;
			response.bodyStr = std::string(e.what());
			return response;
		}
	}

	std::string Sending::getAfterDot(const std::string& input) {
		size_t pos = input.find('.');
		if (pos != std::string::npos) {
			return input.substr(pos + 1);
		}
		return "";
	}

}// namespace greenapi