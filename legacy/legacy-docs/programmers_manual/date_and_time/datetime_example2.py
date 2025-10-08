# first calculate UTC from TT (ET)
utc = swe.jdet_to_utc(jdet)
# now, UTC to local time - note negative sign before tzoffset
local = swe.utc_time_zone(*utc, offset=-tzoffset)

