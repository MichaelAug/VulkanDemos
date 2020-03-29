cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(VulkanTutorial)

# add the executable
add_executable(VulkanTutorial 
	src/main.cpp)