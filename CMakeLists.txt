cmake_minimum_required(VERSION 3.21)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(ft_containers
        containers.hpp
        main.cpp
        map.hpp
        stack.hpp
        vector.hpp
        iteratorVector.hpp
        Utils_iterator.hpp
        Reverse_iterator.hpp
        Pair.hpp
        iteratorMap.hpp)
