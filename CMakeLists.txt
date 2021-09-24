# Pyswisseph CMakeLists.txt

cmake_minimum_required( VERSION 3.10 )

project( pyswisseph )

message( STATUS "-- Configuring pyswisseph..." )

# MinGW variable
if ( WIN32 AND NOT MSVC )
    set( MINGW ON )
else()
    set( MINGW OFF )
endif()

# Python version
set( PYSWE_MINIMUM_PYTHON_VERSION
    3.6
    CACHE STRING "Minimum Python version" )

# Options
option( PYSWE_AUTO_SET_EPHE_PATH
    "Automaticaly set ephemeris path on module import"
    ON )
option( PYSWE_USE_SWEPHELP
    "Build extra functions"
    ON )

# Default ephemeris path
if ( MSVC )
    set( PYSWE_DEFAULT_EPHE_PATH
        "C:\\\\swisseph"
        CACHE STRING "Default ephemeris search path" )
elseif( MINGW )
    set( PYSWE_DEFAULT_EPHE_PATH
        "C:\\\\\\swisseph"
        CACHE STRING "Default ephemeris search path" )
else()
    set( PYSWE_DEFAULT_EPHE_PATH
        "/usr/share/swisseph:/usr/local/share/swisseph"
        CACHE STRING "Default ephemeris search path" )
endif()
add_definitions( -DPYSWE_DEFAULT_EPHE_PATH="${PYSWE_DEFAULT_EPHE_PATH}" )

if ( PYSWE_AUTO_SET_EPHE_PATH )
    add_definitions( -DPYSWE_AUTO_SET_EPHE_PATH=1 )
    message( STATUS "... Ephemeris path will be set to ${PYSWE_DEFAULT_EPHE_PATH} on module import..." )
else()
    add_definitions( -DPYSWE_AUTO_SET_EPHE_PATH=0 )
endif()

if ( PYSWE_USE_SWEPHELP )
    add_definitions( -DPYSWE_USE_SWEPHELP=1 )
    message( STATUS "... Extra functions will be compiled..." )
else()
    add_definitions( -DPYSWE_USE_SWEPHELP=0 )
endif()

# Find Python libs
find_package( PythonLibs ${PYSWE_MINIMUM_VERSION} )
if ( NOT PYTHONLIBS_FOUND )
    message( FATAL_ERROR "Cannot find Python libraries (version ${PYSWE_MINIMUM_PYTHON_VERSION})" )
else()
    message( STATUS "... Using Python version ${PYTHONLIBS_VERSION_STRING}" )
endif()

# Configure cswisseph
add_subdirectory( libswe )

# Configure swephelp
if ( PYSWE_USE_SWEPHELP )
    add_subdirectory( swephelp )
endif()

# Sources
set( SOURCES pyswisseph.c )

# Defines
if ( MSVC )
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
else()
    add_definitions( -std=gnu99 -g -O2 -Wall )
    if ( NOT MINGW )
        add_definitions( -fPIC )
    endif()
endif()

# Includes
include_directories( BEFORE libswe ${PYTHON_INCLUDE_DIRS} )

if ( PYSWE_USE_SWEPHELP )
    include_directories( BEFORE swephelp )
endif()

# Target
add_library( swisseph MODULE ${SOURCES} )
add_dependencies( swisseph swe )
if ( PYSWE_USE_SWEPHELP )
    add_dependencies( swisseph swephelp )
    if ( MSVC OR NOT SQLITE3_FOUND )
        add_dependencies( swisseph sqlite3 )
    endif()
endif()

# Linkage
if ( MSVC )
    target_link_libraries( swisseph swe ${PYTHON_LIBRARIES} )
elseif( MINGW )
    target_link_libraries( swisseph swe m dl ${PYTHON_LIBRARIES} )
else()
    target_link_libraries( swisseph swe m dl ${PYTHON_LIBRARIES} )
endif()
if ( PYSWE_USE_SWEPHELP )
    target_link_libraries( swisseph swephelp sqlite3 )
endif()

# Target properties
if ( WIN32 )
    set_target_properties( swisseph PROPERTIES SUFFIX .pyd )
    if ( MINGW )
        set_target_properties( swisseph PROPERTIES PREFIX "" )
    endif()
else()
    set_target_properties( swisseph PROPERTIES PREFIX "" )
endif()

# vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 :
