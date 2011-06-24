#!/usr/bin/env python
#-*- coding: utf-8 -*-

"""
Find next today's info...

"""

import swisseph as swe
swe.set_ephe_path('/usr/local/share/swisseph')

lat = swe._geocoord2d('46:N:31:0')
lon = swe._geocoord2d('6:E:38:0')
alt = 500
swe.set_topo(lon, lat, alt);

jd = swe._jdnow()

jdret, pos, cusps, ascmc = swe._next_aspect_cusp2(swe.SUN, 0, 1, jd,
    lat, lon, 'P', flag=swe.FLG_SPEED+swe.FLG_SWIEPH+swe.FLG_TOPOCTR)

print('Date: '+str(swe._revjul(jdret[0])))

planets = (swe.SUN, swe.MOON, swe.MERCURY, swe.VENUS, swe.MARS, swe.JUPITER,
    swe.SATURN, swe.URANUS, swe.NEPTUNE, swe.PLUTO, swe.MEAN_NODE, swe.MEAN_APOG)

for p in planets:
    print(swe.get_planet_name(p),
        swe.calc_ut(jdret[0], p, flag=swe.FLG_SPEED+swe.FLG_SWIEPH+swe.FLG_TOPOCTR)[0])

cusps, ascmc = swe.houses_ex(jdret[0], lat, lon, 'P', flag=swe.FLG_SPEED+swe.FLG_SWIEPH+swe.FLG_TOPOCTR)

print('Asc: '+str(ascmc[0]))
print('Mc:  '+str(ascmc[1]))

#.

