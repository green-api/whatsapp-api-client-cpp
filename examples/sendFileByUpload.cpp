#include "../include/greenapi.hpp"

/*
* Example of sending file by upload from local PC
* https://green-api.com/en/docs/api/sending/SendFileByUpload/
*/
int main() {

    /*
    * Example of sending file by upload from local PC
    * You need to provide your instance details from your personal account.
    * Be sure to use the apiUrl and mediaUrl parameters specifically for the higher instance, so you will get the most stable API operation and minimal method response time.
    * https://console.green-api.com
    */
    greenapi::GreenApi instance1101000001{ "https://api.green-api.com","https://media.green-api.com","1101123456","87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80" };

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

    return 0;
}
