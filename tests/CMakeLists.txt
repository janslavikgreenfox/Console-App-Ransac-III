# Define source files for the test project
set(TEST_SOURCES
    LongRunningTests.cpp
    TestOfColumn.cpp
    TestOfLeastSquaresFitStrategy.cpp
    TestOfRANSACFitStrategy.cpp
    TestOfTable.cpp
    TestOfTableBuilder.cpp
    TestOfTableExport.cpp
)

# Define the test executable
add_executable(UnitTests ${TEST_SOURCES})

# Include directories
#target_include_directories(UnitTests PRIVATE .)

# Link the test executable with required libraries
target_link_libraries(UnitTests PRIVATE MyLibrary)

# Ensure the correct subsystem is used for a console application
set_target_properties(UnitTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)