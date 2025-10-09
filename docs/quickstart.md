# Quickstart

Let's calculate the Sun's position right now.

```python
import swisseph as swe
from datetime import datetime, timezone

# 1. Get current time in Coordinated Universal Time (UTC)
now = datetime.now(timezone.utc)

# 2. Convert from UTC to Julian Day (JD) in Terrestrial Time (TT).
# 'jd_tt' is the second element (index 1) of the returned tuple.
jd_ut, jd_tt = swe.utc_to_jd(
    now.year,
    now.month,
    now.day,
    now.hour,
    now.minute,
    now.second + now.microsecond / 1000000.0
)

# 3. Calculate Sun position (swe.SUN is the constant for the Sun)
# We use `jd_tt` for accurate planetary positions.
coords, flags = swe.calc_ut(jd_tt, swe.SUN)

# 4. Extract longitude (first element of the 6-element coordinates tuple)
longitude = coords[0]
print(f"Sun longitude: {longitude:.2f}°")

# Example output: Sun longitude: 196.61872533619996
# In the tropical zodiac, this is `~16 Libra`.
```


## What just happened?

1. **Time scale accuracy**: The Swiss Ephemeris requires time to measure in **terrestrial time** (TT) for accurate planetary calcuations. We used `swe.utc_to_jd()` to correctly convert the current clock time (UTC) into Julian day TT, accounting for the delta-T correction.
2. **Julian day**: The Swiss Ephemeris uses Julian day numbers for astronomical time. `swe.julday()` converts from calender dates.
3. **`calc_ut()`**: "UT" means Universal Time (UTC). This function returns a tuple of `(coordinates, flags)`:
    * `coordinates`: 6-element tuple of `(longitude, latitude, distance, speed_lon, spweed_lat, speed_dist)`
    * `flags`: Return code indicating calculation success.
4. **`swe.SUN`**: A constant for the Sun (value: `0`). See [all available bodies](api/planetary_positions.md/#bodies).
