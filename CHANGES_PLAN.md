# План изменений SDK (сравнение с документацией GREEN API)

Дата анализа: 2026-07-13  
Документация: https://green-api.com/en/docs/api/

---

## Обратная совместимость

Все существующие методы принимают параметры через `nlohmann::json` (без строгих типизированных сигнатур для опциональных полей). Это значит:
- **Новые optional-параметры в существующих методах** не требуют изменения сигнатуры — пользователь просто добавляет их в JSON-объект. Совместимость не нарушается.
- **Новые методы** добавляются как новые функции-члены классов — это аддитивное изменение, обратную совместимость не нарушает.
- **Исключение:** если потребуется добавить перегрузку с дополнительным параметром (например, `getChats(const unsigned int count = 100)`), то нужно использовать default value чтобы не сломать существующий код.

---

## 1. Новые методы

### 1.1 `include/methods/sending.hpp` — класс `Sending`

#### `sendInteractiveButtons`
- **Документация:** https://green-api.com/en/docs/api/sending/SendInteractiveButtons/
- **Endpoint:** POST `{{apiUrl}}/waInstance{{idInstance}}/sendInteractiveButtons/{{apiTokenInstance}}`
- **Описание:** Отправляет сообщение с интерактивными кнопками (типы: copy, call, url). До 3 кнопок, текст кнопки до 25 символов. Работает только в личных чатах.

**Обязательные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `chatId` | string | Идентификатор чата |
| `body` | string | Текст сообщения (до 20 000 символов) |
| `buttons` | array | Массив объектов кнопок |

**Структура объекта кнопки:**
| Поле | Тип | Описание |
|------|-----|----------|
| `type` | string | Тип: `"copy"`, `"call"`, `"url"` |
| `buttonId` | string | Уникальный ID кнопки |
| `buttonText` | string | Текст кнопки (до 25 символов) |
| `copyCode` | string | (для type=copy) Текст для копирования |
| `phoneNumber` | string | (для type=call) Номер телефона |
| `url` | string | (для type=url) URL |

**Опциональные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `header` | string | Заголовок сообщения |
| `footer` | string | Подпись сообщения |

**Ответ:**
```json
{ "idMessage": "3EB0C767D097B7C7C030" }
```

**Пример вызова:**
```cpp
nlohmann::json body = {
    {"chatId", "79876543210@c.us"},
    {"header", "Выберите действие"},
    {"body", "Нажмите на нужную кнопку"},
    {"footer", "GREEN API"},
    {"buttons", {
        {{"type", "url"}, {"buttonId", "1"}, {"buttonText", "Открыть сайт"}, {"url", "https://green-api.com"}},
        {{"type", "call"}, {"buttonId", "2"}, {"buttonText", "Позвонить"}, {"phoneNumber", "79001234567"}},
        {{"type", "copy"}, {"buttonId", "3"}, {"buttonText", "Скопировать код"}, {"copyCode", "ABC123"}}
    }}
};
Response resp = greenApi.sending.sendInteractiveButtons(body);
```

---

#### `sendInteractiveButtonsReply`
- **Документация:** https://green-api.com/en/docs/api/sending/SendInteractiveButtonsReply/
- **Endpoint:** POST `{{apiUrl}}/waInstance{{idInstance}}/sendInteractiveButtonsReply/{{apiTokenInstance}}`
- **Описание:** Отправляет сообщение с кнопками-ответами (текстовые кнопки, каждая нажимается один раз). Бета-версия.

**Обязательные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `chatId` | string | Идентификатор чата |
| `body` | string | Текст сообщения |
| `buttons` | array | Массив объектов кнопок |

**Структура объекта кнопки:**
| Поле | Тип | Описание |
|------|-----|----------|
| `buttonId` | string | Уникальный ID кнопки |
| `buttonText` | string | Текст кнопки (до 25 символов) |

**Опциональные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `header` | string | Заголовок сообщения |
| `footer` | string | Подпись сообщения |

**Ответ:**
```json
{ "idMessage": "3EB0C767D097B7C7C030" }
```

**Пример вызова:**
```cpp
nlohmann::json body = {
    {"chatId", "79876543210@c.us"},
    {"header", "Опрос"},
    {"body", "Вам нравится наш сервис?"},
    {"footer", "Выберите один вариант"},
    {"buttons", {
        {{"buttonId", "1"}, {"buttonText", "Да"}},
        {{"buttonId", "2"}, {"buttonText", "Нет"}},
        {{"buttonId", "3"}, {"buttonText", "Не знаю"}}
    }}
};
Response resp = greenApi.sending.sendInteractiveButtonsReply(body);
```

---

### 1.2 `include/methods/account.hpp` — класс `Account`

#### `getStateInstanceHistory`
- **Документация:** https://green-api.com/en/docs/api/account/GetStateInstanceHistory/
- **Endpoint:** GET `{{apiUrl}}/waInstance{{idInstance}}/GetStateInstanceHistory/{{apiTokenInstance}}`
- **Описание:** Возвращает историю изменений состояния инстанса в хронологическом порядке.

**Опциональные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `count` | integer | Количество записей (по умолчанию 100) |

**Поля ответа (массив объектов):**
| Поле | Тип | Описание |
|------|-----|----------|
| `stateInstance` | string | Состояние: `"notAuthorized"`, `"authorized"`, `"blocked"` |
| `timestamp` | integer | Время события (UNIX) |
| `phoneNumber` | integer | Связанный номер телефона |

**Пример вызова:**
```cpp
// Получить последние 200 записей
Response resp = greenApi.account.getStateInstanceHistory(200);

// Получить 100 записей по умолчанию
Response resp = greenApi.account.getStateInstanceHistory();
```

> **Примечание по обратной совместимости:** метод новый, конфликтов нет. Параметр `count` лучше сделать опциональным с default value 100.

---

### 1.3 `include/methods/serviceMethods.hpp` — класс `ServiceMethods`

#### `getChats`
- **Документация:** https://green-api.com/en/docs/api/service/GetChats/
- **Endpoint:** GET `{{apiUrl}}/waInstance{{idInstance}}/getChats/{{apiTokenInstance}}`
- **Описание:** Возвращает список чатов аккаунта в хронологическом порядке. Обновляется не чаще раза в минуту.

**Опциональные параметры запроса (query-параметр):**
| Поле | Тип | Описание |
|------|-----|----------|
| `count` | integer | Количество чатов (по умолчанию — все) |

**Поля ответа (массив объектов):**
| Поле | Тип | Описание |
|------|-----|----------|
| `id` | string | Идентификатор чата (`@c.us` или `@g.us`) |
| `name` | string | Имя контакта или группы |
| `type` | string | `"user"` или `"group"` |
| `archive` | boolean | Находится ли чат в архиве |
| `ephemeralExpiration` | integer | Время жизни сообщений в секундах (0, 86400, 604800, 7776000) |
| `ephemeralSettingTimestamp` | integer | Время установки настройки (UNIX) |

**Пример вызова:**
```cpp
// Все чаты
Response resp = greenApi.serviceMethods.getChats();

// Первые 50 чатов
Response resp = greenApi.serviceMethods.getChats(50);
```

---

#### `sendTyping`
- **Документация:** https://green-api.com/en/docs/api/service/SendTyping/
- **Endpoint:** POST `{{apiUrl}}/waInstance{{idInstance}}/sendTyping/{{apiTokenInstance}}`
- **Описание:** Показывает индикатор "печатает" или "записывает аудио" в указанном чате.

**Обязательные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `chatId` | string | Идентификатор чата |

**Опциональные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `typingTime` | integer | Продолжительность индикатора в мс (1000–20000, по умолчанию — системное значение) |
| `typingType` | string | Тип: `"recording"` — запись аудио; без этого поля — печатает |

**Ответ:** HTTP 200 с пустым телом.

**Пример вызова:**
```cpp
// Показать "печатает" на 5 секунд
nlohmann::json body = {
    {"chatId", "79876543210@c.us"},
    {"typingTime", 5000}
};
Response resp = greenApi.serviceMethods.sendTyping(body);

// Показать "записывает аудио" на 3 секунды
nlohmann::json body = {
    {"chatId", "79876543210@c.us"},
    {"typingTime", 3000},
    {"typingType", "recording"}
};
Response resp = greenApi.serviceMethods.sendTyping(body);
```

---

### 1.4 `include/methods/groups.hpp` — класс `Groups`

#### `updateGroupSettings`
- **Документация:** https://green-api.com/en/docs/api/groups/UpdateGroupSettings/
- **Endpoint:** POST `{{apiUrl}}/waInstance{{idInstance}}/updateGroupSettings/{{apiTokenInstance}}`
- **Описание:** Изменяет настройки группового чата (права участников). Бета-версия.

**Обязательные параметры запроса:**
| Поле | Тип | Описание |
|------|-----|----------|
| `groupId` | string | Идентификатор группового чата |

**Опциональные параметры запроса (хотя бы одно должно быть указано):**
| Поле | Тип | Описание |
|------|-----|----------|
| `allowParticipantsEditGroupSettings` | boolean | Разрешить участникам менять имя, фото, описание и таймер исчезновения сообщений |
| `allowParticipantsSendMessages` | boolean | Разрешить участникам отправлять сообщения в группу |

**Поля ответа:**
| Поле | Тип | Описание |
|------|-----|----------|
| `updateGroupSettings` | boolean | Результат операции |
| `reason` | string | Описание ошибки (если не успешно) |

**Пример вызова:**
```cpp
nlohmann::json group = {
    {"groupId", "1234567890123@g.us"},
    {"allowParticipantsEditGroupSettings", true},
    {"allowParticipantsSendMessages", false}
};
Response resp = greenApi.groups.updateGroupSettings(group);
```

---

### 1.5 `include/methods/journals.hpp` — класс `Journals`

#### `lastIncomingCalls`
- **Документация:** https://green-api.com/en/docs/api/journals/LastIncomingCalls/
- **Endpoint:** GET `{{apiUrl}}/waInstance{{idInstance}}/lastIncomingCalls/{{apiTokenInstance}}?minutes={{minutes}}`
- **Описание:** Возвращает последние входящие звонки аккаунта. По умолчанию — за последние 24 часа. Бета-версия. Максимум 10 000 записей.

**Опциональные параметры (query):**
| Поле | Тип | Описание |
|------|-----|----------|
| `minutes` | integer | Временное окно в минутах (по умолчанию 1440) |

**Поля ответа (массив объектов):**
| Поле | Тип | Описание |
|------|-----|----------|
| `type` | string | Всегда `"incoming"` |
| `idMessage` | string | Уникальный ID звонка |
| `timestamp` | integer | Время окончания звонка (UNIX) |
| `typeMessage` | string | Всегда `"incomingCall"` |
| `chatId` | string | Идентификатор чата |
| `isVideo` | boolean | Видеозвонок |
| `status` | string | `"pickUp"`, `"hungUp"`, `"declined"`, `"missed"` |
| `isGroup` | boolean | Групповой звонок |

> **Требования:** В настройках инстанса должны быть включены `incomingWebhook` и `incomingCallWebhook`.

**Пример вызова:**
```cpp
// Входящие звонки за последние 24 часа
Response resp = greenApi.journals.lastIncomingCalls();

// Входящие звонки за последние 2 часа
Response resp = greenApi.journals.lastIncomingCalls(120);
```

---

#### `lastOutgoingCalls`
- **Документация:** https://green-api.com/en/docs/api/journals/LastOutgoingCalls/
- **Endpoint:** GET `{{apiUrl}}/waInstance{{idInstance}}/lastOutgoingCalls/{{apiTokenInstance}}?minutes={{minutes}}`
- **Описание:** Возвращает последние исходящие звонки аккаунта. По умолчанию — за последние 24 часа. Максимум 10 000 записей.

**Опциональные параметры (query):**
| Поле | Тип | Описание |
|------|-----|----------|
| `minutes` | integer | Временное окно в минутах (по умолчанию 1440) |

**Поля ответа (массив объектов):**
| Поле | Тип | Описание |
|------|-----|----------|
| `type` | string | Всегда `"outgoing"` |
| `idMessage` | string | Уникальный ID звонка |
| `timestamp` | integer | Время окончания звонка (UNIX) |
| `chatId` | string | Идентификатор чата |
| `duration` | integer | Длительность звонка в секундах |
| `isVideo` | boolean | Видеозвонок |
| `status` | string | `"pickUp"`, `"hungUp"`, `"declined"`, `"invalid"` |
| `participants` | array | Детали по каждому участнику |

> **Требования:** В настройках инстанса должен быть включён `outgoingCallWebhook`.

**Пример вызова:**
```cpp
// Исходящие звонки за последние 24 часа
Response resp = greenApi.journals.lastOutgoingCalls();

// Исходящие звонки за последние 60 минут
Response resp = greenApi.journals.lastOutgoingCalls(60);
```

---

## 2. Дополнение документации существующих методов

### 2.1 `sendMessage` — добавить описание опциональных параметров в комментарий

Текущий комментарий не описывает опциональные поля JSON. Нужно добавить:

| Поле | Тип | Описание |
|------|-----|----------|
| `quotedMessageId` | string | ID сообщения из того же чата для цитирования |
| `linkPreview` | boolean | Включить/выключить превью ссылок (по умолчанию `true`) |
| `typePreview` | string | Размер превью: `"large"` или `"small"` |
| `customPreview` | object | Кастомное превью: поля `title`, `description`, `link`, `image` (до 300 символов каждое) |
| `typingTime` | integer | Длительность индикатора "печатает" перед отправкой в мс (1000–20000) |

**Пример расширенного вызова:**
```cpp
nlohmann::json message = {
    {"chatId", "79876543210@c.us"},
    {"message", "Привет! Посмотри наш сайт."},
    {"quotedMessageId", "3EB0C767D097B7C7C030"},
    {"linkPreview", true},
    {"typePreview", "large"},
    {"typingTime", 3000}
};
Response resp = greenApi.sending.sendMessage(message);
```

---

## 3. Сводная таблица

| Файл | Что изменить | Тип изменения |
|------|-------------|---------------|
| `include/methods/sending.hpp` | Добавить `sendInteractiveButtons` | Новый метод |
| `include/methods/sending.hpp` | Добавить `sendInteractiveButtonsReply` | Новый метод |
| `source/methods/sending.cpp` | Реализовать `sendInteractiveButtons` | Новый метод |
| `source/methods/sending.cpp` | Реализовать `sendInteractiveButtonsReply` | Новый метод |
| `include/methods/account.hpp` | Добавить `getStateInstanceHistory` | Новый метод |
| `source/methods/account.cpp` | Реализовать `getStateInstanceHistory` | Новый метод |
| `include/methods/serviceMethods.hpp` | Добавить `getChats` | Новый метод |
| `include/methods/serviceMethods.hpp` | Добавить `sendTyping` | Новый метод |
| `source/methods/serviceMethods.cpp` | Реализовать `getChats` и `sendTyping` | Новый метод |
| `include/methods/groups.hpp` | Добавить `updateGroupSettings` | Новый метод |
| `source/methods/groups.cpp` | Реализовать `updateGroupSettings` | Новый метод |
| `include/methods/journals.hpp` | Добавить `lastIncomingCalls` | Новый метод |
| `include/methods/journals.hpp` | Добавить `lastOutgoingCalls` | Новый метод |
| `source/methods/journals.cpp` | Реализовать оба метода звонков | Новый метод |
| `include/methods/sending.hpp` | Обновить комментарий `sendMessage` с opt-полями | Документация |
| `examples/` | Добавить примеры для каждого нового метода | Новые файлы |

---

## 4. Что намеренно исключено

- **`updateTokenInstance`** — URL возвращает 404, метод не найден в документации.
- **`GetHistoryOfStateInstance`** (вариант с капсом) — то же, 404.
- **SendButtons, SendTemplateButtons, SendListMessage** — в архиве документации, не добавляем.
- **GetStatusInstance** — уже есть в `account.hpp`.

---

## 5. Примечания по реализации

1. **`sendTyping`** — возвращает HTTP 200 с пустым телом (не JSON). Нужно убедиться, что класс `Response` корректно обрабатывает пустой ответ (вероятно, уже обрабатывает, но стоит проверить).

2. **`getChats` и `getStateInstanceHistory`** — GET-запросы с опциональным параметром через query string или тело. Нужно уточнить по аналогии с `lastIncomingMessages`, как это реализовано (через `?minutes=` в URL или через JSON-тело).

3. **`updateGroupSettings`** — бета-версия API; стоит добавить предупреждение в комментарий.

4. **`lastIncomingCalls` и `lastOutgoingCalls`** — бета-версия API; аналогично.

5. **`sendInteractiveButtonsReply`** — бета-версия API.

6. **Примеры** (`examples/`) — желательно добавить отдельные файлы `test_interactive_buttons.cpp` и обновить существующие тестовые файлы.
