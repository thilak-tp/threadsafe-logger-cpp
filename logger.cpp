#include"logger.h"


// Private Default Constructor
Logger::Logger() {
	logFile.open("app.log", std::ios::app);
	if(!logFile.is_open()) {
		std::cerr<<"Failed to open log file!" << std::endl;
	}
}

		
// Convert Log Level to String
std::string Logger::levelToString(LogLevel level) {
	switch(level) {
		case LogLevel::DEBUG: 	return "DEBUG";
		case LogLevel::INFO: 	return "INFO";
		case LogLevel::WARNING:  return "WARNING";
		case LogLevel::ERROR: 	return "ERROR";
		default:		return "UNKNOWN";
	}
}

// Get current timestamp as String
std::string Logger::getCurrTime() {
	auto now = std::chrono::system_clock::now();
	auto timeT = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000;

	std::stringstream ss;
	ss<<std::put_time(std::localtime(&timeT),"%Y-%m-%d %H:%M:%S");
	ss<<'.'<< std::setfill('0') <<std::setw(3)<<ms.count();
	return ss.str();
}

		
// Creates and returns a single instance once
Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}

// Main Logging function
void Logger::log( const std::string& message, LogLevel level) {
	std::lock_guard<std::mutex> lock(mtx);

	std::string logLine = "[" + getCurrTime() + "]" + "[" + levelToString(level) + "]" + message + "\n";
	if(logFile.is_open()) {
		logFile<<logLine;
		logFile.flush();
	}

	std::cout<<logLine;
}

