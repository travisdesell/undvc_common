cmake_minimum_required (VERSION 2.6)
project (undvc_common)
# The version number.
set (UNDVC_COMMON_VERSION_MAJOR 0)
set (UNDVC_COMMON_VERSION_MINOR 1)
 
#set(CMAKE_CXX_FLAGS "-g -Wall -O3 -funroll-loops -msse3")

set(CMAKE_LIBRARY_PATH ~/boost_1_53_0/stage/lib ${CMAKE_LIBRARY_PATH} /opt/local/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

SET(Boost_DEBUG 1)
unset(Boost_INCLUDE_DIR CACHE)
unset(Boost_INCLUDE_DIRS CACHE)
unset(Boost_LIBRARY_DIRS CACHE)


find_package(Boost COMPONENTS filesystem system)

if (Boost_FOUND)
    include_directories(
        ${Boost_INCLUDE_DIR}
        )
    add_definitions( -DHAS_BOOST )
endif(Boost_FOUND)

find_package(MySQL)
find_package(BOINC)

if (BOINC_SERVER_FOUND AND MYSQL_FOUND)
    include_directories(
        ${BOOST_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIRS}
        ${BOINC_INCLUDE_DIR}
        ${BOINC_INCLUDE_DIR}/api
        ${BOINC_INCLUDE_DIR}/db
        ${BOINC_INCLUDE_DIR}/lib
        ${BOINC_INCLUDE_DIR}/sched
        ${BOINC_INCLUDE_DIR}/tools
        ${MYSQL_INCLUDE_DIR}
        )

    message(STATUS "found boinc and mysql!")

    add_definitions( -D_BOINC_ )
endif (BOINC_SERVER_FOUND AND MYSQL_FOUND)

message (status "BOOST FOUND: ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY}")
message (status "BOINC FOUND: ${BOINC_SERVER_FOUND}, MYSQL FOUND: ${MYSQL_FOUND}")

link_directories(${Boost_LIBRARY_DIRS})

add_library(undvc_common vector_io arguments file_io parse_xml)

message(status "BOOST LIBRARIES: ${Boost_LIBRARIES}")

if (Boost_FOUND)
    target_link_libraries(undvc_common ${Boost_LIBRARIES})
endif (Boost_FOUND)

if (MYSQL_FOUND AND BOINC_SERVER_FOUND)
    target_link_libraries(undvc_common ${BOINC_SERVER_LIBRARIES} ${MYSQL_LIBRARIES} ${Boost_LIBRARIES})
endif (MYSQL_FOUND AND BOINC_SERVER_FOUND)
