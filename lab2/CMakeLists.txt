set(CMAKE_CXX_STANDARD 14)

add_library(lab2-hashtable framework/hashtable.cpp)
target_include_directories(lab2-hashtable PUBLIC framework/hashtable.h)

add_executable(lab2-framework framework/main.cpp)
target_link_libraries(lab2-framework lab2-hashtable)

add_executable(data-generator data-generator.cpp)

add_executable(lab2-main
        main.cpp
        djb2-hash.cpp
        quadratic-probing.cpp
        overflow-region.cpp
        )
target_include_directories(lab2-main PUBLIC .)
target_link_libraries(lab2-main lab2-hashtable)