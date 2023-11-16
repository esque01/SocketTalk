cmake_minimum_required(VERSION 3.0.0)
project(SocketTalk VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK REQUIRED gtk+-3.0)

find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)


add_executable(SocketTalk main.cpp client.cpp server.cpp dbmanager.cpp)

target_compile_definitions(SocketTalk PRIVATE ${GTKMM_CFLAGS_OTHER})
target_include_directories(SocketTalk PRIVATE ${GTK_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_include_directories(SocketTalk PRIVATE ${CMAKE_SOURCE_DIR}/include/bcrypt)
target_include_directories(SocketTalk PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(SocketTalk PRIVATE ${SQLite3_INCLUDE_DIRS})
target_include_directories(SocketTalk PRIVATE ${OPENSSL_INCLUDE_DIR})

target_link_libraries(SocketTalk PRIVATE ${GTK_LIBRARIES} ${GTKMM_LIBRARIES} ${SQLite3_LIBRARIES} ${OPENSSL_LIBRARIES} -lsqlite3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

add_custom_target(run
    COMMAND ./SocketTalk
    DEPENDS SocketTalk
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
