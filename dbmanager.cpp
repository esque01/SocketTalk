#include "dbmanager.h"

DatabaseManager::DatabaseManager() : db(nullptr) {

}

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::connect(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Database opened successfully." << std::endl;
    }
}

void DatabaseManager::close() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database closed successfully." << std::endl;
    } else {
        std::cerr << "Attempted to close a null database pointer." << std::endl;
    }
}

void DatabaseManager::query(const std::string& sql) {
    if (db) {
        char* errorMessage = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL Error: " << errorMessage << std::endl;
        } else {
            std::cout << "Query executed." << std::endl;
        }
    } else {
        std::cerr << "Attempted to execute a query on a null database pointer." << std::endl;
    }
}

void DatabaseManager::createTables() {
    const std::string createUsersTableSQL = "CREATE TABLE users (user_id INTEGER PRIMARY KEY AUTOINCREMENT, first_name TEXT NOT NULL, last_name TEXT NOT NULL, email TEXT NOT NULL, password TEXT NOT NULL)";

    query(createUsersTableSQL);
}

bool DatabaseManager::insertUserData(const UserData& data) {
    std::stringstream query;

    query << "INSERT INTO users (first_name, last_name, email, password) ";
    query << "VALUES ('" << data.firstName << "','" << data.lastName << "','" << data.email << "','" << data.password << "');";

    int result = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, nullptr);

    return result == SQLITE_OK;
}


