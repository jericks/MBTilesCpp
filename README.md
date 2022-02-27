
MBTilesCpp
==========

A C++ MBTiles API.  It can create MBTiles databases and load tiles and metadata but it cannot generate the content of tiles.

```cpp
mbtiles::MBTiles mbtiles { "world.mbtiles" };
mbtiles.addTile(mbtiles::Tile(0,0,0,"tms/0/0/0.jpeg"));
mbtiles.addTile(mbtiles::Tile(1,0,0,"tms/1/0/0.jpeg"));
mbtiles.addTile(mbtiles::Tile(1,0,1,"tms/1/0/1.jpeg"));
mbtiles.addTile(mbtiles::Tile(1,1,0,"tms/1/1/0.jpeg"));
mbtiles.addTile(mbtiles::Tile(1,1,1,"tms/1/1/1.jpeg"));
   
mbtiles.tiles(1, [&](mbtiles::Tile& t) {
    std::cout << t << "\n";
});
```

MBTilesCpp is written in C++ using [SQLiteCPP](https://github.com/SRombauts/SQLiteCpp) and [CLI11](https://github.com/CLIUtils/CLI11).  The [Google Test](https://github.com/google/googletest) library is used to write unit tests.  The project is built
with [CMake](https://cmake.org/) and dependencies are managed with [conan](https://conan.io/).

Build
-----

```bash
mkdir build
cd build
conan install ..
cmake -g "Unix Makefiles" .
cmake --build .
ctest --verbose
```

Command line interface
----------------------

List all commands.

```bash
% mbtiles-cli list
list
create
export
import
info
```

Get help for a command

```bash
 % mbtiles-cli create --help
Create an empty MBTiles file
Usage: app/mbtiles-cli create [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f TEXT REQUIRED            File name
  --name TEXT                 Name
  --version TEXT              Version
  --description TEXT          Description
  --attribution TEXT          Attribution
  --type TEXT                 Type
  --format TEXT               Format
  --bounds TEXT               Bounds
  --minZoom TEXT              Min Zoom
  --maxZoom TEXT              Max Zoom
```

Create an new MBTiles file.

```bash
% mbtiles-cli create -f world.mbtiles
```

Import tiles from a directory.

```bash
% mbtiles-cli import -f world.mbtiles -d tms
```

Export tiles to a directory

```bash
% mbtiles-cli export -f world.mbtiles -d tms
```

Get information on a MBTiles file.

```bash
% mbtiles-cli info -f world.mbtiles
Metadata
attribution = Create with MBTilesCpp
bounds = -179.99,-85.0511,179.99,85.0511
description = Tiles
format = jpeg
maxzoom = 1
minzoom = 0
name = world
type = base_layer
version = 1.0

Tiles
0 = 1
1 = 4
2 = 16
3 = 64
```


