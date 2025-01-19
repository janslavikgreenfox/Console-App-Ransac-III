# executable/CMakeLists.txt

set(EXECUTABLE_SOURCES
    src/Console-App-Ransac-III-main.cpp
)

set(EXECUTABLE_HEADERS
    include/Console-App-Ransac-III-main.h
)

add_executable(MyExecutable ${EXECUTABLE_SOURCES})

target_include_directories(MyExecutable PRIVATE include)

target_link_libraries(MyExecutable PRIVATE MyLibrary)