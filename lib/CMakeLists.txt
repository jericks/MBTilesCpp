project(MBTilesCppLib)

set(MBTilesCppLib_SOURCES 
	src/MBTiles.cpp
	src/Tile.cpp
	src/Metadatum.cpp
	src/Grid.cpp
	src/GridData.cpp
)

add_library(MBTilesCppLib STATIC ${MBTilesCppLib_SOURCES})

target_include_directories(MBTilesCppLib
	PUBLIC include SQLiteCpp::SQLiteCpp
	PRIVATE src
)
target_link_libraries(MBTilesCppLib SQLiteCpp::SQLiteCpp)

add_subdirectory(test)