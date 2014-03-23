# Swephelp CMakeLists.txt

cmake_minimum_required( VERSION 2.8 )
project( swephelp )

message( STATUS "-- Configuring swephelp..." )

set( SOURCES
    swhdatetime.c
    swhformat.c
    swhgeo.c
    swhmisc.c
    swhraman.c
    swhsearch.c
    swhutil.c
    )

include_directories( BEFORE . ../libswe )

if ( MSVC )
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
else()
    add_definitions( -g -O9 -Wall )
    if ( NOT MINGW )
        add_definitions( -fPIC )
    endif()
endif()

add_library( swephelp STATIC ${SOURCES} )

# vi: set fenc=utf-8 ff=unix et sw=4 ts=3 sts=4 :
