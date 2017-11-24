cmake_minimum_required(VERSION 3.8)
project(Ex3New)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AIPlayer.cpp
        AIPlayer.h
        Board.cpp
        Board.h
        DefaultLogic.cpp
        DefaultLogic.h
        GameFlow.cpp
        GameFlow.h
        GameLogic.cpp
        GameLogic.h
        HumanPlayer.cpp
        HumanPlayer.h
        main.cpp
        Player.cpp
        Player.h
        Print.h
        PrintConsole.cpp
        PrintConsole.h
        Square.cpp
        Square.h)

add_executable(Ex3New ${SOURCE_FILES})