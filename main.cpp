#include"logger.h"
#include<thread>

int main() {
	Logger& logger = Logger::getInstance();
	logger.info("Application Initialized");
	logger.debug("Entered Loop");
	logger.warning("Warning, memory overflow!");
	logger.error("Process stopped unexpectedly!");

	std::thread t1([&](){
		for(int i=0; i<5; i++)
			logger.info("Thread 1 messsage:"+std::to_string(i));		
	});

	std::thread t2([&](){
		logger.error("Thread 2 Critical error:");

	});

	t1.join();
	t2.join();
	logger.info("Application Shutdown");
	return 0;
}
