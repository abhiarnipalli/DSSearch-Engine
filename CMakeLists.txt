cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

set(PORTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/porter2stemmer)
add_subdirectory(porter2stemmer)

include_directories(${PORTER_INCLUDE_DIR})
add_executable(mainRun main.cpp Query_Parser.cpp Query_Parser.h File_Parser.cpp File_Parser.h UserInterface.cpp UserInterface.cpp)

# this makes sure we also link rapidjson
# target_include_directories(rapidJSONExample PRIVATE rapidjson/)

target_link_libraries(mainRun porter2stemmer)
ADD_DEPENDENCIES(mainRun porter2stemmer)



target_include_directories(mainRun PRIVATE rapidjson/)
# target_include_directories(mainRun PRIVATE porter2stemmer/)
set(CMAKE_VERBOSE_MAKEFILE OFF)
