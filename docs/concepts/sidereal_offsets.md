# Sidereal Zodiac and Ayanamsa Offsets

The calculation of celestial positions can be based on one of two primary zodiac systems: the tropical zodiac or the sidereal zodiac. While the raw ecliptic longitude remains the same, the choice of zodiac determines the starting point (`0 Aries`) for measuring the 12 signs.

## The two zodiacs

### Tropical zodiac (default)

The tropical zodiac is an **equinoctial, geocentric system** where `0 Aries` is fixed to the point of the Vernal Equinox (the position of the Sun at the start of Spring in the Northern Hemisphere).

It is directly tied to the Earth's orbital relationship with the Sun and the seasons.

The `0 Aries` point is a dynamic coordinate and moves relative to the fixed stars due to axial precession (the slow wobble of the Earth's axis).

### Sidereal zodiac

The sidereal zodiac is a **fixed-star system** used widely in Indian astrology and by a minority of Western astrologers.

It aligns `0 Aries` with a fixed point in the celestial sphere that references the background zodiacal constellations.

Because the tropical starting point (the Vernal Equinox) *precedes* the sidereal starting point over time, the two systems are constantly shifting relative to each other.

## Ayanamsa (sidereal offset)

The angular difference between the tropical `0 Aries` and the sidereal `0 Aries` is called the **ayanamsa**. The ayanamsa value must be subtracted from the tropical longitude to obtain the sidereal longitude.

Since the starting point for the sidereal zodiac is based on different astronomical conventions (e.g., fixed stars like Spica or specific theories), there is no single universally agreed-upon ayanamsa.

The Swiss Ephemeris provides functions to handle this offset automatically.

- `swe.set_sid_mode(jd_tt, ayanamsa_flag)`: Sets the preferred sidereal mode for the session. This is an optional low-level function if you need a non-standard offsets.
- `swe.get_ayanamsa(jd_tt, ayanamsa_flag)`: Calculates the precise offset value (in decimal degrees) for a specific date (Julian Day) and sidereal mode.

## Calculating sidereal positions

Obtaining a sidereal position is a two-step process:

1. **Set the global mode**: Tell the library which offset value to use.
2. **Calculate with flag**: Call the position function (`swe.calc_ut`, `swe.houses`, etc.) and include the `swe.FLG_SIDEREAL` flag to trigger the ayanamsa subtraction.

```{code-block} python
:emphasize-lines: 19,22
import swisseph as swe

SIGNS = ("Ari", "Tau", "Gem", "Can", "Leo", "Vir", "Lib", "Sco", "Sag", "Cap", "Aqu", "Pis")

# This is 1997 Sept 30 14:00 UTC
jd = 2450722.0833377214

# For comparison, we'll calculate the tropical longitude and DMS first
coords, flags = swe.calc_ut(jd, swe.SUN)
longitude = coords[0]
tropical_dms = swe.split_deg(longitude, swe.SPLIT_DEG_ZODIACAL)
tropical_string = f"{tropical_dms[0]} {SIGNS[tropical_dms[4]]} {tropical_dms[1]} {tropical_dms[2]}"
print(f"Tropical sun: {tropical_string}")

# Output:
# Tropical sun: 7 Lib 26 31

# Set the sidereal offset
swe.set_sid_mode(swe.SIDM_FAGAN_BRADLEY)

# Repeat the above for sidereal
coords, flags = swe.calc_ut(jd, swe.SUN, swe.FLG_SIDEREAL)   # <- this pulls what we set in swe.set_sid_mode
longitude = coords[0]
sidereal_dms = swe.split_deg(longitude, swe.SPLIT_DEG_ZODIACAL)
sidereal_string = f"{sidereal_dms[0]} {SIGNS[sidereal_dms[4]]} {sidereal_dms[1]} {sidereal_dms[2]}"
print(f"Sidereal sun: {sidereal_string}")

# Output:
# Sidereal sun: 12 Vir 44 3
```

## `swe.SIDM` ayanamsa constants

The Swiss Ephemeris supports dozens of sidereal offsets which are defined by constants beginning with `swe.SID_` or `swe.SIDM_`. These are passed to `swe.set_sid_mode`.

**Ayanamsa constants[^1]**

| #  | Ayanamsa Name                           | Constant                          |
|----|------------------------------------------|-----------------------------------|
| 0  | Fagan-Bradley                            | swe.SIDM_FAGAN_BRADLEY            |
| 1  | Lahiri                                   | swe.SIDM_LAHIRI                   |
| 2  | Deluce                                   | swe.SIDM_DELUCE                   |
| 3  | Raman                                    | swe.SIDM_RAMAN                    |
| 4  | Ushashashi                               | swe.SIDM_USHASHASHI               |
| 5  | Krishnamurti                             | swe.SIDM_KRISHNAMURTI             |
| 6  | Djwhal Khul                              | swe.SIDM_DJWHAL_KHUL              |
| 7  | Yukteshwar                               | swe.SIDM_YUKTESHWAR               |
| 8  | J.N. Bhasin                              | swe.SIDM_JN_BHASIN                |
| 9  | Babylonian/Kugler 1                      | swe.SIDM_BABYL_KUGLER1            |
| 10 | Babylonian/Kugler 2                      | swe.SIDM_BABYL_KUGLER2            |
| 11 | Babylolnian/Kugler 3                     | swe.SIDM_BABYL_KUGLER3            |
| 12 | Babylonian/Huber                         | swe.SIDM_BABYL_HUBER              |
| 13 | Babylonian/Eta Piscium                   | swe.SIDM_BABYL_ETPSC              |
| 14 | Babylonian/Aldebaran = 15 Tau            | swe.SIDM_ALDEBARAN_15TAU          |
| 15 | Hipparchos                               | swe.SIDM_HIPPARCHOS               |
| 16 | Sassanian                                | swe.SIDM_SASSANIAN                |
| 17 | Galact. Center = 0 Sag                   | swe.SIDM_GALCENT_0SAG             |
| 18 | J2000                                   | swe.SIDM_J2000                    |
| 19 | J1900                                   | swe.SIDM_J1900                    |
| 20 | B1950                                   | swe.SIDM_B1950                    |
| 21 | Suryasiddhanta                          | swe.SIDM_SURYASIDDHANTA           |
| 22 | Suryasiddhanta, mean Sun                | swe.SIDM_SURYASIDDHANTA_MSUN      |
| 23 | Aryabhata                               | swe.SIDM_ARYABHATA                |
| 24 | Aryabhata, mean Sun                     | swe.SIDM_ARYABHATA_MSUN           |
| 25 | SS Revati                               | swe.SIDM_SS_REVATI                |
| 26 | SS Citra                                | swe.SIDM_SS_CITRA                 |
| 27 | True Citra                              | swe.SIDM_TRUE_CITRA               |
| 28 | True Revati                             | swe.SIDM_TRUE_REVATI              |
| 29 | True Pusya (PVRN Rao)                   | swe.SIDM_TRUE_PUSHYA              |
| 30 | Galactic Center (Gil Brand)             | swe.SIDM_GALCENT_RGILBRAND        |
| 31 | Galactic Equator (IAU1958)              | swe.SIDM_GALEQU_IAU1958           |
| 32 | Galactic Equator                        | swe.SIDM_GALEQU_TRUE              |
| 33 | Galactic Equator mid-Mula               | swe.SIDM_GALEQU_MULA              |
| 34 | Skydram (Mardysk)                       | swe.SIDM_GALALIGN_MARDYKS         |
| 35 | True Mula (Chanda Hari)                 | swe.SIDM_TRUE_MULA                |
| 36 | Dhruva/Gal. Center/Mula (Wilhelm)       | swe.SIDM_GALCENT_MULA_WILHELM     |
| 37 | Aryabhata 522                           | swe.SIDM_ARYABHATA_522            |
| 38 | Babylonian/Britton                      | swe.SIDM_BABYL_BRITTON            |
| 39 | 'Vedic'/Sheoran                         | swe.SIDM_TRUE_SHEORAN             |
| 40 | Cochrane (Gal. Center = 0 Cap)          | swe.SIDM_GALCENT_COCHRANE         |
| 41 | Galactic Equator (Forenza)              | swe.SIDM_GALEQU_FIORENZA          |
| 42 | Vettius Valens                          | swe.SIDM_VALENS_MOON              |
| 43 | Lahiri 1940                             | swe.SIDM_LAHIRI_1940              |
| 44 | Lahiri VP285                            | swe.SIDM_LAHIRI_VP285             |
| 45 | Krishnamurti-Senthilathiban             | swe.SIDM_KRISHNAMURTI_VP291       |
| 46 | Lahiri ICRC                             | swe.SIDM_LAHIRI_ICRC              |

[^1]: [`swe_set_sid_mode()`](https://www.astro.com/swisseph/swephprg.htm#_Toc112949017), Swiss Ephemeris Programming Interface
