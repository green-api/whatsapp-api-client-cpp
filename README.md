# whatsapp-api-client-cpp

![](https://img.shields.io/badge/license-CC%20BY--ND%204.0-green)

## Support links

[![Support](https://img.shields.io/badge/support@green--api.com-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:support@green-api.com)
[![Support](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/greenapi_support_ru_bot)
[![Support](https://img.shields.io/badge/WhatsApp-25D366?style=for-the-badge&logo=whatsapp&logoColor=white)](https://wa.me/447458038017)

## Guides & News

[![Guides](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://www.youtube.com/@greenapi-en)
[![News](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/green_api)
[![News](https://img.shields.io/badge/WhatsApp-25D366?style=for-the-badge&logo=whatsapp&logoColor=white)](https://whatsapp.com/channel/0029VaLj6J4LNSa2B5Jx6s3h)

- [Документация на русском языке](https://github.com/green-api/whatsapp-api-client-cpp/blob/master/README.ru.md).

`whatsapp-api-client-cpp` - library for integration with WhatsApp messenger using the API service [green-api.com](https://green-api.com/). 
You should get a registration token and an account ID in your [personal cabinet](https://console.green-api.com/). 
There is a free developer account tariff.

- [whatsapp-api-client-cpp](#whatsapp-api-client-cpp)
  - [Support links](#support-links)
  - [Guides \& News](#guides--news)
  - [API](#api)
  - [Authorization](#authorization)
  - [Installation](#installation)
    - [Windows](#windows)
      - [Windows x64](#windows-x64)
  - [Building the library](#building-the-library)
    - [Windows](#windows-1)
    - [Importing the library](#importing-the-library)
    - [Linux](#linux)
  - [Examples](#examples)
    - [How to initialize an object](#how-to-initialize-an-object)
    - [Sending a text message example](#sending-a-text-message-example)
    - [Working with library examples](#working-with-library-examples)
  - [Examples list](#examples-list)
  - [Full list of all methods](#full-list-of-all-methods)
  - [Service methods documentation](#service-methods-documentation)
  - [Library dependencies](#library-dependencies)
  - [Licence](#licence)

## API

The documentation for the REST API can be found at the [link](https://green-api.com/en/docs/api/). The library is a wrapper for the REST API, so the documentation at the link above also applies.

## Authorization

To send a message or perform other GREEN API methods, the WhatsApp account in the phone app must be authorized. To authorize the account, go to your [cabinet](https://console.green-api.com/) and scan the QR code using the WhatsApp app.

## Installation

This library uses C++ 17, supports Linux (GCC) and Windows (Visual Studio 2019/2022) compilers.

Clone library repository

```bash
git clone https://github.com/green-api/whatsapp-api-client-cpp.git
```

### Windows

Installing dependencies using `vcpkg` package manager:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install curl
vcpkg install nlohmann-json
# vcpkg install websocketpp (optional)
vcpkg integrate install
```

#### Windows x64

Most Windows machines now have x64 version, but `vcpkg` uses x86 packages by default.

```bash
vcpkg install nlohmann-json:x64-windows
vcpkg install curl:x64-windows
```

> To execute commands in PowerShell it is required to change commands to .\\vcpkg

After building `bootstrap-vcpkg.bat` it is required to **add `vcpkg.exe` into the PATH variables of your system** `PATH\vcpkg\installed\x64-windows\bin`.

## Building the library

### Windows

To build the library you need:

- [CMake](https://cmake.org/download/) - a cross-platform utility for automatically building software from source code.
- Compiler [Microsoft Visual C++ (MSVC)](https://visualstudio.microsoft.com/ru/downloads/) for C++ applications.

Building the library using CMake and Visual Studio compiler

Building is done by using the **build.bat** scenario or manually by using CMake (compiling Debug version of the library):


```bash
mkdir build
cd build
cmake ..
cd ../
cmake --build build
```

> Most likely you will have to specify direct paths to the used libraries, uncomment the lines in [CMakeList.txt](./CMakeLists.txt)

### Importing the library

You can import the library in Visual Studio 
by adding the `whatsapp-api-client-cpp.lib` file in the project dependencies:

1. Properties->Configuration properties->C/C++->General->Additional Include Directories (PATH/whatsapp-api-client-cpp/include)
2. Properties->Configuration properties->Linker->General->Additional Library Directories (PATH/build/)
3. Properties->Configuration properties->Linker->Inpit->Additional Dependencies (whatsapp-api-client-cpp.lib)

> Carefully choose your configuration type and install required library version (debug and release)

### Linux

Installing dependencies with `vcpkg` package manager:

- Dependencies
  - curl
  - nlohmann-json
  - websocketpp (optional)

You can install dependencies with ready-made **install.sh** scenario (`sudo sh install.sh`) or manually:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg/vcpkg install curl
./vcpkg/vcpkg install nlohmann-json
# ./vcpkg install websocketpp (optional)
./vcpkg/vcpkg integrate install
```

You can build the library with ready-made **build.sh** scenario (`sudo sh build.sh`) or manually:

```bash
mkdir build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build/

```

> You can change vcpkg catalogue by specifying relative or absolute path.

You might need to install additional packages to build the library:

```sh
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install g++
sudo apt-get install pkg-config
sudo apt-get install libcurl4-openssl-dev
sudo apt install build-essential
```

## Examples

### How to initialize an object

To initialize an object it is required to use apiUrl and mediaUrl parameters specifically for your instance from your [personal cabinet](https://console.green-api.com/), that way you will get the most stable API work and minimal response time.

```cpp
greenapi::GreenApi instance1101000001{
    "https://api.green-api.com",
    "https://media.green-api.com",
    "1101123456",
    "87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80"
    };
```

### Sending a text message example
Link to the example: [main.cpp](./main.cpp).

```cpp
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
```

### Working with library examples

All examples are put in the examples folder, every file has examples of all the methods with all the supported parameters
To run a particular example it is required to copy a code section into your main.cpp file and use your values in the parameters.

## Examples list

| Description                                 | Module                                                        |
| ------------------------------------------- | ------------------------------------------------------------- |
| Sending a text example                      | [main.cpp](./main.cpp)                                        |
| Examples of account methods                 | [test_accaunt.cpp](./examples/test_accaunt.cpp)               |
| Examples of sending methods                 | [test_sending.cpp](./examples/test_sending.cpp)               |
| Examples of receiving methods               | [test_receiving.cpp](./examples/test_receiving.cpp)           |
| Examples of journal methods                 | [test_journals.cpp](./examples/test_journals.cpp)             |
| Examples of queue methods                   | [test_queues.cpp](./examples/test_queues.cpp)                 |
| Examples of group methods                   | [test_groups.cpp](./examples/test_groups.cpp)                 |
| Examples of status methods                  | [test_statuses.cpp](./examples/test_statuses.cpp)             |
| Examples of read mark methods               | [test_readMark.cpp](./examples/test_readMark.cpp)             |
| Examples of service methods                 | [test_serviceMethods.cpp](./examples/test_serviceMethods.cpp) |

## Full list of all methods

| API Method              | Description                  | Documentation link                       |
| ---------------------- | ------------------------- | ---------------------------------------- |
| `account.getSettings`                | Method for getting current settings of the account                                                                | [GetSettings](https://green-api.com/en/docs/api/account/GetSettings/)                                       |
| `account.getWaSettings`              | Method for getting information of the WhatsApp account                                                           | [GetWaSettings](https://green-api.com/en/docs/api/account/GetWaSettings/)                                   |
| `account.setSettings`                | Method to set account                                                                        | [SetSettings](https://green-api.com/en/docs/api/account/SetSettings/)                                       |
| `account.getStateInstance`           | Method for getting the account state                                                                       | [GetStateInstance](https://green-api.com/en/docs/api/account/GetStateInstance/)                             |
| `account.getStatusInstance`          | Method for getting socket connection state of the account with WhatsApp                                 | [GetStatusInstance](https://green-api.com/en/docs/api/account/GetStatusInstance/)                           |
| `account.reboot`                     | Method for restarting the account                                                                               | [Reboot](https://green-api.com/en/docs/api/account/Reboot/)                                                 |
| `account.logout`                     | Method for logging out                                                                            | [Logout](https://green-api.com/en/docs/api/account/Logout/)                                                 |
| `account.qr`                         | Method for getting a QR code                                                                                  | [QR](https://green-api.com/en/docs/api/account/QR/)                                                         |
| `account.setProfilePicture`          | Method for setting a profile picture                                                                         | [SetProfilePicture](https://green-api.com/en/docs/api/account/SetProfilePicture/)                           |
| `account.getAuthorizationCode`       | Method for authorizing by phone number                                                       | [GetAuthorizationCode](https://green-api.com/en/docs/api/account/GetAuthorizationCode/)                     |
| `device.getDeviceInfo`               | Method for getting information about the device (phone) on which the WhatsApp Business application is running    | [GetDeviceInfo](https://green-api.com/en/docs/api/phone/GetDeviceInfo/)                                     |
| `groups.createGroup`                 | Method for creating a group chat                                                                           | [CreateGroup](https://green-api.com/en/docs/api/groups/CreateGroup/)                                        |
| `groups.updateGroupName`             | Method for changing a group chat name                                                                               | [UpdateGroupName](https://green-api.com/en/docs/api/groups/UpdateGroupName/)                                |
| `groups.getGroupData`                | Method for getting a group chat data                                                                                     | [GetGroupData](https://green-api.com/en/docs/api/groups/GetGroupData/)                                      |
| `groups.addGroupParticipant`         | Method for adding a participant into a group chat                                                                                 | [AddGroupParticipant](https://green-api.com/en/docs/api/groups/AddGroupParticipant/)                        |
| `groups.removeGroupParticipant`      | Method for deleting a participant from a group chat                                                                                | [RemoveGroupParticipant](https://green-api.com/en/docs/api/groups/RemoveGroupParticipant/)                  |
| `groups.setGroupAdmin`               | Method for setting a participant as a group administrator                                                                 | [SetGroupAdmin](https://green-api.com/en/docs/api/groups/SetGroupAdmin/)                                    |
| `groups.removeAdmin`                 | Method for removing administrator rights from a participant                                                             | [RemoveAdmin](https://green-api.com/en/docs/api/groups/RemoveAdmin/)                                        |
| `groups.setGroupPicture`             | Method for setting a group picture                                                                                         | [SetGroupPicture](https://green-api.com/en/docs/api/groups/SetGroupPicture/)                                |
| `groups.leaveGroup`                  | Method for leaving from a group                                                  | [LeaveGroup](https://green-api.com/en/docs/api/groups/LeaveGroup/)                                          |
| `journals.getChatHistory`            | Method for getting a chat history                                                                                   | [GetChatHistory](https://green-api.com/en/docs/api/journals/GetChatHistory/)                                |
| `journals.getMessage`                | Method for getting a message                                                                                            | [GetMessage](https://green-api.com/en/docs/api/journals/GetMessage/)                                        |
| `journals.lastIncomingMessages`      | Method for getting last incoming messages                                                                      | [LastIncomingMessages](https://green-api.com/en/docs/api/journals/LastIncomingMessages/)                    |
| `journals.lastOutgoingMessages`      | Method for getting last outgoing messages                                                                  | [LastOutgoingMessages](https://green-api.com/en/docs/api/journals/LastOutgoingMessages/)                    |
| `queues.showMessagesQueue`           | Method for getting messages that are in the outgoing messages queue                                      | [ShowMessagesQueue](https://green-api.com/en/docs/api/queues/ShowMessagesQueue/)                            |
| `queues.clearMessagesQueue`          | Method for clearing messages from the outgoing message queue                                                              | [ClearMessagesQueue](https://green-api.com/en/docs/api/queues/ClearMessagesQueue/)                          |
| `marking.readChat`                   | Method for marking a chat as read                                                              | [ReadChat](https://green-api.com/en/docs/api/marks/ReadChat/)                                               |
| `receiving.receiveNotification`      | Method for receiving a notification from the incoming notification queue                                      | [ReceiveNotification](https://green-api.com/en/docs/api/receiving/technology-http-api/ReceiveNotification/) |
| `receiving.deleteNotification`       | Method for deleting a notification from the incoming notification queue                                              | [DeleteNotification](https://green-api.com/en/docs/api/receiving/technology-http-api/DeleteNotification/)   |
| `receiving.downloadFile`             | Method for downloading file from outgoing or incoming message                                                          | [DownloadFile](https://green-api.com/en/docs/api/receiving/files/DownloadFile/)                             |
| `sending.sendMessage`                | Method for sending a text message to a personal or group chat                                           | [SendMessage](https://green-api.com/en/docs/api/sending/SendMessage/)                                       |
| `sending.sendButtons`                | Method for sending buttons to a personal or group chat                                           | [SendButtons](https://green-api.com/en/docs/api/sending/SendButtons/)                                       |
| `sending.sendTemplateButtons`        | Method for sending a message with interactive buttons from the list of templates in a personal or group chat        | [SendTemplateButtons](https://green-api.com/en/docs/api/sending/SendTemplateButtons/)                       |
| `sending.sendListMessage`            | Method for sending a message with a selection button from a list of values to a personal or group chat                  | [SendListMessage](https://green-api.com/en/docs/api/sending/SendListMessage/)                               |
| `sending.sendFileByUpload`           | Method for sending a file through a form (form-data)                                               | [SendFileByUpload](https://green-api.com/en/docs/api/sending/SendFileByUpload/)                             |
| `sending.sendFileByUrl`              | Method for sending a file by URL                                                             | [SendFileByUrl](https://green-api.com/en/docs/api/sending/SendFileByUrl/)                                   |
| `sending.uploadFile`                 | Method for uploading a file to the cloud storage, which can be sent using the sendFileByUrl method                 | [UploadFile](https://green-api.com/en/docs/api/sending/UploadFile/)                                         |
| `sending.sendLocation`               | Method for sending a location                                                                      | [SendLocation](https://green-api.com/en/docs/api/sending/SendLocation/)                                     |
| `sending.sendContact`                | Method for sending a contact                                                                     | [SendContact](https://green-api.com/en/docs/api/sending/SendContact/)                                       |
| `sending.sendLink`                   | Method for sending a message with a link that will add an image preview, title and description | [SendLink](https://green-api.com/en/docs/api/sending/SendLink/)                                             |
| `sending.forwardMessages`            | Method for forwarding messages to a personal or group chat                                                     | [ForwardMessages](https://green-api.com/en/docs/api/sending/ForwardMessages/)                               |
| `sending.sendPoll`                   | Method for sending messages with a poll to a private or group chat                                            | [SendPoll](https://green-api.com/en/docs/api/sending/SendPoll/)                                             |
| `serviceMethods.checkWhatsapp`       | Method for checking if there is a WhatsApp account on the phone number                                                              | [CheckWhatsapp](https://green-api.com/en/docs/api/service/CheckWhatsapp/)                                   |
| `serviceMethods.getAvatar`           | Method for getting the avatar of the correspondent or group chat                                                                | [GetAvatar](https://green-api.com/en/docs/api/service/GetAvatar/)                                           |
| `serviceMethods.getContacts`         | Method for getting contacts of current account                                                       | [GetContacts](https://green-api.com/en/docs/api/service/GetContacts/)                                       |
| `serviceMethods.getContactInfo`      | Method for getting information of the contact                                                                    | [GetContactInfo](https://green-api.com/en/docs/api/service/GetContactInfo/)                                 |
| `serviceMethods.deleteMessage`       | Method for deleting a messages from the chat                                                                                           | [DeleteMessage](https://green-api.com/en/docs/api/service/deleteMessage/)                                   |
| `serviceMethods.archiveChat`         | Method for archiving a chat                                                                                                      | [ArchiveChat](https://green-api.com/en/docs/api/service/archiveChat/)                                       |
| `serviceMethods.unarchiveChat`       | Method for unarchiving a chat                                                                                                   | [UnarchiveChat](https://green-api.com/en/docs/api/service/unarchiveChat/)                                   |
| `serviceMethods.setDisappearingChat` | Method for changing the settings of disappearing messages in chats                                                    | [SetDisappearingChat](https://green-api.com/en/docs/api/service/SetDisappearingChat/)                       |     |

## Service methods documentation

[https://green-api.com/docs/api/](https://green-api.com/en/docs/api/).

## Library dependencies

- [curl](https://vcpkg.io/en/package/curl) - for HTTP requests.
- [nlohmann-json](https://vcpkg.io/en/package/nlohmann-json) - to work with JSON.
- [websocketpp](https://vcpkg.io/en/package/websocketpp) - for websocket requests.

## Licence

Licences under [
Creative Commons Attribution-NoDerivatives 4.0 International (CC BY-ND 4.0)
](https://creativecommons.org/licenses/by-nd/4.0/).
[LICENSE](../LICENSE).
