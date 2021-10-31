cmake_minimum_required(VERSION 3.7)

project(SDL2-Calculator
	VERSION 1.0
	DESCRIPTION "A CMake + SDL2 experiment."
	LANGUAGES CXX)

# Custom SDL2_image & CMake_ttf config
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

if(SDL2_TTF_FOUND)
	message(STATUS "SDL2_ttf was found!")
endif()

add_executable(SDL2-Calc 
	LTexture.cpp
	LTexture.h
	Ltexture_button.cpp
	Ltexture_button.h
	Ltexture_window.cpp
	Ltexture_window.h
	postfix.cpp
	postfix.h
	Stroka.cpp
	Stroka.h
	stroka_dec.cpp
	stroka_dec.h
	visual.cpp)

file(COPY 
	sprite1.png 
	456.ttf
	calculator.png
	calculator_clic.png
	DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(SDL2-Calc ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
