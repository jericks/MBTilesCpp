#include "MBTiles.hpp"

namespace mbtiles {

    MBTiles::MBTiles(std::string fileName) : MBTiles(fileName, MBTilesOptions{}) {}

    MBTiles::MBTiles(std::string fileName, MBTilesOptions options): fileName(fileName) {
        createTables();
        setMetadatum(mbtiles::Metadatum{"name",options.name});
        setMetadatum(mbtiles::Metadatum{"version",options.version});
        setMetadatum(mbtiles::Metadatum{"description",options.description});
        setMetadatum(mbtiles::Metadatum{"attribution",options.attribution});
        setMetadatum(mbtiles::Metadatum{"type",options.type});
        setMetadatum(mbtiles::Metadatum{"format",options.format});
        setMetadatum(mbtiles::Metadatum{"bounds",options.bounds});
        setMetadatum(mbtiles::Metadatum{"minzoom",options.minzoom});
        setMetadatum(mbtiles::Metadatum{"maxzoom",options.maxzoom});
    }

    MBTiles::~MBTiles() {
    }

    void  MBTiles::createTables() {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            db.exec("CREATE TABLE IF NOT EXISTS metadata (name text, value text);");  
            db.exec("CREATE TABLE IF NOT EXISTS tiles (zoom_level integer, tile_column integer, tile_row integer, tile_data blob);");
            db.exec("CREATE UNIQUE INDEX IF NOT EXISTS tile_index on tiles (zoom_level, tile_column, tile_row);");
            db.exec("CREATE TABLE IF NOT EXISTS grids (zoom_level integer, tile_column integer, tile_row integer, grid blob);");
            db.exec("CREATE TABLE IF NOT EXISTS grid_data (zoom_level integer, tile_column integer, tile_row integer, key_name text, key_json text);");
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }
    }

    int MBTiles::getMinZoom() {
        SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "select min(zoom_level) as min_zoom_level from tiles");
        query.executeStep();
        return query.getColumn(0).getInt();
    }

    int MBTiles::getMaxZoom() {
        SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "select max(zoom_level) as max_zoom_level from tiles");
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    int MBTiles::countTiles(int zoom) {
        SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "select count(*) as tile_count from tiles where zoom_level = ?");
        query.bind(1, zoom);
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    void MBTiles::exportToDirectory(std::string directory) {
        std::string format = getMetadatum("format").value_or(Metadatum{"format","png"}).value;  
        std::filesystem::path dir = directory;
        std::filesystem::create_directories(dir);
        const int minZoom = getMinZoom();
        const int maxZoom = getMaxZoom();
        for(int z = minZoom; z <= maxZoom; ++z) {
            std::string zoomDir = directory + "/" + std::to_string(z);
            std::filesystem::create_directories(zoomDir);   
            tiles(z, [&](Tile& t) {
               std::string tileDir = zoomDir + "/" + std::to_string(t.column);
               std::filesystem::create_directories(tileDir);
               t.save(tileDir + "/" + std::to_string(t.row) + "." + format);
            });
        } 
    }

    void MBTiles::loadFromDirectory(std::string directory) {
        for (auto& dirEntry: std::filesystem::recursive_directory_iterator(directory)) {
            if (dirEntry.is_regular_file()) {
                std::filesystem::path file = dirEntry.path();
                if (file.extension() == ".jpeg") {
                    int z = std::stoi(file.parent_path().parent_path().stem());
                    int c = std::stoi(file.parent_path().stem());
                    int r = std::stoi(file.filename().stem());
                    const Tile t {z,c,r,std::filesystem::absolute(file)};
                    addTile(t);
                }
            }
        }
    }

    // Metadata

    void MBTiles::addMetadatum(const Metadatum& m) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO metadata (name, value) VALUES (?,?)");
            insert.bind(1, m.name);
            insert.bind(2, m.value);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::updateMetadatum(const Metadatum& m) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "UPDATE metadata SET value = ? WHERE name = ?");
            insert.bind(1, m.value);
            insert.bind(2, m.name);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::setMetadatum(const Metadatum& m) {
        auto metadatum = getMetadatum(m.name);
        if (metadatum) {
            updateMetadatum(m);
        } else {
            addMetadatum(m);
        }
    }

    void MBTiles::deleteMetadatum(const Metadatum& m) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM metadata WHERE name = ?");
            insert.bind(1, m.name);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    std::optional<Metadatum> MBTiles::getMetadatum(const std::string& name) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT name, value FROM metadata WHERE name = ?");
            query.bind(1, name);
            if (query.executeStep()) {
                const char* metadataName = query.getColumn(0);
                const char* metadataValue = query.getColumn(1);
                return Metadatum{metadataName, metadataValue};
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    std::map<std::string,std::string> MBTiles::getMetadata() {
        std::map<std::string, std::string> values;
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);        
            SQLite::Statement query(db, "SELECT name, value FROM metadata");
            while (query.executeStep()) {
                const char* metadataName = query.getColumn(0);
                const char* metadataValue = query.getColumn(1);
                values[metadataName] = metadataValue;
            } 
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return values;
    }


    // Tile

    void  MBTiles::addTile(const Tile& t) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO tiles (zoom_level, tile_column, tile_row, tile_data) VALUES (?,?,?,?)");
            insert.bind(1, t.zoom);
            insert.bind(2, t.column);
            insert.bind(3, t.row);
            insert.bind(4, std::data(t.data), t.data.size());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::updateTile(const Tile& t) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE tiles SET tile_data = ? WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            update.bind(1, std::data(t.data), t.data.size());
            update.bind(2, t.zoom);
            update.bind(3, t.column);
            update.bind(4, t.row);
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::setTile(const Tile& t) {
        auto tile = getTile(t.zoom, t.column, t.row);
        if (tile) {
            updateTile(t);
        } else {
            addTile(t);
        }
    }

    void MBTiles::deleteTile(const Tile& t) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            insert.bind(1, t.zoom);
            insert.bind(2, t.column);
            insert.bind(3, t.row);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    std::optional<Tile> MBTiles::getTile(int z, int c, int r) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, tile_data FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            query.bind(1, z);
            query.bind(2, c);
            query.bind(3, r);
            if (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                return Tile{zoom, column, row, data};
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  MBTiles::tiles(int zoom, std::function<void(Tile& t)> func) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, tile_data FROM tiles WHERE zoom_level = ?");
            query.bind(1, zoom);
            while (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                Tile tile {zoom, column, row, data};
                func(tile);
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    
    }

    // Grid

    void MBTiles::addGrid(const Grid& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO grids (zoom_level, tile_column, tile_row, grid) VALUES (?,?,?,?)");
            insert.bind(1, g.zoom);
            insert.bind(2, g.column);
            insert.bind(3, g.row);
            insert.bind(4, std::data(g.data), g.data.size());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::updateGrid(const Grid& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE grids SET grid = ? WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            update.bind(1, std::data(g.data), g.data.size());
            update.bind(2, g.zoom);
            update.bind(3, g.column);
            update.bind(4, g.row);
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::setGrid(const Grid& g) {
        auto grid = getGrid(g.zoom, g.column, g.row);
        if (grid) {
            updateGrid(g);
        } else {
            addGrid(g);
        }
    }

    void MBTiles::deleteGrid(const Grid& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM grids WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            insert.bind(1, g.zoom);
            insert.bind(2, g.column);
            insert.bind(3, g.row);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    std::optional<Grid> MBTiles::getGrid(int z, int c, int r) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, grid FROM grids WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            query.bind(1, z);
            query.bind(2, c);
            query.bind(3, r);
            if (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                return Grid{zoom, column, row, data};
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  MBTiles::grids(int zoom, std::function<void(Grid& g)> func) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, grid FROM grids WHERE zoom_level = ?");
            query.bind(1, zoom);
            while (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                Grid grid{zoom, column, row, data};
                func(grid);
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    // GridData

   void MBTiles::addGridData(const GridData& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO grid_data (zoom_level, tile_column, tile_row, key_name, key_json) VALUES (?,?,?,?,?)");
            insert.bind(1, g.zoom);
            insert.bind(2, g.column);
            insert.bind(3, g.row);
            insert.bind(4, g.name);
            insert.bind(5, g.json);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::updateGridData(const GridData& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE grid_data SET key_json = ? WHERE zoom_level = ? AND tile_column = ? AND tile_row = ? AND key_name = ?");
            update.bind(1, g.json);
            update.bind(2, g.zoom);
            update.bind(3, g.column);
            update.bind(4, g.row);
            update.bind(5, g.name);
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    void MBTiles::setGridData(const GridData& g) {
        auto gridData = getGridData(g.zoom, g.column, g.row, g.name);
        if (gridData) {
            updateGridData(g);
        } else {
            addGridData(g);
        }
    }

    void MBTiles::deleteGridData(const GridData& g) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM grid_data WHERE zoom_level = ? AND tile_column = ? AND tile_row = ? AND key_name = ?");
            insert.bind(1, g.zoom);
            insert.bind(2, g.column);
            insert.bind(3, g.row);
            insert.bind(4, g.name);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
    }

    std::optional<GridData> MBTiles::getGridData(int z, int c, int r, std::string name) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, key_name, key_json FROM grid_data WHERE zoom_level = ? AND tile_column = ? AND tile_row = ? AND key_name = ?");
            query.bind(1, z);
            query.bind(2, c);
            query.bind(3, r);
            query.bind(4, name);
            if (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                std::string name = query.getColumn(3).getString();
                std::string json = query.getColumn(4).getString();
                return GridData{zoom, column, row, name, json};
            }
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    std::map<std::string,std::string> MBTiles::getGridData(int z, int c, int r) {
        std::map<std::string, std::string> values;
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);        
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, key_name, key_json FROM grid_data WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            query.bind(1, z);
            query.bind(2, c);
            query.bind(3, r);
            while (query.executeStep()) {
                std::string name = query.getColumn(3).getString();
                std::string json = query.getColumn(4).getString();
                values[name] = json;
            } 
        }
        catch (std::exception& e) {
            std::cout << "exception: " << e.what() << std::endl;
        }    
        return values;   
    }

}