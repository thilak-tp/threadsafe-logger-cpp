#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<mutex>
#include<iomanip>

// Different Strongly Typed Log Levels
enum class LogLevel {
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

// Main Logger Class
class Logger {
	private:
		Logger(); 		// Private Default Constructor
		std::ofstream logFile;  // Log File Handle
		std::mutex mtx;		// Mutex for thread safety while file access and writing
		
		// Convert Log Level to String
		std::string levelToString(LogLevel level); 
		// Get current timestamp as String
		std::string getCurrTime();
	public:
		Logger(const Logger&) = delete; 		// Delete Copy
		Logger& operator = (const Logger&) = delete;	// Delete Assignment
		
		// Creates and returns a single instance once
		static Logger& getInstance();
		// Main Logging function
		void log( const std::string& message, LogLevel level = LogLevel::INFO);

		// Convenience Method
		void debug( const std::string& msg) {	log(msg, LogLevel::DEBUG);	} 
		void info( const std::string& msg) {	log(msg, LogLevel::INFO);	} 
		void warning( const std::string& msg) {	log(msg, LogLevel::WARNING);	} 
		void error( const std::string& msg) {	log(msg, LogLevel::ERROR);	} 

		// Explicit Close Function
		void close() {
			std::lock_guard<std::mutex> lock(mtx);
			if(logFile.is_open())
				logFile.close();
		}

		// Destructor
		~Logger() {
			close();
		}

};
