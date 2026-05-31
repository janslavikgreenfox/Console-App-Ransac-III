# Define source files for the test project
set(TEST_SOURCES
    #pch.cpp
    LongRunningTests.cpp
    TestOfColumn.cpp
    TestOfLeastSquaresFitStrategy.cpp
    TestOfRANSACFitStrategy.cpp
    TestOfTable.cpp
    TestOfTableBuilder.cpp
    TestOfTableExport.cpp
)



# set(TEST_SOURCES
#     minimal.cpp
# )

add_executable(tests ${TEST_SOURCES})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(tests
    PRIVATE
        MyLibrary
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
