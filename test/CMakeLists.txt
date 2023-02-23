ENABLE_TESTING()

FILE(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
ADD_EXECUTABLE(
        Transcript_Test
        ${TEST_FILES}
)

TARGET_LINK_LIBRARIES(
        Transcript_Test
        GTest::gtest_main
        Transcript
)

INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(Transcript_Test)