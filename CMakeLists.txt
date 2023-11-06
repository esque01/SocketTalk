cmake_minimum_required(VERSION 3.0.0)
project(SocketTalk VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK REQUIRED gtk+-3.0)

add_executable(SocketTalk main.cpp client.cpp server.cpp)

target_compile_definitions(SocketTalk PRIVATE ${GTKMM_CFLAGS_OTHER})
target_include_directories(SocketTalk PRIVATE ${GTK_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_include_directories(SocketTalk PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SocketTalk PRIVATE ${GTK_LIBRARIES} ${GTKMM_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

add_custom_target(run
    COMMAND ./SocketTalk
    DEPENDS SocketTalk
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
