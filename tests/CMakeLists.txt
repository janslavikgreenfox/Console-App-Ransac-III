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

add_executable(tests ${TEST_SOURCES})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(tests
    PRIVATE
        RansacLibrary
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
# Use add_test to register the test executable without running it during the build.
# This avoids executing the test binary at build-time (which was crashing during discovery).
#add_test(NAME tests COMMAND tests)

# If you want individual test discovery later, run the test executable manually
# or re-enable `gtest_discover_tests(tests)` after diagnosing the crash.
