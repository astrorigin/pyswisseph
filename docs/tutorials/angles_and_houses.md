# Angles and Houses

## Using `swe.houses()`

Let's calculate the house cusps and angles of a given chart. We'll use [the Swiss Ephemeris' initial release](https://www.astro.com/swisseph/swephchart_e.htm) in this example and the subsequent [Tutorial](tutorial.md) with the following birth data:

- 1997 September 30
- 4:00 p.m. CEST (UTC+2) -> 14:00 UTC
- Zollikon, Switzerland -> 47.33 N, 8.58 E[^1]

For ease, we're working with UTC so we can use the Python standard library `datetime` with `swe.utc_to_jd`, but you can also use `swe.utc_time_zone`. The merits of either are discussed in [Time Zones and Julian Day Conversions](../concepts/time_and_zones.md).

As this is geocentric information that relies on coordinates, you'll need to get into the habit of using coordinates as **decimal degrees (DD)** where negative latitudes mean the **southern hemisphere** and negative longitudes fall **west of the prime meridian**.

```{code-block} python
import swisseph as swe
from datetime import datetime, timezone

# 1. Define a day and convert it to Julian day (JD)
date = datetime(1997, 9, 30, 14, 0, 0, tzinfo=timezone.utc)
jd_ut, jd_tt = swe.utc_to_jd(
    date.year,
    date.month,
    date.day,
    date.hour,
    date.minute,
    date.second + date.microsecond / 1000000.0
    )

# 2. Define coordinates
lat, lng = (47.33, 8.58)

# 3. Calculate house cusps and angles
# b'P' selects hsys (house system) Placidus
cusps, ascmc = swe.houses(jd_tt, lat, lng, b'P')

# 4. Format and Print results
# Format each of the first 12 cusps to two decimal places and join them with a comma
formatted_cusps = ", ".join([f"{c:.2f}" for c in cusps[:12]])

print(f"House cusps (Placidus): [{formatted_cusps}]")
print(f"Ascendant: {ascmc[0]:.2f}")
print(f"Midheaven: {ascmc[1]:.2f}")

# Output:
# House cusps (Placidus): [290.44, 341.06, 22.92, 50.38, 70.82, 89.30, 110.44, 161.06, 202.92, 230.38, 250.82, 269.30]
# Ascendant: 290.44
# Midheaven: 230.38
```

### Explanation

The most reliable way to access the angles (Ascendant and Midheaven) is to use the dedicated `ascmc` tuple, as the `cusps` tuple is explicitly limited to the 12 houses.

| Tuple name    | Length    | Contents                                                  |
| ------------- | --------- | --------------------------------------------------------- |
| `cusps`       | 12        | Cusps for the 1st through 12th houses (index `0` to `11`) |
| `ascmc`       | 8         | Ascendant, Midheaven, Vertex, Equatorial Ascendant, etc.  |


#### Accessing angles

- The **Ascendant (ASC)**: Always at value `ascmc[0]`.
- The **Midheaven (MC)**: Always at value `ascmc[1]`.

In **quadrant house systems** like Placidus (used in this example), Campanus, Regiomonatus, or Koch:

- `ascmc[0]` (AC) should be the same as `cusps[0]` (1st house).
- `ascmc[1]` (MC) may be *theoretically* the same as `cusps[9]` (10th house).

It's generally best practice to still use the `ascmc` tuple for the Ascendant and Midheaven, which lie between two cusps in **Whole Sign Houses** and some **equal house systems**.

## Other house functions

`pywisseph` also offers:

- `swe.houses_armc`: Using the right ascension of the MC.
- `swe.houses_armc_ex2`: House cusps with their speeds using ARMC.
- `swe.houses_ex`: Extended house cusps (UT).
- `swe.houses_ex2`: Extended cusps with their speeds (UT).

[^1]: [GeoHack - Zollikon](https://geohack.toolforge.org/geohack.php?pagename=Zollikon&params=47_20_N_8_35_E_region:CH-ZH_type:city(13311))
