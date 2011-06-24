/*
    Swephelp

    Copyright 2007-2009 Stanislas Marquis <stnsls@gmail.com>

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

/** @file swhformat.h
** @brief swephelp formating functions
*/

#ifndef SWHFORMAT_H
#define SWHFORMAT_H

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Get degrees, sign number, minutes, seconds, from longitude position
**
** Split a longitude position to a more usual format.
**
** @param pos Longitude position [0;360[
** @param ret Results, declared as int[4] (deg, sign, min, sec)
** @return 0
*/
int swh_degsplit(double pos, int *ret);

/** @brief Get the 3-letters string representing a sign number
** @param sign Sign number [0;11]
** @param str Returned string, declared as char[4]
** @return 0, or -1 if sign was invalid
*/
int swh_signtostr(int sign, char *str);

/** @brief Get house system name
** @param hsys House system char [PKRCBOAEHVXGU]
** @param str Returned string, declared as char[25]
** @return 0, or -1 if house system is unknown
*/
int swh_house_system_name(char hsys, char *str);

/** @brief Get house system unique id
** @param hsys House system char identifier (see swisseph docs)
** @return Identifier, or -1 if house system invalid
*/
int swh_house_system_id(char hsys);

/** @brief Get house system char
** @param hsys House system int identifier
** @return iIdentifier, or -1 if house system invalid
*/
char swh_house_system_char(int hsys);

/** @brief Get sidereal mode flag
**
** Return the swisseph sidereal mode flag from the given sidereal mode index.
**
** @param sidmode
** @return Flag, or -1 if invalid mode
*/
int swh_sidereal_mode_flag(int sidmode);

/** @brief Get sidereal mode unique identifier
** @param sidmode Sidereal mode identifier
** @return index [0:22]
*/
int swh_sidereal_mode_id(int sidmode);

#if SWH_USE_ALIASES

/** @def HouseSystem_AsCharP
*/
#define HouseSystem_AsCharP(x)      swh_house_system_name(x)

/** @def HouseSystem_AsChar
*/
#define HouseSystem_AsChar(x)       swh_house_system_char(x)

/** @def HouseSystem_AsInt
*/
#define HouseSystem_AsInt(x)        swh_house_system_id(x)

/** @def SiderealMode_AsFlag
*/
#define SiderealMode_AsFlag(x)      swh_sidereal_mode_flag(x)

/** @def SiderealMode_AsInt
*/
#define SiderealMode_AsInt(x)       swh_sidereal_mode_id(x)

#endif /* SWH_USE_ALIASES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWHFORMAT_H */
