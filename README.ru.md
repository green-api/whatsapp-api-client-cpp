# whatsapp-api-client-cpp

![](https://img.shields.io/badge/license-CC%20BY--ND%204.0-green)

## Поддержка

[![Support](https://img.shields.io/badge/support@green--api.com-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:support@green-api.com)
[![Support](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/greenapi_support_ru_bot)
[![Support](https://img.shields.io/badge/WhatsApp-25D366?style=for-the-badge&logo=whatsapp&logoColor=white)](https://wa.me/447458038017)

## Руководства и новости

[![Guides](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://www.youtube.com/@green-api)
[![News](https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/green_api)
[![News](https://img.shields.io/badge/WhatsApp-25D366?style=for-the-badge&logo=whatsapp&logoColor=white)](https://whatsapp.com/channel/0029VaHUM5TBA1f7cG29nO1C)

- [Documentation in English](https://github.com/green-api/whatsapp-api-client-cpp/blob/master/README.md).

`whatsapp-api-client-cpp` - библиотека для интеграции с мессенджером WhatsApp через API
сервиса [green-api.com](https://green-api.com/). Чтобы воспользоваться библиотекой, нужно получить регистрационный токен
и ID аккаунта в [личном кабинете](https://console.green-api.com/). Есть бесплатный тариф аккаунта разработчика.

- [whatsapp-api-client-cpp](#whatsapp-api-client-cpp)
	- [Поддержка](#поддержка)
	- [Руководства и новости](#руководства-и-новости)
	- [API](#api)
	- [Авторизация](#авторизация)
	- [Установка зависимостей](#установка-зависимостей)
		- [Windows](#windows)
			- [Windows x64](#windows-x64)
	- [Сборка библиоткеки](#сборка-библиоткеки)
		- [Windows](#windows-1)
		- [Подключение библиотеки](#подключение-библиотеки)
		- [Linux](#linux)
	- [Примеры](#примеры)
		- [Как инициализировать объект](#как-инициализировать-объект)
		- [Пример отправки текстового сообщения](#пример-отправки-текстового-сообщения)
		- [Работа с примерами библиотеки](#работа-с-примерами-библиотеки)
	- [Список примеров](#список-примеров)
	- [Полный список методов библиотеки](#полный-список-методов-библиотеки)
	- [Документация по методам сервиса](#документация-по-методам-сервиса)
	- [Зависимости библиотеки](#зависимости-библиотеки)
	- [Лицензия](#лицензия)

## API

Документация к REST API находится по [ссылке](https://green-api.com/docs/api/). Библиотека является обёрткой к REST API,
поэтому документация по ссылке выше применима и к самой библиотеке.

## Авторизация

Чтобы отправить сообщение или выполнить другие методы GREEN API, аккаунт WhatsApp в приложении телефона должен быть в
авторизованном состоянии. Для авторизации аккаунта перейдите в [личный кабинет](https://console.green-api.com/) и
сканируйте QR-код с использованием приложения WhatsApp.

## Установка зависимостей

Эта библиотека использует C++ 17, поддерживает Linux (g++) и Windows (Visual Studio 2019/2022).

Клонируйте репозиторий библиотеки

```bash
git clone https://github.com/green-api/whatsapp-api-client-cpp.git
```

### Windows

Установка зависимостей с пакетным менеджером `vcpkg`:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install curl
vcpkg install nlohmann-json
# vcpkg install websocketpp (опционально)
vcpkg integrate install
```

#### Windows x64

Большинство компьютеров с Windows сейчас имеют x64-разрядную версию, но по умолчанию `vcpkg` использует пакеты x86.

```bash
vcpkg install nlohmann-json:x64-windows
vcpkg install curl:x64-windows
```

> Для выполнения команд в PowerShell необходимо изменить команды на .\\vcpkg

После сборки `bootstrap-vcpkg.bat` требуется **добавить `vcpkg.exe` в переменные окружения Вашей системы** `PATH\vcpkg\installed\x64-windows\bin`.

## Сборка библиоткеки

### Windows

Для сборки библиотеки Вам потребуется:

- [CMake](https://cmake.org/download/) - кроcсплатформенная утилита для автоматической сборки программы из исходного кода.
- Компилятор [Microsoft Visual C++ (MSVC)](https://visualstudio.microsoft.com/ru/downloads/) для приложений на языке C++

Сборка библиотеки с использованием CMake и компилятором Visual Studio

Сборка библиотеки осуществляется с помощью сценария **build.bat** или CMake вручную (компиляция Debug версии библиотеки):

```bash
mkdir build
cd build
cmake ..
cd ../
cmake --build build
```

> Возможно при сборке Вам потребуется указать прямые пути до используемых библиотек, раскомментируйте строки в [CMakeList.txt](./CMakeLists.txt)

### Подключение библиотеки

Подключение библиотеки в Visual Studio можно сделать
добавив файл библиотеки whatsapp-api-client-cpp.lib в зависимости проекта:

1. Свойства->Свойства конфигурации->С/С++->Общие->Дополнительные каталоги включаемых файлов, указать файлы заголовков (папка PATH/whatsapp-api-client-cpp/include)
2. Свойства->Свойства конфигурации->Компоновщик->Общие->Дополнительные каталоги библиотек, указать путь к библиотеке (папка с собранным файлом PATH/build/)
3. Свойства->Свойства конфигурации->Компоновщик->Ввод->Дополнительные зависимости, указать наименование фаила библиотеки (whatsapp-api-client-cpp.lib)

> Внимательно выбирайте тип Вашей конфигурации и подключайте необходимую версию библиотеки (debug и release)

### Linux

Установка зависимостей с пакетным менеджером `vcpkg`:

- Зависимости
  - curl
  - nlohmann-json
  - websocketpp (опционально)

Вы можете установить зависимости с помощью готового сценария **install.sh** (`sudo sh install.sh`) или вручную:

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg/vcpkg install curl
./vcpkg/vcpkg install nlohmann-json
# ./vcpkg install websocketpp (опционально)
./vcpkg/vcpkg integrate install
```

Сборка библиотеки осуществляется с помощью сценария **build.sh** (`sudo sh build.sh`) или вручную:

```bash
mkdir build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build/

```

> Вы можете изменить каталог vcpkg, указав относительный или абсолютный путь.

Возможно при сборке библиотеки Вам потребуется установить дополнительные пакеты:

```sh
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install g++
sudo apt-get install pkg-config
sudo apt-get install libcurl4-openssl-dev
sudo apt install build-essential
```

## Примеры

### Как инициализировать объект

При инициализации объекта обязательно используйте параметры apiUrl и mediaUrl специально для экземпляра из Вашего [личного кабинета](https://console.green-api.com/), так вы получите наиболее стабильную работу API и минимальное время ответа методов.

```cpp
greenapi::GreenApi instance1101000001{
    "https://api.green-api.com",
    "https://media.green-api.com",
    "1101123456",
    "87be9e9532fc49748f2a44b9242e55f2e89f4bf97ed6498f80"
    };
```

### Пример отправки текстового сообщения
Ссылка на пример: [main.cpp](./main.cpp).

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

### Работа с примерами библиотеки

Все примеры собранны в папке examples, каждый из файлов примера содержит примеры всех методов библиотеки со всеми параметрами, которые поддерживает конкретный метод.
Для запуска конкретного примера необходимо производить копирование кода примера в ваш рабочий фаил main.cpp и параметризировать метод вашими значениями.

## Список примеров

| Описание                                    | Модуль                                                        |
| ------------------------------------------- | ------------------------------------------------------------- |
| Пример отправки текста                      | [main.cpp](./main.cpp)                                        |
| Примеры работы методов аккаунта             | [test_accaunt.cpp](./examples/test_accaunt.cpp)               |
| Примеры работы методов отправки             | [test_sending.cpp](./examples/test_sending.cpp)               |
| Примеры работы методов получения            | [test_receiving.cpp](./examples/test_receiving.cpp)           |
| Примеры работы методов журналов             | [test_journals.cpp](./examples/test_journals.cpp)             |
| Примеры работы методов очередей             | [test_queues.cpp](./examples/test_queues.cpp)                 |
| Примеры работы методов групп                | [test_groups.cpp](./examples/test_groups.cpp)                 |
| Примеры работы методов статусов             | [test_statuses.cpp](./examples/test_statuses.cpp)             |
| Примеры работы методов отметкок о прочтении | [test_readMark.cpp](./examples/test_readMark.cpp)             |
| Примеры работы методов сервисных методов    | [test_serviceMethods.cpp](./examples/test_serviceMethods.cpp) |

## Полный список методов библиотеки

| Метод API              | Описание                  | Documentation link                       |
| ---------------------- | ------------------------- | ---------------------------------------- |
| `account.getSettings`                | Метод предназначен для получения текущих настроек аккаунта                                                                | [GetSettings](https://green-api.com/docs/api/account/GetSettings/)                                       |
| `account.getWaSettings`              | Метод предназначен для получения информации о аккаунте WhatsApp                                                           | [GetWaSettings](https://green-api.com/docs/api/account/GetWaSettings/)                                   |
| `account.setSettings`                | Метод предназначен для установки настроек аккаунта                                                                        | [SetSettings](https://green-api.com/docs/api/account/SetSettings/)                                       |
| `account.getStateInstance`           | Метод предназначен для получения состояния аккаунта                                                                       | [GetStateInstance](https://green-api.com/docs/api/account/GetStateInstance/)                             |
| `account.getStatusInstance`          | Метод предназначен для получения состояния сокета соединения инстанса аккаунта с WhatsApp                                 | [GetStatusInstance](https://green-api.com/docs/api/account/GetStatusInstance/)                           |
| `account.reboot`                     | Метод предназначен для перезапуска аккаунта                                                                               | [Reboot](https://green-api.com/docs/api/account/Reboot/)                                                 |
| `account.logout`                     | Метод предназначен для разлогинивания аккаунта                                                                            | [Logout](https://green-api.com/docs/api/account/Logout/)                                                 |
| `account.qr`                         | Метод предназначен для получения QR-кода                                                                                  | [QR](https://green-api.com/docs/api/account/QR/)                                                         |
| `account.setProfilePicture`          | Метод предназначен для установки аватара аккаунта                                                                         | [SetProfilePicture](https://green-api.com/docs/api/account/SetProfilePicture/)                           |
| `account.getAuthorizationCode`       | Метод предназначен для авторизации инстанса по номеру телефона                                                            | [GetAuthorizationCode](https://green-api.com/docs/api/account/GetAuthorizationCode/)                     |
| `device.getDeviceInfo`               | Метод предназначен для получения информации об устройстве (телефоне), на котором запущено приложение WhatsApp Business    | [GetDeviceInfo](https://green-api.com/docs/api/phone/GetDeviceInfo/)                                     |
| `groups.createGroup`                 | Метод предназначен для создания группового чата                                                                           | [CreateGroup](https://green-api.com/docs/api/groups/CreateGroup/)                                        |
| `groups.updateGroupName`             | Метод изменяет наименование группового чата                                                                               | [UpdateGroupName](https://green-api.com/docs/api/groups/UpdateGroupName/)                                |
| `groups.getGroupData`                | Метод получает данные группового чата                                                                                     | [GetGroupData](https://green-api.com/docs/api/groups/GetGroupData/)                                      |
| `groups.addGroupParticipant`         | Метод добавляет участника в групповой чат                                                                                 | [AddGroupParticipant](https://green-api.com/docs/api/groups/AddGroupParticipant/)                        |
| `groups.removeGroupParticipant`      | Метод удаляет участника из группового чата                                                                                | [RemoveGroupParticipant](https://green-api.com/docs/api/groups/RemoveGroupParticipant/)                  |
| `groups.setGroupAdmin`               | Метод назначает участника группового чата администратором                                                                 | [SetGroupAdmin](https://green-api.com/docs/api/groups/SetGroupAdmin/)                                    |
| `groups.removeAdmin`                 | Метод лишает участника прав администрирования группового чата                                                             | [RemoveAdmin](https://green-api.com/docs/api/groups/RemoveAdmin/)                                        |
| `groups.setGroupPicture`             | Метод устанавливает аватар группы                                                                                         | [SetGroupPicture](https://green-api.com/docs/api/groups/SetGroupPicture/)                                |
| `groups.leaveGroup`                  | Метод производит выход пользователя текущего аккаунта из группового чата                                                  | [LeaveGroup](https://green-api.com/docs/api/groups/LeaveGroup/)                                          |
| `journals.getChatHistory`            | Метод возвращает историю сообщений чата                                                                                   | [GetChatHistory](https://green-api.com/docs/api/journals/GetChatHistory/)                                |
| `journals.getMessage`                | Метод возвращает сообщение чата                                                                                           | [GetMessage](https://green-api.com/docs/api/journals/GetMessage/)                                        |
| `journals.lastIncomingMessages`      | Метод возвращает крайние входящие сообщения аккаунта                                                                      | [LastIncomingMessages](https://green-api.com/docs/api/journals/LastIncomingMessages/)                    |
| `journals.lastOutgoingMessages`      | Метод возвращает крайние отправленные сообщения аккаунта                                                                  | [LastOutgoingMessages](https://green-api.com/docs/api/journals/LastOutgoingMessages/)                    |
| `queues.showMessagesQueue`           | Метод предназначен для получения списка сообщений, находящихся в очереди на отправку                                      | [ShowMessagesQueue](https://green-api.com/docs/api/queues/ShowMessagesQueue/)                            |
| `queues.clearMessagesQueue`          | Метод предназначен для очистки очереди сообщений на отправку                                                              | [ClearMessagesQueue](https://green-api.com/docs/api/queues/ClearMessagesQueue/)                          |
| `marking.readChat`                   | Метод предназначен для отметки сообщений в чате прочитанными                                                              | [ReadChat](https://green-api.com/docs/api/marks/ReadChat/)                                               |
| `receiving.receiveNotification`      | Метод предназначен для получения одного входящего уведомления из очереди уведомлений                                      | [ReceiveNotification](https://green-api.com/docs/api/receiving/technology-http-api/ReceiveNotification/) |
| `receiving.deleteNotification`       | Метод предназначен для удаления входящего уведомления из очереди уведомлений                                              | [DeleteNotification](https://green-api.com/docs/api/receiving/technology-http-api/DeleteNotification/)   |
| `receiving.downloadFile`             | Метод предназначен для скачивания принятых и отправленных файлов                                                          | [DownloadFile](https://green-api.com/docs/api/receiving/files/DownloadFile/)                             |
| `sending.sendMessage`                | Метод предназначен для отправки текстового сообщения в личный или групповой чат                                           | [SendMessage](https://green-api.com/docs/api/sending/SendMessage/)                                       |
| `sending.sendButtons`                | Метод предназначен для отправки сообщения с кнопками в личный или групповой чат                                           | [SendButtons](https://green-api.com/docs/api/sending/SendButtons/)                                       |
| `sending.sendTemplateButtons`        | Метод предназначен для отправки сообщения с интерактивными кнопками из перечня шаблонов в личный или групповой чат        | [SendTemplateButtons](https://green-api.com/docs/api/sending/SendTemplateButtons/)                       |
| `sending.sendListMessage`            | Метод предназначен для отправки сообщения с кнопкой выбора из списка значений в личный или групповой чат                  | [SendListMessage](https://green-api.com/docs/api/sending/SendListMessage/)                               |
| `sending.sendFileByUpload`           | Метод предназначен для отправки файла, загружаемого через форму (form-data)                                               | [SendFileByUpload](https://green-api.com/docs/api/sending/SendFileByUpload/)                             |
| `sending.sendFileByUrl`              | Метод предназначен для отправки файла, загружаемого по ссылке                                                             | [SendFileByUrl](https://green-api.com/docs/api/sending/SendFileByUrl/)                                   |
| `sending.uploadFile`                 | Метод предназначен для загрузки файла в облачное хранилище, который можно отправить методом sendFileByUrl                 | [UploadFile](https://green-api.com/docs/api/sending/UploadFile/)                                         |
| `sending.sendLocation`               | Метод предназначен для отправки сообщения геолокации                                                                      | [SendLocation](https://green-api.com/docs/api/sending/SendLocation/)                                     |
| `sending.sendContact`                | Метод предназначен для отправки сообщения с контактом                                                                     | [SendContact](https://green-api.com/docs/api/sending/SendContact/)                                       |
| `sending.sendLink`                   | Метод предназначен для отправки сообщения со ссылкой, по которой будут добавлены превью изображения, заголовок и описание | [SendLink](https://green-api.com/docs/api/sending/SendLink/)                                             |
| `sending.forwardMessages`            | Метод предназначен для пересылки сообщений в личный или групповой чат                                                     | [ForwardMessages](https://green-api.com/docs/api/sending/ForwardMessages/)                               |
| `sending.sendPoll`                   | Метод предназначен для отправки сообщения с опросом в личный или групповой чат                                            | [SendPoll](https://green-api.com/docs/api/sending/SendPoll/)                                             |
| `serviceMethods.checkWhatsapp`       | Метод проверяет наличие аккаунта WhatsApp на номере телефона                                                              | [CheckWhatsapp](https://green-api.com/docs/api/service/CheckWhatsapp/)                                   |
| `serviceMethods.getAvatar`           | Метод возвращает аватар корреспондента или группового чата                                                                | [GetAvatar](https://green-api.com/docs/api/service/GetAvatar/)                                           |
| `serviceMethods.getContacts`         | Метод предназначен для получения списка контактов текущего аккаунта                                                       | [GetContacts](https://green-api.com/docs/api/service/GetContacts/)                                       |
| `serviceMethods.getContactInfo`      | Метод предназначен для получения информации о контакте                                                                    | [GetContactInfo](https://green-api.com/docs/api/service/GetContactInfo/)                                 |
| `serviceMethods.deleteMessage`       | Метод удаляет сообщение из чата                                                                                           | [DeleteMessage](https://green-api.com/docs/api/service/deleteMessage/)                                   |
| `serviceMethods.archiveChat`         | Метод архивирует чат                                                                                                      | [ArchiveChat](https://green-api.com/docs/api/service/archiveChat/)                                       |
| `serviceMethods.unarchiveChat`       | Метод разархивирует чат                                                                                                   | [UnarchiveChat](https://green-api.com/docs/api/service/unarchiveChat/)                                   |
| `serviceMethods.setDisappearingChat` | Метод предназначен для изменения настроек исчезающих сообщений в чатах                                                    | [SetDisappearingChat](https://green-api.com/docs/api/service/SetDisappearingChat/)                       |     |

## Документация по методам сервиса

[https://green-api.com/docs/api/](https://green-api.com/docs/api/).

## Зависимости библиотеки

- [curl](https://vcpkg.io/en/package/curl) - для HTTP запросов.
- [nlohmann-json](https://vcpkg.io/en/package/nlohmann-json) - для работы с json.
- [websocketpp](https://vcpkg.io/en/package/websocketpp) - для websocket запросов.

## Лицензия

Лицензировано на условиях [
Creative Commons Attribution-NoDerivatives 4.0 International (CC BY-ND 4.0)
](https://creativecommons.org/licenses/by-nd/4.0/).
[LICENSE](../LICENSE).
