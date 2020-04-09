cmake_minimum_required(VERSION 3.10)

#Can't add GLM because it is a header only library (no .so file)
# TODO: learn about header only libraries
add_library(glm INTERFACE)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VD_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Search all files by VD_SOURCES wildcard
file(GLOB SOURCES ${VD_SOURCES})

# Include header files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# set the project name
project(VulkanDemos)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# can Define VT_DEBUG for debug calls (remove in release) by adding -DVT_DEBUG
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -Wextra)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		vulkan
		glfw
		glm
)
