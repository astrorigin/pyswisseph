# START SETUP
import swisseph as swe
from datetime import datetime, timezone

lat = 47.33
lng = 8.58
hsys = b"W"
date = datetime(1997, 9, 30, 14, 0, 0, tzinfo=timezone.utc)

jd_ut, jd_tt = swe.utc_to_jd(
    date.year, date.month, date.day, date.hour, date.minute, date.second
)

# print(f"Julian day: {jd_tt}")

# Output:
# Julian day: 2450722.0833377214
# END SETUP
# START ASCMC
cusps, ascmc = swe.houses(jd_tt, lat, lng, hsys)
angles = [ascmc[0], ascmc[1]]

# print(f"Ascendant: {angles[0]}")
# print(f"Midheaven: {angles[1]}")

# Output:
# Ascendant: 290.4375225094583
# Midheaven: 230.37565140999195
# END ASCMC
# START PLANETS
PLANET_IDS = {
    "Sun": swe.SUN,
    "Moon": swe.MOON,
    "Mercury": swe.MERCURY,
    "Venus": swe.VENUS,
    "Mars": swe.MARS,
    "Jupiter": swe.JUPITER,
    "Saturn": swe.SATURN,
    "Uranus": swe.URANUS,
    "Neptune": swe.NEPTUNE,
    "Pluto": swe.PLUTO,
}

planets = []
for name, id_val in PLANET_IDS.items():
    coords, flag = swe.calc_ut(jd_tt, id_val)
    longitude = coords[0]
    planets.append(longitude)

# for name, planet in zip(PLANET_IDS.keys(), planets):
#    print(f"{name}: {planet}")

# Output:
# Sun: 187.44207682576493
# Moon: 175.3108433704147
# Mercury: 177.03456720228542
# Venus: 231.25169861097027
# Mars: 241.1545702632383
# Jupiter: 312.18899266331294
# Saturn: 17.660024903370054
# Uranus: 304.81633539199663
# Neptune: 297.20035476146546
# Pluto: 243.46074212504317
# END PLANETS
# START DMS
objects = planets + angles

zodiacal = []
for point in objects:
    dms_split = swe.split_deg(point, swe.SPLIT_DEG_ZODIACAL)
    zodiacal.append(dms_split)

# print(zodiacal)

# Output:
# [(7, 26, 31, 0.47657275374280417, 6), (25, 18, 39, 0.03613349287529388, 5), (27, 2, 4, 0.44192822749755756, 5), (21, 15, 6, 0.11499949295648548, 7), (1, 9, 16, 0.45294765787414093, 8), (12, 11, 20, 0.373587926601477, 10), (17, 39, 36, 0.08965213219526191, 0), (4, 48, 58, 0.8074111878721197, 10), (27, 12, 1, 0.2771412 7566374014, 9), (3, 27, 38, 0.6716501554064536, 8), (20, 26, 15, 0.08103404984462159, 9), (20, 22, 32, 0.34507597100455456, 7)]

SIGNS = (
    "Ari",
    "Tau",
    "Gem",
    "Can",
    "Leo",
    "Vir",
    "Lib",
    "Sco",
    "Sag",
    "Cap",
    "Aqu",
    "Pis",
)
# END DMS
# START PRINT
OBJECT_NAMES = list(PLANET_IDS.keys()) + ["AC", "MC"]

print(f"--- Chart Positions (System: {hsys.decode()}) ---")

for name, dms_split in zip(OBJECT_NAMES, zodiacal):
    deg, minute, sec, f_of_s, sign_index = dms_split
    sign = SIGNS[int(sign_index)]
    position_string = f"{name:<8} {deg:2.0f} {sign} {minute:02} {sec:02.0f}"
    print(position_string)
