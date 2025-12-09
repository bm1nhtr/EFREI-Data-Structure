cmake_minimum_required(VERSION 4.0)
project(LinkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(LinkedList main.c
        Lists/Slist/Slist.c
        Lists/Slist/Slist.h
        Lists/Slist_tail/Slist_tail.c
        Lists/Slist_tail/Slist_tail.h
        Lists/Dlist/Dlist.c
        Lists/Dlist/Dlist.h
        Stack/Stack.c
        Stack/Stack.h
        Trees/Btree/Btree.c
        Trees/Btree/Btree.h
        Queue/Queue.c
        Queue/Queue.h
        Trees/AVL/AVL.c
        Trees/AVL/AVL.h)
