project(MBTilesCppApp)

add_library(MBTilesCppAppLib STATIC
	src/Command.cpp
	src/Commands.cpp
	src/ListCommand.cpp
	src/CreateCommand.cpp
	src/ExportCommand.cpp
	src/ImportCommand.cpp
)
target_include_directories(MBTilesCppAppLib PUBLIC "include" "../lib/include" CLI11::CLI11)
target_compile_features(MBTilesCppAppLib PUBLIC cxx_std_17)
target_link_libraries(MBTilesCppAppLib PRIVATE MBTilesCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11)

# Application
add_executable(mbtiles-cli src/App.cpp)
target_link_libraries(mbtiles-cli PRIVATE MBTilesCppAppLib MBTilesCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11) 

add_subdirectory(test)