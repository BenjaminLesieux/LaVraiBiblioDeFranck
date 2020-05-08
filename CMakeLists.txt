cmake_minimum_required(VERSION 3.15)
project(LaBiblioDeFranck C)

set(CMAKE_C_STANDARD 99)

add_executable(LaBiblioDeFranck main.c Date.c Date.h Client.c Client.h Book.c Book.h DB_Books.c DB_Books.h DB_Clients.c DB_Clients.h LinkedList.c LinkedList.h)