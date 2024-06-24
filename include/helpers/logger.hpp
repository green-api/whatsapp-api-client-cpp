#pragma once
#ifndef GREEN_API_LOGGER_H
#define GREEN_API_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>

#include "../config.hpp"

namespace greenapi {

	class Logger {

	private:
		Logger();
		~Logger();

		std::ofstream logfile;
		std::mutex log_mutex;

#if LOG_FILE
		void initLogFile();
#endif

		std::string getCurrentTime() const;

	public:
		// Getting a single instance of Logger
		static Logger& getInstance();

		// Removing copy and move methods
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(Logger&&) = delete;


		/*
		* Logging messages
		* @param message - line to write to log
		* @param level - optional logging level (error, warn, info, trace). The default level is debug
		* Regardless of the logging settings, the ERROR level is always logged
		*/
		void log(const std::string& message, std::string level = "debug");
		
		/*
		* Hiding part of a line
		* @param input - input string
		* @param start - character from the beginning of the line from which the text should be hidden
		* @param length - number of characters to hide
		*/
		std::string hideStringPart(const std::string& input, size_t start, size_t length);

	};
}// namespace greenapi

#endif // GREEN_API_LOGGER_H