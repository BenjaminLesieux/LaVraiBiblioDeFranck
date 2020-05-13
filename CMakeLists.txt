cmake_minimum_required(VERSION 3.15)
project(LaBiblioDeFranck C)

set(CMAKE_C_STANDARD 99)

add_executable(LaBiblioDeFranck main.c Date.c Date.h LinkedList.c LinkedList.h DBClients.c DBClients.h DBBooks.c DBBooks.h)