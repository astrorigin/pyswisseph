#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Script to track maximum days an object is retro.

Pass the planet number as first argument to the script:
Example: « python maxretro.py <planetNumber> »

"""

import sys
import swisseph as swe

swe.set_ephe_path('/usr/local/share/swisseph')

plnt = int(sys.argv[1])

jdstart = swe.julday(-3000,1,1)
jdstop = swe.julday(3000,1,1)
flag = swe.FLG_SWIEPH + swe.FLG_SPEED + swe.FLG_NOGDEFL

step = 1 # in days
result = 0
cnt = 0
when = '?'

# make sure planet is direct
res = swe.calc_ut(jdstart, plnt, flag)
if res[3] < 0:
	while res[3] < 0:
		jdstart += step
		res = swe.calc_ut(jdstart, plnt, flag)

# start
while jdstart < jdstop:
	# find a retro motion
	while res[3] > 0:
		jdstart += step
		res = swe.calc_ut(jdstart, plnt, flag)
	# begin count
	while res[3] < 0:
		jdstart += step
		cnt += 1
		res = swe.calc_ut(jdstart, plnt, flag)
	# set result
	if cnt > result:
		result = cnt
		when = jdstart
	cnt = 0


print '%s: max. retro time=%s (%s)' % (swe.get_planet_name(plnt), result, when)

# End.
