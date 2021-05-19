set(CMAKE_CXX_STANDARD 14)

add_library(lab2-hashtable framework/hashtable.cpp)
target_include_directories(lab2-hashtable PUBLIC framework/hashtable.h)

add_executable(lab2-framework framework/main.cpp)
target_link_libraries(lab2-framework lab2-hashtable)

add_executable(data-generator data-generator.cpp)