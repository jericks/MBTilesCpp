add_executable(tests 
    MBTilesTest.cpp
)
target_link_libraries(tests 
    MBTilesCppLib
    GTest::GTest
)
add_test(NAME "MBTilesTests" COMMAND "tests")