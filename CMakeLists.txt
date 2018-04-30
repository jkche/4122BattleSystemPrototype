cmake_minimum_required(VERSION 3.5.1)
project(SFMLDemo)

set(CMAKE_CX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -IC:/Users/justi_000/Desktop/SFML/include -LC:/Users/justi_000/Desktop/SFML/lib")

set(SOURCE_FILES main.cpp)

#set(EXECUTABLE_NAME "SFMLDemo")
#add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

#Find SFML for find_package
#set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/lib/SFML-2.4.2")

#find_package(SFML REQUIRED COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
add_executable(SFMLDemo main.cpp MoveButton.cpp MoveButton.h MoveMenu.cpp MoveMenu.h move.h move.cpp FillBar.h Animation.cpp Animation.h character.cpp character.h)
target_link_libraries(SFMLDemo sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_target(run
    COMMAND SFMLDemo
    DEPENDS SFMLDemo
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)