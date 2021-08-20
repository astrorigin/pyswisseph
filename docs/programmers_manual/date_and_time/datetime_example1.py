import swisseph as swe

year = 2021
month = 8
day = 19
hour = 15
mins = 25
secs = 0
tzoffset = 5.5 # Indian Standard Time
# if date and time is not UTC, the timezone must be substracted first
# in order to get UTC
utc = swe.utc_time_zone(year, month, day, hour, mins, secs, tzoffset)
# get julian day number in UT and ET
jdet, jdut = swe.utc_to_jd(*utc)
# calculate planets with tjdut...
# swe.calc(...)
# calculate houses
# swe.houses(...)

