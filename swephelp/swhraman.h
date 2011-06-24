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

/** @file swhraman.h
** @brief B.V.Raman's astrology
*/

#ifndef SWHRAMAN_H
#define SWHRAMAN_H

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <swephexp.h>

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
int swh_raman_houses(double asc, double mc, double *ret, int sandhi);

/** @brief Get lord of sign
**
** Get planet number (lord of sign) for given sign number.
**
** @param sign Sign number [0:11]
** @return Planet number (SE_*), or -1 if sign is invalid
*/
int swh_lord(int sign);

/** @brief Get Rasi from longitude
**
** Get Rasi number [0:11] from longitude.
**
** @param longitude Longitude on ecliptic (double)
** @return Rasi number [0:11]
*/
#define swh_long2rasi(longitude)    ((int) (swe_degnorm(longitude) / 30.0))

/** @brief Get Navamsa from longitude
**
** Get Navamsa number [0:11] from longitude.
**
** @param longitude Longitude on ecliptic (double)
** @return Navamsa number [0:11]
*/
#define swh_long2navamsa(longitude)     ((int) (swe_degnorm(longitude) / (10/3.0)) % 12)

/** @brief Get Nakshatra and Pada from longitude
**
** Get Nakshatra number [0:26] and Pada [0:3] from longitude.
**
** @param longitude Longitude on ecliptic
** @param ret Returned Nakshatra and Pada, declared as int[2]
** @return 0
*/
int swh_long2nakshatra(double longitude, int *ret);

/** @brief Get Nakshatra name
**
** Get Nakshatra name from Nakshatra number.
**
** @param nakshatra Nakshatra number [0:26]
** @param str Buffer for returned string, declared as char[15]
** @return 0 on success, or -1 if nakshatra is invalid
*/
int swh_get_nakshatra_name(int nakshatra, char *str);

/** @brief Get normalized rasi number
**
** Get a normalized rasi number between 0 and 11.
**
** @param rasi Rasi number (int)
** @return Normalized rasi number [0:11]
*/
#define swh_rasinorm(rasi)      ((rasi) < 0 ?\
        ((rasi) + (12 * (1 + (int) ((rasi) / -12)))) % 12 : (rasi) % 12)

/** @brief Get Rasi difference
**
** Get number of rasi between two rasis, from 0 to 11.
** That is used for drishti.
**
** @param r1 Rasi number [0:11]
** @param r2 Rasi number [0:11]
** @return Rasi difference [0:11]
*/
int swh_rasi_dif(int r1, int r2);

/** @brief Get Rasi difference
**
** Get number of rasi between two rasis, from -5 to 6.
**
** @param r1 Rasi number [0:11]
** @param r2 Rasi number [0:11]
** @return Rasi difference [-5:6]
*/
int swh_rasi_dif2(int r1, int r2);

/** @brief Get Tatkalika relation between planets
**
** Get tatkalika relation between two planets.
**
** @param r1 Rasi number of graha (int) [0:11]
** @param r2 Rasi number of graha (int) [0:11]
** @return Tatkalika relation Satru (-1) or Mitra (1)
*/
#define swh_tatkalika_relation(r1, r2)  (abs(swh_rasi_dif2((r1), (r2))) <= 3 ? 1 : -1)

/** @brief Get Naisargika relation between planets
**
** Get naisargika relation between planets.
**
** @param gr1 Planet number
** @param gr2 Planet number
** @param ret Relation returned Satru (-1) Sama (0) or Mitra (1)
** @return 0 on success, or -1 if a planet is invalid
*/
int swh_naisargika_relation(int gr1, int gr2, int *ret);

/** @brief Get residential strength of a planet
**
** Get the residential strength of a planet, given the bhavamadhya longitudes.
**
** @param graha Graha longitude
** @param bm 12 Bhavamadhya longitudes
** @param ret Residential strength returned
** @return 0 on success, or -1 on error
*/
int swh_residential_strength(double graha, const double *bm, double *ret);

/** @brief Get Ochchabala
**
** Get the exaltation strength of a planet.
**
** @param graha Planet number (SE_*)
** @param sputha Planet longitude on ecliptic [0:360[
** @return Ochchabala in shashtiamsa, or -1 if planet is invalid
*/
double swh_ochchabala(int graha, double sputha);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWHRAMAN_H */
