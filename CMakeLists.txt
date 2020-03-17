# Pyswisseph CMakeLists.txt

cmake_minimum_required( VERSION 2.8 )

project( pyswisseph )

message( STATUS "-- Configuring pyswisseph..." )

# MinGW variable
if ( WIN32 AND NOT MSVC )
    set( MINGW ON )
else()
    set( MINGW OFF )
endif()

# Python version
set( PYSWE_DESIRED_PYTHON_VERSION
    3.6
    CACHE STRING "Desired Python version" )

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
find_package( PythonLibs ${PYSWE_DESIRED_PYTHON_VERSION} )
if ( NOT PYTHONLIBS_FOUND )
    message( FATAL_ERROR "Cannot find Python libraries (version ${PYSWE_DESIRED_PYTHON_VERSION})" )
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
    add_definitions( -std=gnu99 -fno-strict-aliasing -DNDEBUG
        -g -fwrapv -O2 -Wall -Wstrict-prototypes )
    if ( NOT MINGW )
        add_definitions( -pthread -fPIC )
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
endif()

# Linkage
if ( MSVC )
    target_link_libraries( swisseph swe ${PYTHON_LIBRARIES} )
elseif( MINGW )
    target_link_libraries( swisseph swe m ${PYTHON_LIBRARIES}
        pthread -Wl,-O1 -Wl,-Bsymbolic-functions )
else()
    target_link_libraries( swisseph swe m ${PYTHON_LIBRARIES}
        -pthread -Wl,-O1 -Wl,-Bsymbolic-functions )
endif()
if ( PYSWE_USE_SWEPHELP )
    target_link_libraries( swisseph swephelp )
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
