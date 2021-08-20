#!/usr/bin/env python3
# swemini.py

import swisseph as swe

swe.set_ephe_path(None)

flag = swe.FLG_SPEED

while True:
    date = input('Date (d.m.y) ? (type . to exit) : ')
    # stop if a period . is entered
    if date == '.':
        break
    try:
        jday, jmon, jyear = date.split('.')
    except ValueError:
        continue
    try:
        jyear = int(jyear)
        jmon = int(jmon)
        jday = int(jday)
    except ValueError:
        continue
    # we have day, month, year and convert to julian day
    isvalid, tjd_ut, dt = swe.date_conversion(jyear, jmon, jday, 0.0)
    print("date: %02d.%02d.%02d at 0:00 Universal time" % (dt[2], dt[1], dt[0]))
    print("julian day: %d" % tjd_ut)
    print("planet\tlongitude\tlatitude\tdistance\tspeed long.")
    # loop over all planets
    for p in range(swe.SUN, swe.CHIRON+1):
        if p == swe.EARTH:
            continue
        # do the coordinate calculation for this planet p
        try:
            xx, flgret = swe.calc_ut(tjd_ut, p, flag)
        except swe.Error as err:
            # if there is a problem, an exception is raised with a message
            print("error: %s" % err)
            break
        # get the name of the planet p
        pnam = swe.get_planet_name(p)
        # print the coordinates
        print("%s\t%.7f\t%.7f\t%.7f\t%.7f" % (pnam, xx[0], xx[1], xx[2], xx[3]))

