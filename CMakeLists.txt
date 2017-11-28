cmake_minimum_required(VERSION 3.6)
project(Ex3New)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES src/AIPlayer.cpp src/AIPlayer.h src/Board.cpp src/Board.h src/DefaultLogic.cpp
        src/DefaultLogic.h src/GameFlow.cpp src/GameFlow.h src/HumanPlayer.cpp src/HumanPlayer.h
        src/Player.cpp src/Player.h src/Print.h src/PrintConsole.cpp src/PrintConsole.h src/Square.cpp
        src/Square.h src/GameLogic.cpp src/GameLogic.h)

set(TEST_FILES test/BoardTests.cpp test/SquareTests.cpp test/DefaultLogicTests.cpp test/GameFlowTests.cpp  test/DefaultLogicTests.h test/GameFlowTests.h test/SquareTests.h test/BoardTests.h)

add_executable(reversiTests ${SOURCE_FILES} ${TEST_FILES} test/gtest_main.cpp)
add_executable(reversiGame ${SOURCE_FILES} src/main.cpp)
target_link_libraries(reversiTests gtest gtest_main pthread)
add_test(reversiTests reversiTests)