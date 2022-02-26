add_executable(cli_tests 
    CreateCommandTest.cpp
    ListCommandTest.cpp
)
target_link_libraries(cli_tests 
    MBTilesCppAppLib
    SQLiteCpp::SQLiteCpp
    CLI11::CLI11
    GTest::GTest
)
add_test(NAME "MBTilesCliTests" COMMAND "cli_tests")