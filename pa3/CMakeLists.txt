add_executable(pa3-1 1.cpp)

add_executable(pa3-3-sample 3-provided/kth_sample.cpp 3-provided/kth_lib.cpp)
add_executable(pa3-3-leftmostheap 3-leftmostheap.cpp 3-provided/kth_lib.cpp)
add_executable(pa3-3-binaryheap 3-binaryheap.cpp 3-provided/kth_lib.cpp)
add_executable(pa3-3-bst 3-bst.cpp 3-provided/kth_lib.cpp)
target_include_directories(pa3-3-sample PUBLIC 3-provided)
target_include_directories(pa3-3-leftmostheap PUBLIC 3-provided)
target_include_directories(pa3-3-binaryheap PUBLIC 3-provided)
target_include_directories(pa3-3-bst PUBLIC 3-provided)

add_executable(pa3-4 4.cpp)

add_executable(pa3-5 5.cpp)