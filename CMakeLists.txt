cmake_minimum_required(VERSION 3.9.2)
project(FastAdaboost)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.58 REQUIRED serialization program_options)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(FastAdaboost
        src/boost_classifier.cpp
        src/boost_classifier.h
        src/boost_tree_helper.cpp
        src/boost_tree_helper.h
        src/classifier.h
        src/data_processor.cpp
        src/data_processor.h
        src/feature_hashing_classifier.cpp
        src/feature_hashing_classifier.h
        src/main.cpp
        src/math_util.cpp
        src/math_util.h
        src/matrix_util.cpp
        src/matrix_util.h
        src/murmurhash.cpp
        src/murmurhash.h
        src/stump_classifier.cpp
        src/stump_classifier.h
        src/typeredef.h)

target_link_libraries(FastAdaboost ${Boost_LIBRARIES})