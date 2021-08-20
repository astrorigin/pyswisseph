#!/usr/bin/env python3

import swisseph as swe
import sys

def main():
    epheflag = swe.FLG_SWIEPH
    gregflag = swe.GREG_CAL
    year = 2017
    month = 4
    day = 12
    geolon = 76.5
    geolat = 30.0
    geoalt = 0.0
    # pressure & temperature
    # irrelevant for hindu method, can be set to 0
    atmo = (1013.25, 15)
    geopos = (geolon, geolat, geoalt) # also irrelevant for hindu method
    swe.set_topo(*geopos)
    pl = swe.SUN
    # calculate the Julian day number of the date at 0:00 UT
    tjd = swe.julday(year, month, day, 0, gregflag)
    # convert geographic longitude to time (day fraction) and subtract it
    # from tjd
    # this method should be good for all geographic latitudes except near in
    # polar regions
    dt = geolon / 360.0
    tjd = tjd - dt
    # calculation flag for Hindu risings/settings
    rsmi = swe.CALC_RISE | swe.BIT_HINDU_RISING
    res, tret = swe.rise_trans(tjd, pl, rsmi, geopos, atmo[0], atmo[1], epheflag)
    if (res != 0):
        print('sunrise not found.')
        sys.exit(1)
    trise = tret[0]
    # conversion to local time zone must be made by the user.
    # The Swiss Ephemeris does not have a function for that.
    # After that, the Julian day number of the rising time can be converted
    # into date and time:
    y, m, d, h = swe.revjul(trise, gregflag)
    print('sunrise: date=%d/%02d/%02d, hour=%.6f UT' % (y, m, d, h))
    # To calculate the time of the sunset, you can either use the same
    # tjd increased or trise as start date for the search.
    rsmi = swe.CALC_SET | swe.BIT_DISC_CENTER | swe.BIT_NO_REFRACTION
    res, tret = swe.rise_trans(tjd, pl, rsmi, geopos, atmo[0], atmo[1], epheflag)
    if (res != 0):
        print('sunset not found.')
        sys.exit(1)
    tset = tret[0]
    y, m, d, h = swe.revjul(tset, gregflag)
    print('sunset: date=%d/%02d/%02d, hour=%.6f UT' % (y, m, d, h))

if __name__ == '__main__':
    main()

