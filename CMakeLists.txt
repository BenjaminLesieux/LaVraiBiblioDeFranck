cmake_minimum_required(VERSION 3.15)
project(LaBiblioDeFranck C)

set(CMAKE_C_STANDARD 99)
find_package(LibXml2 REQUIRED)

message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})

include_directories(${LIBXML2_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})


add_executable(LaBiblioDeFranck main.c Date.c Date.h LinkedList.c LinkedList.h DBClients.c DBClients.h DBBooks.c DBBooks.h)
target_link_libraries(LaBiblioDeFranck ${LIBXML2_LIBRARIES})



