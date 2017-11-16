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

/** @file swhmisc.c
** @brief Misc experimental stuff
*/

#include <swephexp.h>

#include "swhmisc.h"

int swh_saturn_4_stars( const double jd, const int flag, double* ret, char* err )
{
    char starbuf[50];
    double xx[6];
    double* stars[2] = {0,0}; /* dummy assign */
    double midp, dist0, dist1, dist2;
    int i;

    /* Get bodies positions */
    i = swe_calc_ut( jd, SE_SATURN, flag, xx, err );
    if ( i < 0 )
        return -1;
    ret[0] = xx[0];

    strcpy( starbuf, "Aldebaran" );
    i = swe_fixstar_ut( starbuf, jd, flag, xx, err );
    if ( i < 0 )
        return -1;
    ret[1] = xx[0];

    strcpy( starbuf, "Regulus" );
    i = swe_fixstar_ut( starbuf, jd, flag, xx, err );
    if ( i < 0 )
        return -1;
    ret[2] = xx[0];

    strcpy( starbuf, "Antares" );
    i = swe_fixstar_ut( starbuf, jd, flag, xx, err );
    if ( i < 0 )
        return -1;
    ret[3] = xx[0];

    strcpy( starbuf, "Fomalhaut" );
    i = swe_fixstar_ut( starbuf, jd, flag, xx, err );
    if ( i < 0 )
        return -1;
    ret[4] = xx[0];

    /* Find nearest stars from Saturn */
    if ( ret[0] <= ret[1] || ret[0] > ret[4] )
    {
        stars[0] = &ret[4];
        stars[1] = &ret[1];
    }
    else if ( ret[0] <= ret[2] )
    {
        stars[0] = &ret[1];
        stars[1] = &ret[2];
    }
    else if ( ret[0] <= ret[3] )
    {
        stars[0] = &ret[2];
        stars[1] = &ret[3];
    }
    else if ( ret[0] <= ret[4] )
    {
        stars[0] = &ret[3];
        stars[1] = &ret[4];
    }

    /* Find midpoint between stars */
    midp = swe_deg_midp( *stars[0], *stars[1] );

    /* Find distance Saturn/midpoint */
    dist0 = fabs( swe_difdeg2n( ret[0], midp ) );

    /* Find which star is closer from saturn and calculate the index */
    dist1 = fabs( swe_difdeg2n( ret[0], *stars[0] ) );
    dist2 = fabs( swe_difdeg2n( ret[0], *stars[1] ) );

    if ( dist1 <= dist2 ) /* first is closer */
        ret[5] = dist0 / ( fabs( swe_difdeg2n( midp, *stars[0] ) ) / 100.0 );
    else /* second is closer */
        ret[5] = dist0 / ( fabs( swe_difdeg2n( midp, *stars[1] ) ) / 100.0 );
    return 0;
}

/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
