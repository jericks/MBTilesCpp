project(MBTilesCppApp)

add_library(MBTilesCppAppLib STATIC
	src/Command.cpp
	src/Commands.cpp
	src/ListCommand.cpp
	src/CreateCommand.cpp
	src/ExportCommand.cpp
	src/InfoCommand.cpp
	src/ImportCommand.cpp
	src/MetadataListCommand.cpp
	src/MetadataGetCommand.cpp
	src/MetadataDeleteCommand.cpp
	src/TileGetCommand.cpp
	src/TileSetCommand.cpp
	src/TileDeleteCommand.cpp
	src/GridDataDeleteCommand.cpp
	src/GridDataGetCommand.cpp
	src/GridDataSetCommand.cpp
	src/GridSetCommand.cpp
	src/GridDeleteCommand.cpp
	src/GridGetCommand.cpp
)
target_include_directories(MBTilesCppAppLib PUBLIC "include" "../lib/include" CLI11::CLI11)
target_compile_features(MBTilesCppAppLib PUBLIC cxx_std_17)
target_link_libraries(MBTilesCppAppLib PRIVATE MBTilesCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11)

# Application
add_executable(mbtiles-cli src/App.cpp)
target_link_libraries(mbtiles-cli PRIVATE MBTilesCppAppLib MBTilesCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11) 

add_subdirectory(test)