#pragma once
#ifndef GREEN_API_HELPERS_H
#define GREEN_API_HELPERS_H

#include <nlohmann/json.hpp>

/*
* Library Internal Functions
*/
#include "./helpers/logger.hpp"
#include "./helpers/requests.hpp"

/*
* API methods https://green-api.com/en/docs/api/
*/
#include "./methods/account.hpp"
#include "./methods/sending.hpp"
#include "./methods/receiving.hpp"
#include "./methods/journals.hpp"
#include "./methods/queues.hpp"
#include "./methods/groups.hpp"
#include "./methods/statuses.hpp"
#include "./methods/readMark.hpp"
#include "./methods/serviceMethods.hpp"

/*
* Library methods response
*/
#include "./helpers/response.hpp"

#endif // GREEN_API_HELPERS_H
