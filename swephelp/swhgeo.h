/*
    Swephelp

    Copyright 2007-2011 Stanislas Marquis <stnsls@gmail.com>

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

/** @file swhgeo.h
** @brief Geographical utilities (latitude, longitude, altitude)
*/

#ifndef SWHGEO_H
#define SWHGEO_H

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Get double from latitude or longitude string
**
** Get a double from a longitude or latitude expressed as a string like
** "{degrees}:{direction}:{minutes}:{seconds}".
** Directions are given in a single char, 'N' for north, 'S' for south,
** 'E' for east, 'W' for west.
**
** @param coord Latitude or longitude string
** @param ret Returned double
** @return 0 on success, or -1 if string is invalid
*/
int swh_geoc2d(const char *coord, double *ret);

/** @brief Extract degrees, minutes and seconds from a geographical coordinate
** @param coord Latitude or Longitude
** @param ret Returned degrees, minutes, seconds, declared as int[3]
** @return 0
*/
int swh_geod2i(double coord, int *ret);

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
int swh_geod2c(double coord, int maxdeg, char *ret);

/** @brief Get string from geographical latitude
**
** Get formated string for a latitude, like
** "{degrees}:{N|S}:{minutes}:{seconds}".
**
** @param coord latitude as double
** @param ret Buffer for returned string, declared as char[11]
** @return 0 on success, or -1 if latitude is invalid
*/
#define swh_geolat2c(coord, ret)        swh_geod2c((coord), 90, (ret))

/** @brief Get string from geographical longitude
**
** Get formated string for a longitude, like
** "{degrees}:{E|W}:{minutes}:{seconds}".
**
** @param coord latitude as double
** @param ret Buffer for returned string, declared as char[12]
** @return 0 on success, or -1 if latitude is invalid
*/
#define swh_geolon2c(coord, ret)        swh_geod2c((coord), 180, (ret))

#if SWH_USE_ALIASES

/** @def GeoLat
** @brief Latitude (as double)
*/
#define GeoLat      double

/** @def GeoLon
** @brief Longitude (as double)
*/
#define GeoLon      double

/** @def GeoCoord
** @brief Generic Geocoordinate (as double)
*/
#define GeoCoord    double

/** @def GeoAlt
** @brief Altitude (as integer)
*/
#define GeoAlt      int

/** @def GeoLat_Check
** @brief Check latitude validity
*/
#define GeoLat_Check(x)     (((x) < -90 || (x) > 90) ? (0) : (1))

/** @def GeoLon_Check
** @brief Check longitude validity
*/
#define GeoLon_Check(x)     (((x) < -180 || (x) > 180) ? (0) : (1))

/** @def GeoAlt_Check
** @brief Check altitude validity (must be >= 0, cf. swisseph doc)
*/
#define GeoAlt_Check(x)     (((x) < 0) ? (0) : (1))

/** @def GeoCoord_AsInt
** @brief Get degrees, minutes, seconds of a coordinate, in an int[3]
*/
#define GeoCoord_AsInt(x, y)        swh_geod2i((x), (y))

/** @def GeoCoord_AsDouble
** @brief Get a double from a geocoord char* representation
*/
#define GeoCoord_AsDouble(x, y)     swh_geoc2d((x), (y))

/** @def GeoLat_AsString
** @brief Get a char* representation of a latitude
*/
#define GeoLat_AsString(coord, ret)        swh_geolat2c((coord), (ret))

/** @def GeoLon_AsString
** @brief Get a char* representation of a longitude
*/
#define GeoLon_AsString(coord, ret)        swh_geolon2c((coord), (ret))

#endif /* SWH_USE_ALIASES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWHGEO_H */
