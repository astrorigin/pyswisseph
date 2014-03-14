# Swisseph CMakeLists.txt

cmake_minimum_required( VERSION 2.8 )
project( cswisseph )

message( STATUS "-- Configuring cswisseph..." )

set( SOURCES
    swecl.c
    swedate.c
    swehel.c
    swehouse.c
    swejpl.c
    swemmoon.c
    swemplan.c
    #swemptab.c
    swepcalc.c
    sweph.c
    swephlib.c
    )

include_directories( BEFORE . )

if ( MSVC )
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
else()
    add_definitions( -g -O9 -Wall )
    if ( NOT MINGW )
        add_definitions( -fPIC )
    endif()
endif()

add_library( swe STATIC ${SOURCES} )

# vi: set ai et sw=4:
