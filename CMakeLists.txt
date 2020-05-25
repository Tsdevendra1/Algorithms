cmake_minimum_required(VERSION 3.16)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algorithms main.cpp datastructures/hashmap/HashMap.cpp datastructures/hashmap/HashMap.h datastructures/binary_heap/BinaryHeap.cpp datastructures/binary_heap/BinaryHeap.h datastructures/red_black_tree/RedBlackTree.cpp datastructures/red_black_tree/RedBlackTree.h prefix-sufix/z_algorithm.cpp prefix-sufix/z_algorithm.h prefix-sufix/LongestPalindromSub.cpp prefix-sufix/LongestPalindromSub.h prefix-sufix/KMP.cpp prefix-sufix/KMP.h)