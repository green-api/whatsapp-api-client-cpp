#include "../include/greenapi.hpp"

/*
* Examples of sending methods working
* Rename the function to main to use
* https://green-api.com/en/docs/api/sending/
*/
int main_sending() {

	/*
	* Examples of sending methods working
	* You need to provide your instance details from your personal account.
	* Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
	* https://console.green-api.com
	*/
	greenapi::GreenApi instance1101000001{ "https://7107.api.greenapi.com","https://7107.api.greenapi.com","710701676160","36f20dae0c964139a06f9d8223ea479e3722e557bc234be2a0" };

	/*
	* Example of using the sendMessage method
	* The method is aimed for sending a text message to a personal or a group chat.
	* @param message - nlohmann::json object with message parameters
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "message","I use GREEN-API to send this message to you!" },
	{ "quotedMessageId","3EB0C767D097B7C7C030" },
	{ "linkPreview",true }
	};
	* https://green-api.com/en/docs/api/sending/SendMessage/
	*/

	nlohmann::json sendMessageJson{
		{ "chatId","71234567890@c.us" },
		{ "message","I use GREEN-API to send this message to you!" }
	};
	greenapi::Response sendMessage = instance1101000001.sending.sendMessage(sendMessageJson);

	if (sendMessage.error) {
		std::cout << "sendMessage error: {status code: " << sendMessage.status_code << ", request time: " << sendMessage.total_time << ", body: " << sendMessage.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendMessage.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* Example of using the sendPoll method
	* This method is intended for sending messages with a poll to a private or group chat.
	* @param message - nlohmann::json object with message parameters
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "message","Please choose the color:" },
		{"options", {
			{{"optionName", "green"}},
			{{"optionName", "red"}},
			{{"optionName", "blue"}}
		}},
	{ "multipleAnswers",true },
	{ "quotedMessageId","3EB0C767D097B7C7C030" }
	};
	* https://green-api.com/en/docs/api/sending/SendPoll/
	*/

	nlohmann::json sendPollJson{
		{ "chatId","71234567890@c.us" },
		{ "message","Please choose the color:" },
		{"options", {
			{{"optionName", "green"}},
			{{"optionName", "red"}},
			{{"optionName", "blue"}}
			}
		},
	};
	greenapi::Response sendPoll = instance1101000001.sending.sendPoll(sendPollJson);

	if (sendPoll.error) {
		std::cout << "sendPoll error: {status code: " << sendPoll.status_code << ", request time: " << sendPoll.total_time << ", body: " << sendPoll.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendPoll.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* Example of using the SendFileByUpload method
	* The method is aimed for sending a file uploaded by form (form-data). The message will be added to the send queue, in the response you will receive a link to the downloaded file.
	* @param file - nlohmann::json obj containing file fields
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestFile{{ "file","C:/1.png" }};
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "caption","I use GREEN-API to send this message to you!" },
	{ "fileName","1.png" },
	{ "quotedMessageId","" }
	};
	* https://green-api.com/en/docs/api/sending/SendFileByUpload/
	*/

	nlohmann::json sendFileByUploadFileJson{
	{ "file","C:/1.png" }
	};

	nlohmann::json sendFileByUploadJson{
	{ "chatId","71234567890@c.us" },
	{ "caption","I use GREEN-API to send this message to you!" },
	{ "fileName","1.png" }
	};

	greenapi::Response sendFileByUpload = instance1101000001.sending.sendFileByUpload(sendFileByUploadFileJson, sendFileByUploadJson);

	if (sendFileByUpload.error) {
		std::cout << "sendFileByUpload error: {status code: " << sendFileByUpload.status_code << ", request time: " << sendFileByUpload.total_time << ", body: " << sendFileByUpload.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendFileByUpload.bodyJson["idMessage"] << std::endl;
		std::cout << "\turlFile: " << sendFileByUpload.bodyJson["urlFile"] << "\n" << std::endl;
	}

	/*
	* Example of using the SendFileByUrl method
	* The method is aimed for sending a file uploaded by Url.
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "urlFile","https://storage/1101123456/13238852123456.png" },
	{ "fileName","1.png" },
	{ "caption","I use GREEN-API to send this message to you!" },
	{ "quotedMessageId","" }
	};
	* https://green-api.com/en/docs/api/sending/SendFileByUrl/
	*/

	nlohmann::json SendFileByUrlJson{
	{ "chatId","71234567890@c.us" },
	{ "urlFile","https://sw-media-1101.storage.yandexcloud.net/1101123456s/13238852-be73-4f8c-a973-966d2730ce15.png" },
	{ "fileName","1.png" },
	{ "caption","I use GREEN-API to send this message to you!" }
	};

	greenapi::Response sendFileByUrl = instance1101000001.sending.sendFileByUrl(SendFileByUrlJson);

	if (sendFileByUrl.error) {
		std::cout << "sendFileByUrl error: {status code: " << sendFileByUrl.status_code << ", request time: " << sendFileByUrl.total_time << ", body: " << sendFileByUrl.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendFileByUrl.bodyJson["idMessage"] << std::endl;
	}

	/*
	* Example of using the UploadFile method
	* The method is designed to upload a file to the cloud storage, which can be sent using the sendFileByUrl method.
	* @param file - nlohmann::json obj containing file fields
	* @param header - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestFile{{ "file","C:/1.png" }};
	* example json object nlohmann::json requestHeader{
	{ "GA-Filename","picture.png" },
	{ "Content-Type","image/png" }
	};
	* https://green-api.com/en/docs/api/sending/UploadFile/
	*/

	nlohmann::json uploadFileFileJson{
	{ "file","C:/1.png" }
	};

	greenapi::Response uploadFile = instance1101000001.sending.uploadFile(uploadFileFileJson);

	if (uploadFile.error) {
		std::cout << "uploadFile error: {status code: " << uploadFile.status_code << ", request time: " << uploadFile.total_time << ", header: " << uploadFile.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\turlFile: " << uploadFile.bodyJson["urlFile"] << "\n" << std::endl;
	}

	/*
	* Example of using the getFileSaveTime method
	* The method allows you to get the time of uploading a file to the GREEN API storage and its deletion
	* @param url - GREEN API link to the downloaded file
	*/
	greenapi::Response getFileSaveTime = instance1101000001.sending.getFileSaveTime("https://sw-media-out.storage.yandexcloud.net/1101123456/1234567890123456789.png");
	
	if (getFileSaveTime.error) {
		std::cout << "getFileSaveTime error: {status code: " << getFileSaveTime.status_code << ", request time: " << getFileSaveTime.total_time << ", header: " << getFileSaveTime.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tcurrentDate: " << getFileSaveTime.headers.currentDate << "\n" << std::endl;
		std::cout << "\tuploadDate: " << getFileSaveTime.headers.uploadDate << "\n" << std::endl;
		std::cout << "\texpirationDate: " << getFileSaveTime.headers.expirationDate << "\n" << std::endl;
	}

	/*
	* Example of using the SendLocation method
	* The method is aimed for sending location message.
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{"nameLocation", "nameLocation"},
	{"address", "address"},
	{"latitude", 20.24},
	{"longitude", 20.24},
	{ "quotedMessageId","" }
	};
	* https://green-api.com/en/docs/api/sending/SendLocation/
	*/

	nlohmann::json sendLocationJson{
	{ "chatId","71234567890@c.us" },
	{"nameLocation", "nameLocation"},
	{"address", "address"},
	{"latitude", 20.24},
	{"longitude", 20.24}
	};

	greenapi::Response sendLocation = instance1101000001.sending.sendLocation(sendLocationJson);

	if (sendLocation.error) {
		std::cout << "sendLocation error: {status code: " << sendLocation.status_code << ", request time: " << sendLocation.total_time << ", body: " << sendLocation.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendLocation.bodyJson["idMessage"] << std::endl;
	}

	/*
	* Example of using the SendContact method
	* The method is aimed for sending a contact message.
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{"contact", {
		{{"phoneContact", 71234567890}},
		{{"firstName", "firstName"}},
		{{"middleName", "middleName"}},
		{{"lastName", "lastName"}},
		{{"company", "company"}}
		}
	},
	{ "quotedMessageId","" }
	};
	* https://green-api.com/en/docs/api/sending/SendContact/
	*/

	nlohmann::json sendContactJson{
	{ "chatId","71234567890@c.us" },
	{"contact", {
		{"phoneContact", 71234567890},
		{"firstName", "firstName"},
		{"middleName", "middleName"},
		{"lastName", "lastName"},
		{"company", "company"}
		}
	}
	};

	greenapi::Response sendContact = instance1101000001.sending.sendContact(sendContactJson);

	if (sendContact.error) {
		std::cout << "sendContact error: {status code: " << sendContact.status_code << ", request time: " << sendContact.total_time << ", body: " << sendContact.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendContact.bodyJson["idMessage"] << std::endl;
	}

	/*
	* Example of using the ForwardMessages method
	* The method is intended for forwarding messages to a personal or group chat.
	* @param text - nlohmann::json obj containing text fields
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "chatIdFrom","71234567890@c.us" },
	{"messages", {
			"BAE5DBB8DEABDA22",
			"BAE5BBA9BE3142D8"
		}
	}
	};
	* https://green-api.com/en/docs/api/sending/ForwardMessages/
	*/

	nlohmann::json forwardMessagesJson{
	{ "chatId","71234567890@c.us" },
	{ "chatIdFrom","71234567890@c.us" },
	{"messages", {
			"optionName",
			"optionName"
		}
	}
	};

	greenapi::Response forwardMessages = instance1101000001.sending.forwardMessages(forwardMessagesJson);

	if (forwardMessages.error) {
		std::cout << "forwardMessages error: {status code: " << forwardMessages.status_code << ", request time: " << forwardMessages.total_time << ", body: " << forwardMessages.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tmessages: " << forwardMessages.bodyJson["messages"] << std::endl;
	}

	/*
	* Example of using the sendInteractiveButtons method
	* The method is aimed for sending a message with interactive buttons (types: copy, call, url) to a personal chat.
	* Up to 3 buttons per message, button text up to 25 characters.
	* @param message - nlohmann::json object with message parameters
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "header","Header text" },
	{ "body","Message body text" },
	{ "footer","Footer text" },
	{ "buttons", {
		{{"type","url"}, {"buttonId","1"}, {"buttonText","Open website"}, {"url","https://green-api.com"}},
		{{"type","call"}, {"buttonId","2"}, {"buttonText","Call us"}, {"phoneNumber","71234567890"}},
		{{"type","copy"}, {"buttonId","3"}, {"buttonText","Copy code"}, {"copyCode","ABC123"}}
		}
	}
	};
	* https://green-api.com/en/docs/api/sending/SendInteractiveButtons/
	*/

	nlohmann::json sendInteractiveButtonsJson{
		{ "chatId","71234567890@c.us" },
		{ "header","Choose an action" },
		{ "body","Press the button you need" },
		{ "footer","GREEN API" },
		{ "buttons", {
			{{"type","url"}, {"buttonId","1"}, {"buttonText","Open website"}, {"url","https://green-api.com"}},
			{{"type","call"}, {"buttonId","2"}, {"buttonText","Call us"}, {"phoneNumber","71234567890"}},
			{{"type","copy"}, {"buttonId","3"}, {"buttonText","Copy code"}, {"copyCode","ABC123"}}
			}
		}
	};

	greenapi::Response sendInteractiveButtons = instance1101000001.sending.sendInteractiveButtons(sendInteractiveButtonsJson);

	if (sendInteractiveButtons.error) {
		std::cout << "sendInteractiveButtons error: {status code: " << sendInteractiveButtons.status_code << ", request time: " << sendInteractiveButtons.total_time << ", body: " << sendInteractiveButtons.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendInteractiveButtons.bodyJson["idMessage"] << "\n" << std::endl;
	}

	/*
	* Example of using the sendInteractiveButtonsReply method
	* The method is aimed for sending a message with reply buttons (text buttons, each can be pressed once) to a personal chat.
	* Up to 3 buttons per message, button text up to 25 characters. Beta version.
	* @param message - nlohmann::json object with message parameters
	* example json object nlohmann::json requestMessage{
	{ "chatId","71234567890@c.us" },
	{ "header","Survey" },
	{ "body","Do you like our service?" },
	{ "footer","Choose one option" },
	{ "buttons", {
		{{"buttonId","1"}, {"buttonText","Yes"}},
		{{"buttonId","2"}, {"buttonText","No"}},
		{{"buttonId","3"}, {"buttonText","Not sure"}}
		}
	}
	};
	* https://green-api.com/en/docs/api/sending/SendInteractiveButtonsReply/
	*/

	nlohmann::json sendInteractiveButtonsReplyJson{
		{ "chatId","71234567890@c.us" },
		{ "header","Survey" },
		{ "body","Do you like our service?" },
		{ "footer","Choose one option" },
		{ "buttons", {
			{{"buttonId","1"}, {"buttonText","Yes"}},
			{{"buttonId","2"}, {"buttonText","No"}},
			{{"buttonId","3"}, {"buttonText","Not sure"}}
			}
		}
	};

	greenapi::Response sendInteractiveButtonsReply = instance1101000001.sending.sendInteractiveButtonsReply(sendInteractiveButtonsReplyJson);

	if (sendInteractiveButtonsReply.error) {
		std::cout << "sendInteractiveButtonsReply error: {status code: " << sendInteractiveButtonsReply.status_code << ", request time: " << sendInteractiveButtonsReply.total_time << ", body: " << sendInteractiveButtonsReply.bodyStr << "}" << "\n" << std::endl;
	}
	else {
		std::cout << "\tidMessage: " << sendInteractiveButtonsReply.bodyJson["idMessage"] << "\n" << std::endl;
	}

	return 0;
}
