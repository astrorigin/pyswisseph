#!/usr/bin/env python3

import swisseph as swe

swe.set_ephe_path("...")

whicheph = 0 # default ephemeris
tjd_start = 2451545 # Julian day number for Jan 1st 2000
fltype = swe.ECL_TOTAL | swe.ECL_CENTRAL | swe.ECL_NONCENTRAL

# find next eclipse anywhere on earth
eclflag, tret = swe.sol_eclipse_when_glob(tjd_start, whicheph, fltype)

# the time of the greatest eclipse has been returned in tret[0]
# now we can find geographical position of the eclipse maximum
tjd_start = tret[0]
eclflag, geopos, attr = swe.sol_eclipse_where(tjd_start, whicheph)

# the position of the eclipse maximum is in geopos[0] and geopos[1]
# now we can calculate the four contacts for this place
# the start time is chosen a day before the maximum eclipse.
tjd_start = tret[0] - 1;
lon = geopos[0]
lat = geopos[1]
alt = 0 # 11°S 2°E south atlantic ocean, altitude is zero
eclflag, tret, attr = swe.sol_eclipse_when_loc(tjd_start, (lon, lat, alt), whicheph)

# now tret contains the following values:
print("time of greatest eclipse", swe.revjul(tret[0]))
print("first contact", swe.revjul(tret[1]))
print("second contact", swe.revjul(tret[2]))
print("third contact", swe.revjul(tret[3]))
print("fourth contact", swe.revjul(tret[4]))

