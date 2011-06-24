#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Get the aspectarian for the next days.
Example: « python aspectarian.py <numberOfDays> »


"""

import sys
from math import floor
import swisseph as swe

swe.set_ephe_path('/usr/local/share/swisseph')

jdstart = swe._utcnow()
jdstop = jdstart + int(sys.argv[1])

planets = (swe.SUN, swe.MOON, swe.MERCURY, swe.VENUS, swe.MARS, swe.JUPITER,
	swe.SATURN, swe.URANUS, swe.NEPTUNE, swe.PLUTO)

aspects = (0, 30, 45, 60, 72, 90, 120, 135, 144, 150, 180)

results = list()

corr = (1.0/86400)*2

# get next aspects
for i, p1 in enumerate(planets):
	for p2 in planets[i+1:]:
		if p1 == swe.SUN and p2 == swe.MERCURY:
			continue
		for asp in aspects:
			if p1 == swe.SUN and p2 == swe.VENUS and asp > 60:
				continue
			if p1 == swe.MERCURY and p2 == swe.VENUS and asp > 90:
				continue
			jd = jdstart
			while jd != None:
				trange = jdstop-(jd+corr)
				jd, pos0, pos1 = swe._next_aspect_with2(p1, asp, p2, jd+corr,
					dayspan=trange)
				if jd[0] != None:
					results.append((jd, p1, asp, p2))
				jd = jd[0]


# get next retro/direct changings
for p in planets:
	if p == swe.SUN or p == swe.MOON:
		continue
	jd = jdstart
	while jd != None:
		res = swe.calc_ut(jd+corr, p)
		trange = jdstop-(jd+corr)
		jd, pos = swe._next_retro(p, jd+corr, dayspan=trange)
		if jd[0] != None:
			if res[3] > 0:
				results.append((jd, p, -1, p))
			else:
				results.append((jd, p, -2, p))
		jd = jd[0]


# get ingres
for p in planets:
	jd = jdstart
	while jd != None:
		res = swe.calc_ut(jd+corr, p)
		sign = floor(res[0]/30)
		trange = jdstop-(jd+corr)
		jd, pos = swe._next_aspect(p, 0, swe.degnorm((sign+1)*30), jd+corr,
			dayspan=trange)
		if jd[0] != None:
			results.append((jd, p, -3-swe.degnorm((sign+1)*30), p))
		jd = jd[0]


results.sort(key=lambda x: x[0])


def aspect_name(asp):
	if asp == 0: return 'Conjunction'
	if asp == 30: return 'SemiSextile'
	if asp == 45: return 'SemiSquare'
	if asp == 60: return 'Sextile'
	if asp == 72: return 'Quintile'
	if asp == 90: return 'Square'
	if asp == 120: return 'Trine'
	if asp == 135: return 'SesquiSquare'
	if asp == 144: return 'BiQuintile'
	if asp == 150: return 'Quincunx'
	if asp == 180: return 'Opposition'
	if asp == -1: return 'Retro'
	if asp == -2: return 'Direct'
	if asp <= -3: return 'Ingres %s' % (abs(asp+3),)


for jd, p1, asp, p2 in results:
	print('%s = %s | %s | %s' % (swe._revjul(jd[0]), swe.get_planet_name(p1),
		aspect_name(asp), swe.get_planet_name(p2)))


#.

