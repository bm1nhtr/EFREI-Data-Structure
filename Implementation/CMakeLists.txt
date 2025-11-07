cmake_minimum_required(VERSION 4.0)
project(LinkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(LinkedList main.c
        Slist.c
        Slist.h
        Btree.c
        Btree.h
        Queue.c
        Queue.h)
