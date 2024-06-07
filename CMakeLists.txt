cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Argus VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADERS include/Toaster.h)
set(SOURCES src/main.cpp src/Toaster.cpp)

add_subdirectory(lib/WinToast)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE 
            ${CMAKE_CURRENT_LIST_DIR}/include 
            ${CMAKE_CURRENT_LIST_DIR}/lib/WinToast/include
)
target_link_libraries(${PROJECT_NAME} PUBLIC WinToast)