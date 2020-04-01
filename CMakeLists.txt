cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH /usr/lib)

#Can't add GLM because it is a header only library (no .so file)
# TODO: learn about header only libraries
add_library(glm INTERFACE)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(VulkanTutorial)

# add the executable
add_executable(VulkanTutorial 
	src/main.cpp)


target_link_libraries(${PROJECT_NAME}
	PUBLIC
		vulkan
		glfw
		glm
)
