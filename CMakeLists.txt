cmake_minimum_required(VERSION 3.14)

project(LoggerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable
add_executable(logger_app
	main.cpp
	logger.cpp
)

# Link threading library
find_package(Threads REQUIRED)
target_link_libraries(logger_app PRIVATE Threads::Threads)

# Add Additional Warnings
if(MSVC)
	target_compile_options(logger_app PRIVATE /W3)
else()
	target_compile_options(logger_app PRIVATE -Wall -Wextra)
endif()
