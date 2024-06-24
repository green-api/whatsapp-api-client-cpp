#include "../../../whatsapp-api-client-cpp/include/helpers/logger.hpp"

namespace greenapi {

	Logger& Logger::getInstance() {
		static Logger instance;
		return instance;
	}

	Logger::Logger() {
#if LOG_FILE
		initLogFile();
#endif
	}

	Logger::~Logger() {
		if (logfile.is_open()) {
			logfile.close();
		}
	}

	void Logger::log(const std::string& message, const std::string level) {

		if (level == "error") {

			std::string messageLog = "{ \"timestamp\": \"" + Logger::getCurrentTime() + "\", \"level\": \"" + level + "\", \"message\": \"" + message + "\" }";
			std::lock_guard<std::mutex> lock(log_mutex);
			std::cout << messageLog << std::endl;
#if LOG_FILE
			if (logfile.is_open()) {
				logfile << messageLog << std::endl;
			}
#endif
		}
		else {

#if LOG_CONSOLE || LOG_FILE
			std::string messageLog = "{ \"timestamp\": \"" + Logger::getCurrentTime() + "\", \"level\": \"" + level + "\", \"message\": \"" + message + "\" }";
			std::lock_guard<std::mutex> lock(log_mutex);
#endif
#if LOG_CONSOLE
			std::cout << messageLog << std::endl;
#endif
#if LOG_FILE
			if (logfile.is_open()) {
				logfile << messageLog << std::endl;
			}
#endif
		}
	}

#if LOG_FILE
	void Logger::initLogFile() {
		logfile.open("log.txt", std::ios::app);
		if (!logfile.is_open()) {
			throw std::runtime_error("Unable to open log file");
		}
	}
#endif

	std::string Logger::getCurrentTime() const {
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm;
#if defined(_MSC_VER) || defined(__MINGW32__)
		localtime_s(&now_tm, &now_time);
#else
		localtime_r(&now_tm, &now_time);
#endif
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
		return std::string(buffer);
	}

	std::string Logger::hideStringPart(const std::string& input, size_t start, size_t length) {
		if (start > input.size() || start + length > input.size()) {
			throw std::out_of_range("Invalid start or length");
		}

		std::string result = input;
		for (size_t i = start; i < start + length; ++i) {
			result[i] = '*';
		}

		return result;
	}

}// namespace greenapi