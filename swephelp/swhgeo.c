/*
    Swephelp

    Copyright 2007-2014 Stanislas Marquis <smarquis@astrorigin.ch>

    Swephelp is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    Swephelp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Swephelp.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file swhgeo.c
** @brief Geographical utilities (latitude, longitude, altitude)
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swhgeo.h"
#include "swhwin.h"

/** @brief Get double from latitude or longitude string
**
** Get a double from a longitude or latitude expressed as a string like
** "{degrees}:{direction}:{minutes}:{seconds}".
** Directions are given as a single char, 'N' for north, 'S' for south,
** 'E' for east, 'W' for west.
**
** @param coord Latitude or longitude string
** @param ret Returned double
** @return 0 on success, or -1 if string is invalid
*/
int swh_geoc2d(const char *coord, double *ret)
{
    int deg, dir, min, sec;
#ifndef NDEBUG
    int degmax; /* used in asserts only */
#endif
    char *ptr, buf[12];
    strcpy(buf, coord);
#ifndef WIN32
    char *saveptr;
    ptr = strtok_r(buf, ":", &saveptr);
#else
    ptr = strtok(buf, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        deg = atoi(ptr);
    assert(deg >= 0);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL)
        return -1;
    else
    {
        if (strcmp(ptr, "N") == 0 || strcmp(ptr, "E") == 0)
        {
#ifndef NDEBUG
            degmax = 90;
#endif
            dir = 1;
        }
        else if (strcmp(ptr, "S") == 0 || strcmp(ptr, "W") == 0)
        {
#ifndef NDEBUG
            degmax = 180;
#endif
            dir = 0;
        }
        else
            return -1;
    }
    assert(deg <= degmax);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        min = atoi(ptr);
    assert(deg == degmax ? min == 0 : min >= 0 && min <= 59);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        sec = atoi(ptr);
    assert(deg == degmax ? sec == 0 : sec >= 0 && sec <= 59);
    *ret = (double) (dir ?
        (deg + ((1.0/60) * min) + ((1.0/3600) * sec)) :
        -(deg + ((1.0/60) * min) + ((1.0/3600) * sec)));
    return 0;
}

/** @brief Extract degrees, minutes and seconds from a geographical coordinate
** @param coord Latitude or Longitude
** @param ret Returned degrees, minutes, seconds, declared as int[3]
** @return 0
*/
int swh_geod2i(double coord, int *ret)
{
    coord = fabs(coord);
    ret[0] = (int) floor(coord);
    coord -= ret[0];
    ret[1] = (int) lround(coord * 60);
    coord -= ret[1] / 60.0;
    ret[2] = (int) lround(coord * 3600);
    if (ret[2] < 0) ret[2] = 0;
    return 0;
}

/** @brief Get string from geographical coordinates
**
** Get formated string for a geographical coordinate, like
** "{degrees}:{N|S|E|W}:{minutes}:{seconds}".
**
** @remarks Use the defined macros swh_geolat2c swh_geolon2c instead.
**
** @param coord longitude as double
** @param ret Buffer for returned string, declared as char[12]
** @param maxdeg 90 for latitude, 180 for longitude
** @return 0 on success, or -1 if coord is invalid
*/
int swh_geod2c(double coord, int maxdeg, char *ret)
{
    int deg, dir, min, sec;
    if (coord < -(maxdeg) || coord > maxdeg)
        return -1;
    if (coord >= 0)
    {
        deg = (int) floor(coord);
        dir = 1;
    }
    else
    {
        deg = (int) fabs(ceil(coord));
        dir = 0;
    }
    coord = fabs(coord) - deg;
    min = (int) lround(coord * 60);
    coord -= min / 60.0;
    sec = (int) lround(coord * 3600);
    if (maxdeg == 90) /* latitude */
        sprintf(ret, "%.2d:%s:%.2d:%.2d", deg, dir ? "N" : "S", min, sec);
    else /* assuming longitude */
        sprintf(ret, "%.3d:%s:%.2d:%.2d", deg, dir ? "E" : "W", min, sec);
    return 0;
}

/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
