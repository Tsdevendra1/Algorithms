cmake_minimum_required(VERSION 3.16)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algorithms main.cpp datastructures/hashmap/HashMap.cpp datastructures/hashmap/HashMap.h datastructures/binary_heap/BinaryHeap.cpp datastructures/binary_heap/BinaryHeap.h datastructures/red_black_tree/RedBlackTree.cpp datastructures/red_black_tree/RedBlackTree.h strings/z_algorithm.cpp strings/z_algorithm.h strings/LongestPalindromSub.cpp strings/LongestPalindromSub.h strings/KMP.cpp strings/KMP.h strings/DeBruijn.cpp strings/DeBruijn.h graphs/Hierholzer.cpp graphs/Hierholzer.h datastructures/fenwick/Fenwick.cpp datastructures/fenwick/Fenwick.h datastructures/segment_tree/SegmentTree.cpp datastructures/segment_tree/SegmentTree.h sorting/merge_sort/MergeSort.cpp sorting/merge_sort/MergeSort.h)