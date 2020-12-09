cmake_minimum_required(VERSION 3.15)
project(TCP_server C)

set(CMAKE_C_STANDARD 99)

add_executable(TCP_server main.c server.c client.c)