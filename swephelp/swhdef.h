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

/** @file swhdef.h
** @brief swephelp defines header file
**
** Contains various usefull defines.
*/

#ifndef SWHDEF_H
#define SWHDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Aspects */
#define SWH_CONJUNCTION     0
#define SWH_SQUISEXTILE     15
#define SWH_SEMINOVILE      20
#define SWH_SQUISQUARE      22.5
#define SWH_UNDECILE        (360/11.0)
#define SWH_SEMISEXTILE     30
#define SWH_SEMIQUINTILE    36
#define SWH_NOVILE          40
#define SWH_SEMISQUARE      45
#define SWH_SEPTILE         (360/7.0)
#define SWH_SEXTILE         60
#define SWH_BIUNDECILE      ((360/11.0)*2)
#define SWH_QUINTILE        72
#define SWH_BINOVILE        80
#define SWH_SQUARE          90
#define SWH_TRIUNDECILE     ((360/11.0)*3)
#define SWH_BISEPTILE       ((360/7.0)*2)
#define SWH_TRINE           120
#define SWH_QUADUNDECILE    ((360/11.0)*4)
#define SWH_SESQUISQUARE    135
#define SWH_BIQUINTILE      144
#define SWH_QUINCUNX        150
#define SWH_TRISEPTILE      ((360/7.0)*3)
#define SWH_QUATRONOVILE    160
#define SWH_QUINUNDECILE    ((360/11.0)*5)
#define SWH_OPPOSITION      180

/* Signs */
#define SWH_ARIES       0
#define SWH_TAURUS      1
#define SWH_GEMINI      2
#define SWH_CANCER      3
#define SWH_LEO         4
#define SWH_VIRGO       5
#define SWH_LIBRA       6
#define SWH_SCORPIO     7
#define SWH_SAGITTARIUS 8
#define SWH_CAPRICORN   9
#define SWH_AQUARIUS    10
#define SWH_PISCES      11

#define SWH_MESHA       SWH_ARIES
#define SWH_VRISHABA    SWH_TAURUS
#define SWH_MITHUNA     SWH_GEMINI
#define SWH_KATAKA      SWH_CANCER
#define SWH_SIMHA       SWH_LEO
#define SWH_KANYA       SWH_VIRGO
#define SWH_THULA       SWH_LIBRA
#define SWH_VRISHIKA    SWH_SCORPIO
#define SWH_DHANUS      SWH_SAGITTARIUS
#define SWH_MAKARA      SWH_CAPRICORN
#define SWH_KUMBHA      SWH_AQUARIUS
#define SWH_MEENA       SWH_PISCES

/* Planets */
#define SWH_RAVI        0
#define SWH_CHANDRA     1
#define SWH_BUDHA       2
#define SWH_SUKRA       3
#define SWH_KUJA        4
#define SWH_GURU        5
#define SWH_SANI        6
#define SWH_RAHU        10
#define SWH_KETU        -10

#define SWH_SURYA       SWH_RAVI
#define SWH_SOMA        SWH_CHANDRA
#define SWH_SOUMYA      SWH_BUDHA
#define SWH_BHARGAVA    SWH_SUKRA
#define SWH_ANGARAKA    SWH_KUJA
#define SWH_BRIHASPATI  SWH_GURU
#define SWH_MANDA       SWH_SANI
#define SWH_THAMA       SWH_RAHU
#define SWH_SIKHI       SWH_KETU

/* Nakshatras */
#define SWH_ASWINI          0
#define SWH_BHARANI         1
#define SWH_KRITHIKA        2
#define SWH_ROHINI          3
#define SWH_MRIGASIRA       4
#define SWH_ARIDRA          5
#define SWH_PUNARVASU       6
#define SWH_PUSHYAMI        7
#define SWH_ASLESHA         8
#define SWH_MAKHA           9
#define SWH_PUBBA           10
#define SWH_UTTARA          11
#define SWH_HASTA           12
#define SWH_CHITTA          13
#define SWH_SWATHI          14
#define SWH_VISHAKA         15
#define SWH_ANURADHA        16
#define SWH_JYESTA          17
#define SWH_MOOLA           18
#define SWH_POORVASHADA     19
#define SWH_UTTARASHADA     20
#define SWH_SRAVANA         21
#define SWH_DHANISHTA       22
#define SWH_SATABISHA       23
#define SWH_POORVABHADRA    24
#define SWH_UTTARABHADRA    25
#define SWH_REVATHI         26

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* swhdef.h */
