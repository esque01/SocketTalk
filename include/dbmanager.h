#ifndef DB_MANAGER
#define DB_MANAGER

#include <iostream>
#include <string>
#include <sqlite3.h>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();
    void connect(const std::string&);
    void close();
    void query(const std::string& sql);
    void createTables();
private:
    sqlite3* db;
    DatabaseManager();
};

#endif
