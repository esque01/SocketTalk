#ifndef DB_MANAGER
#define DB_MANAGER

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <sstream>

struct UserData {
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    
    UserData(){}
    UserData(const std::string& first, const std::string& last, const std::string& e, const std::string& p): 
    firstName(first), lastName(last), email(e), password(p) {}
};

class DatabaseManager {
public:
    static DatabaseManager& getInstance();
    void connect(const std::string&);
    void close();
    void query(const std::string& sql);
    void createTables();
    bool insertUserData(const UserData&);
private:
    sqlite3* db;
    DatabaseManager();
};

#endif
