cmake_minimum_required(VERSION 3.5)

project(clituner LANGUAGES CXX VERSION 0.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(doc)
add_subdirectory(source)
add_subdirectory(package)

install(TARGETS clituner DESTINATION /usr/bin)