#pragma once
#ifndef GREEN_API_CONFIG_H
#define GREEN_API_CONFIG_H

#define CURL_LOG false // true/false cURL library logging level
#define GA_CURLOPT_TIMEOUT 60L // Total waiting time 60 seconds
#define GA_CURLOPT_CONNECTTIMEOUT 15L  // Connection timeout 15 seconds

#define LOG_FILE false
#define LOG_CONSOLE false // library errors are always written to the console

#endif // GREEN_API_CONFIG_H