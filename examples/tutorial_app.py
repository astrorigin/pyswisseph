import swisseph as swe
from datetime import datetime, timezone

# -*- Calculation functions -*-

def calculate_jd(date: datetime) -> float:
    _, jd_tt = swe.utc_to_jd(
        date.year, date.month, date.day, date.hour, date.minute, date.second
    )
    return jd_tt


def get_angles(jd_tt: float, lat: float, lng: float, hsys: bytes) -> list[float]:
    _, ascmc = swe.houses(jd_tt, lat, lng, hsys)
    return [ascmc[0], ascmc[1]]  # AC, MC


def get_planets(jd_tt: float) -> list[float]:
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
    for id_val in PLANET_IDS.values():
        coords, _ = swe.calc_ut(jd_tt, id_val)
        planets.append(coords[0])
    return planets


def format_positions(objects: list[float], names: list[str], hsys: bytes):
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

    print(f"\n--- CHART POSITIONS (System: {hsys.decode()}) ---")

    for name, point in zip(names, objects):
        dms_split = swe.split_deg(point, swe.SPLIT_DEG_ZODIACAL)
        deg, minute, sec, _, sign_index = dms_split
        sign = SIGNS[int(sign_index)]

        position_string = f"{name:<8} {deg:2.0f} {sign} {minute:02} {sec:02.0f}"
        print(position_string)


# -*- Entry point -*-

if __name__ == "__main__":
    # User inputs here!
    BIRTH_DATA = {
        "date": datetime(1997, 7, 19, 12, 0, 0, tzinfo=timezone.utc),
        "lat": 35.6897,
        "lng": 139.69,
        "hsys": b"W",
    }

    PLANET_NAMES = [
        "Sun",
        "Moon",
        "Mercury",
        "Venus",
        "Mars",
        "Jupiter",
        "Saturn",
        "Uranus",
        "Neptune",
        "Pluto",
    ]
    OBJECT_NAMES = PLANET_NAMES + ["AC", "MC"]

    # Run the calculation flow
    jd_tt = calculate_jd(BIRTH_DATA["date"])

    angles = get_angles(jd_tt, BIRTH_DATA["lat"], BIRTH_DATA["lng"], BIRTH_DATA["hsys"])
    planets = get_planets(jd_tt)

    all_positions = planets + angles

    # Print the result
    format_positions(all_positions, OBJECT_NAMES, BIRTH_DATA["hsys"])
