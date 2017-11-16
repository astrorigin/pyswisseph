/*
    Swephelp

    Copyright 2007-2017 Stanislas Marquis <stan@astrorigin.com>

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

/** @file swhraman.c
*/

#include <stdlib.h>

#include "swhdef.h"
#include "swhraman.h"

/** @brief Get Raman houses cusps
**
** Get Raman houses cusps (bhavamadhya or arambhasandhi), given the ascendant
** and midheaven cusps.
**
** @param asc Udaya lagna
** @param mc Madhya lagna
** @param ret Returned sputhas, declared as double[12]
** @param sandhi Return bhavamadhya (0) or arambhasandhi (1), boolean
** @return 0
*/
int swh_raman_houses(double asc, double mc, double *ret, int sandhi)
{
    double arc;
    if (sandhi == 0) /* we want bhavamadhya */
    {
        ret[0] = swe_degnorm(asc);
        ret[9] = swe_degnorm(mc);
    }
    else /* we want arambhasandhi */
    {
        arc = fabs(swe_difdeg2n(asc, mc)) / 6.0;
        ret[0] = swe_degnorm(asc - arc);
        ret[9] = swe_degnorm(mc - arc);
    }
    ret[6] = swe_degnorm(ret[0] + 180);
    ret[3] = swe_degnorm(ret[9] + 180);
    arc = fabs(swe_difdeg2n(ret[0], ret[9])) / 3.0;
    ret[11] = swe_degnorm(ret[0] - arc);
    ret[10] = swe_degnorm(ret[9] + arc);
    ret[4] = swe_degnorm(ret[10] + 180);
    ret[5] = swe_degnorm(ret[11] + 180);
    arc = fabs(swe_difdeg2n(ret[0], ret[3])) / 3.0;
    ret[1] = swe_degnorm(ret[0] + arc);
    ret[2] = swe_degnorm(ret[3] - arc);
    ret[7] = swe_degnorm(ret[1] + 180);
    ret[8] = swe_degnorm(ret[2] + 180);
    return 0;
}

/** @brief Get lord of sign
**
** Get planet number (lord of sign) for given sign number.
**
** @param sign Sign number [0:11]
** @return Planet number (SE_*), or -1 if sign is invalid
*/
int swh_lord(int sign)
{
    switch (sign)
    {
    case SWH_ARIES:
    case SWH_SCORPIO: return SE_MARS;
    case SWH_TAURUS:
    case SWH_LIBRA: return SE_VENUS;
    case SWH_GEMINI:
    case SWH_VIRGO: return SE_MERCURY;
    case SWH_CANCER: return SE_MOON;
    case SWH_LEO: return SE_SUN;
    case SWH_SAGITTARIUS:
    case SWH_PISCES: return SE_JUPITER;
    case SWH_CAPRICORN:
    case SWH_AQUARIUS: return SE_SATURN;
    default: return -1;
    }
}

/** @brief Get Nakshatra and Pada from longitude
**
** Get Nakshatra number [0:26] and Pada [0:3] from longitude.
**
** @param longitude Longitude on ecliptic
** @param ret Returned Nakshatra and Pada, declared as int[2]
** @return 0
*/
int swh_long2nakshatra(double longitude, int *ret)
{
    longitude = swe_degnorm(longitude);
    ret[0] = (int) (longitude / (40/3.0));
    ret[1] = (int) ((longitude - (ret[0] * (40/3.0))) / (10/3.0));
    return 0;
}

/** @brief Get Nakshatra name
**
** Get Nakshatra name from Nakshatra number.
**
** @param nakshatra Nakshatra number [0:26]
** @param str Buffer for returned string, declared as char[15]
** @return 0 on success, or -1 if nakshatra is invalid
*/
int swh_get_nakshatra_name(int nakshatra, char *str)
{
    switch (nakshatra)
    {
    case SWH_ASWINI: strcpy(str, "Aswini"); return 0;
    case SWH_BHARANI: strcpy(str, "Bharani"); return 0;
    case SWH_KRITHIKA: strcpy(str, "Krithika"); return 0;
    case SWH_ROHINI: strcpy(str, "Rohini"); return 0;
    case SWH_MRIGASIRA: strcpy(str, "Mrigasira"); return 0;
    case SWH_ARIDRA: strcpy(str, "Aridra"); return 0;
    case SWH_PUNARVASU: strcpy(str, "Punarvasu"); return 0;
    case SWH_PUSHYAMI: strcpy(str, "Pushyami"); return 0;
    case SWH_ASLESHA: strcpy(str, "Aslesha"); return 0;
    case SWH_MAKHA: strcpy(str, "Makha"); return 0;
    case SWH_PUBBA: strcpy(str, "Pubba"); return 0;
    case SWH_UTTARA: strcpy(str, "Uttara"); return 0;
    case SWH_HASTA: strcpy(str, "Hasta"); return 0;
    case SWH_CHITTA: strcpy(str, "Chitta"); return 0;
    case SWH_SWATHI: strcpy(str, "Swathi"); return 0;
    case SWH_VISHAKA: strcpy(str, "Vishaka"); return 0;
    case SWH_ANURADHA: strcpy(str, "Anuradha"); return 0;
    case SWH_JYESTA: strcpy(str, "Jyesta"); return 0;
    case SWH_MOOLA: strcpy(str, "Moola"); return 0;
    case SWH_POORVASHADA: strcpy(str, "Poorvashada"); return 0;
    case SWH_UTTARASHADA: strcpy(str, "Uttarashada"); return 0;
    case SWH_SRAVANA: strcpy(str, "Sravana"); return 0;
    case SWH_DHANISHTA: strcpy(str, "Dhanishta"); return 0;
    case SWH_SATABISHA: strcpy(str, "Satabhisha"); return 0;
    case SWH_POORVABHADRA: strcpy(str, "Poorvabhadra"); return 0;
    case SWH_UTTARABHADRA: strcpy(str, "Uttarabhadra"); return 0;
    case SWH_REVATHI: strcpy(str, "Revathi"); return 0;
    default: return -1;
    }
}

/** @brief Get Rasi difference
**
** Get number of rasi between two rasis, from 0 to 11.
** That is used for drishti.
**
** @param r1 Rasi number [0:11]
** @param r2 Rasi number [0:11]
** @return Rasi difference [0:11]
*/
int swh_rasi_dif(int r1, int r2)
{
    r1 = swh_rasinorm(r1);
    r2 = swh_rasinorm(r2);
    if (r1 == r2) return 0;
    else if (r1 < r2) return 12 - (r2 - r1);
    else return r1 - r2;
}

/** @brief Get Rasi difference
**
** Get number of rasi between two rasis, from -5 to 6.
**
** @param r1 Rasi number [0:11]
** @param r2 Rasi number [0:11]
** @return Rasi difference [-5:6]
*/
int swh_rasi_dif2(int r1, int r2)
{
    const int i = swh_rasi_dif(r1, r2);
    return (i > 6) ? (-6 + (i - 6)) : (i);
}

/** @brief Get Naisargika relation between planets
**
** Get naisargika relation between planets.
**
** @param gr1 Planet number
** @param gr2 Planet number
** @param ret Relation returned Satru (-1) Sama (0) or Mitra (1)
** @return 0 on success, or -1 if a planet is invalid
*/
int swh_naisargika_relation(int gr1, int gr2, int *ret)
{
    switch (gr1)
    {
    case SE_SUN:
        switch (gr2)
        {
        case SE_MOON: case SE_MARS: case SE_JUPITER: goto mitra;
        case SE_MERCURY: goto sama;
        case SE_VENUS: case SE_SATURN: goto satru;
        }
    case SE_MOON:
        switch (gr2)
        {
        case SE_SUN: case SE_MERCURY: goto mitra;
        case SE_MARS: case SE_JUPITER: case SE_VENUS: case SE_SATURN: goto sama;
        }
    case SE_MERCURY:
        switch (gr2)
        {
        case SE_SUN: case SE_VENUS: goto mitra;
        case SE_MARS: case SE_JUPITER: case SE_SATURN: goto sama;
        case SE_MOON: goto satru;
        }
    case SE_VENUS:
        switch (gr2)
        {
        case SE_MERCURY: case SE_SATURN: goto mitra;
        case SE_MARS: case SE_JUPITER: goto sama;
        case SE_SUN: case SE_MOON: goto satru;
        }
    case SE_MARS:
        switch (gr2)
        {
        case SE_SUN: case SE_MOON: case SE_JUPITER: goto mitra;
        case SE_VENUS: case SE_SATURN: goto sama;
        case SE_MERCURY: goto satru;
        }
    case SE_JUPITER:
        switch (gr2)
        {
        case SE_SUN: case SE_MOON: case SE_MARS: goto mitra;
        case SE_SATURN: goto sama;
        case SE_MERCURY: case SE_VENUS: goto satru;
        }
    case SE_SATURN:
        switch (gr2)
        {
        case SE_MERCURY: case SE_VENUS: goto mitra;
        case SE_JUPITER: goto sama;
        case SE_SUN: case SE_MOON: case SE_MARS: goto satru;
        }
    }
    return -1;
    mitra: *ret = 1; return 0;
    sama: *ret = 0; return 0;
    satru: *ret = -1; return 0;
}

/** @brief Get residential strength of a planet
**
** Get the residential strength of a planet, given the bhavamadhya longitudes.
**
** @param graha Graha longitude
** @param bm 12 Bhavamadhya longitudes
** @param ret Residential strength returned
** @return 0 on success, or -1 on error
*/
int swh_residential_strength(double graha, const double *bm, double *ret)
{
    int i;
    double s, arc1, arc2;
    static const int idx[] = {0,1,2,3,4,5,6,7,8,9,10,11,0};
    for (i = 0; i < 12; ++i)
    {
        if (graha == bm[idx[i]] || graha == bm[idx[i+1]])
        {
            *ret = 0; return 0;
        }
        arc1 = swe_difdeg2n(bm[idx[i]], graha);
        arc2 = swe_difdeg2n(bm[idx[i+1]], graha);
        if ((arc1 >= 0 ? 1 : 0) !=
            (arc2 >= 0 ? 1 : 0)
            && fabs(arc1) + fabs(arc2) < 180)
        {
            s = swe_deg_midp(bm[idx[i]], bm[idx[i+1]]);
            if (graha == s)
            {
                *ret = 1.0; return 0;
            }
            arc1 = fabs(arc1);
            arc2 = fabs(arc2);
            if (arc1 < arc2)
            {
                *ret = (arc1 / fabs(swe_difdeg2n(s, bm[idx[i]])));
            }
            else
            {
                *ret = (arc2 / fabs(swe_difdeg2n(s, bm[idx[i+1]])));
            }
            return 0;
        }
    }
    return -1;
}

/* *** Sthanabala ***/

/** @brief Get Ochchabala
**
** Get the exaltation strength of a planet.
**
** @param graha Planet number (SE_*)
** @param sputha Planet longitude on ecliptic [0:360[
** @return Ochchabala in shashtiamsa, or -1 if planet is invalid
*/
double swh_ochchabala(int graha, double sputha)
{
    int x;
    switch (graha)
    {
    case SE_SUN: x = 190; break;
    case SE_MOON: x = 213; break;
    case SE_MERCURY: x = 345; break;
    case SE_VENUS: x = 177; break;
    case SE_MARS: x = 118; break;
    case SE_JUPITER: x = 275; break;
    case SE_SATURN: x = 20; break;
    default: return -1;
    }
    return fabs(swe_difdeg2n(sputha, x)) / 3.0;
}

/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
