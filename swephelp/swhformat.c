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

/** @file swhformat.c
** @brief swephelp formating functions
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "swhformat.h"
#include <swephexp.h>

/** @brief Get degrees, sign number, minutes, seconds, from longitude position
**
** Split a longitude position to a more usual format.
**
** @param pos Longitude position [0;360[
** @param ret Results, declared as int[4] (deg, sign, min, sec)
** @return 0
*/
int swh_degsplit(double pos, int *ret)
{
    pos = swe_degnorm(pos);
    ret[1] = (int) floor(pos/30.0);
    pos -= ret[1]*30;
    ret[0] = (int) floor(pos);
    pos -= ret[0];
    ret[2] = (int) floor(pos*60);
    pos -= ret[2]/60.0;
    ret[3] = (int) floor(pos*3600);
    return 0;
}

/** @brief Get the 3-letters string representing a sign number
** @param sign Sign number [0;11]
** @param str Returned string, declared as char[4]
** @return 0, or -1 if sign was invalid
*/
int swh_signtostr(int sign, char *str)
{
    switch (sign)
    {
    case 0: strcpy(str, "Ari"); return 0;
    case 1: strcpy(str, "Tau"); return 0;
    case 2: strcpy(str, "Gem"); return 0;
    case 3: strcpy(str, "Can"); return 0;
    case 4: strcpy(str, "Leo"); return 0;
    case 5: strcpy(str, "Vir"); return 0;
    case 6: strcpy(str, "Lib"); return 0;
    case 7: strcpy(str, "Sco"); return 0;
    case 8: strcpy(str, "Sag"); return 0;
    case 9: strcpy(str, "Cap"); return 0;
    case 10: strcpy(str, "Aqu"); return 0;
    case 11: strcpy(str, "Pis"); return 0;
    default: return -1;
    }
}

/** @brief Get house system name
** @param hsys House system char [PKRCBOAEHVXGU]
** @param str Returned string, declared as char[25]
** @return 0, or -1 if house system is unknown
*/
int swh_house_system_name(char hsys, char *str)
{
    switch (hsys)
    {
    case 'P': strcpy(str, "Placidus"); return 0;
    case 'K': strcpy(str, "Koch"); return 0;
    case 'R': strcpy(str, "Regiomontanus"); return 0;
    case 'C': strcpy(str, "Campanus"); return 0;
    case 'B': strcpy(str, "Alcabitius"); return 0;
    case 'O': strcpy(str, "Porphyry"); return 0;
    case 'A': strcpy(str, "Equal"); return 0;
    case 'E': strcpy(str, "Equal"); return 0;
    case 'H': strcpy(str, "Horizon/azimuth"); return 0;
    case 'V': strcpy(str, "Equal Vehlow"); return 0;
    case 'X': strcpy(str, "Axial rotation/meridian"); return 0;
    case 'G': strcpy(str, "Gauquelin"); return 0;
    case 'U': strcpy(str, "Krusinski"); return 0;
    case 'W': strcpy(str, "Whole sign"); return 0;
    default: return -1;
    }
}

/** @brief Get house system unique id
** @param hsys House system char identifier (see swisseph docs)
** @return Identifier, or -1 if house system invalid
*/
int swh_house_system_id(char hsys)
{
    switch (hsys)
    {
    case 'P': return 0;
    case 'K': return 1;
    case 'R': return 2;
    case 'C': return 3;
    case 'B': return 4;
    case 'O': return 5;
    case 'A': return 6;
    case 'E': return 6; /* same */
    case 'H': return 7;
    case 'V': return 8;
    case 'X': return 9;
    case 'G': return 10;
    case 'U': return 11;
    case 'W': return 12;
    default: return -1;
    }
}

/** @brief Get house system char
** @param hsys House system int identifier
** @return iIdentifier, or -1 if house system invalid
*/
char swh_house_system_char(int hsys)
{
    switch (hsys)
    {
    case 0: return 'P';
    case 1: return 'K';
    case 2: return 'R';
    case 3: return 'C';
    case 4: return 'B';
    case 5: return 'O';
    case 6: return 'A';
    /* case 6: return 'E'; / same */
    case 7: return 'H';
    case 8: return 'V';
    case 9: return 'X';
    case 10: return 'G';
    case 11: return 'U';
    case 12: return 'W';
    default: return -1;
    }
}

/** @brief Get sidereal mode flag
**
** Return the swisseph sidereal mode flag from the given sidereal mode index.
**
** @param sidmode
** @return Flag, or -1 if invalid mode
*/
int swh_sidereal_mode_flag(int sidmode)
{
    if (sidmode == 0) return 256; /* no western/tropical flag in swisseph */
    else if (sidmode == 22) return 255; /* user defined */
    else if (sidmode > 0 && sidmode < 22) return sidmode - 1;
    else return -1;
}

/** @brief Get sidereal mode unique identifier
** @param sidmode Sidereal mode identifier
** @return index [0:22]
*/
int swh_sidereal_mode_id(int sidmode)
{
    if (sidmode == 256) return 0; /* western/tropical */
    else if (sidmode == 255) return 22; /* user-defined */
    else if (sidmode > -1 && sidmode < 21) return sidmode + 1;
    else return -1;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
