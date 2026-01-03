include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(dragonfly_tests
    vector_test.cpp
)

target_link_libraries(dragonfly_tests
    PRIVATE
    dragonfly
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dragonfly_tests)
