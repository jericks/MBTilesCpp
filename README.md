
MBTilesCpp
==========

A C++ MBTiles API.

Command line interface
----------------------

mbtiles-cli list

mbtiles-cli create -f world.mbtiles

mbtiles-cli import -f world.mbtiles -d tms

mbtiles-cli export -f world.mbtiles -d tms

mbtiles-cli info -f world.mbtiles

mbtiles-cli metadata-get -f world.mbtiles -n name

mbtiles-cli metadata-set -f world.mbtiles -n name -v World

mbtiles-cli metadata-list -f world.mbtiles

mbtiles-cli tile-get -f world.mbtiles -z 0 -c 1 -r 1 -o 1.jpeg

mbtiles-cli tile-set -f world.mbtiles -z 0 -c 1 -r 1 -t 1.jpeg

mbtiles-cli tile-delete -f world.mbtiles -z 0 -c 1 -r 1
