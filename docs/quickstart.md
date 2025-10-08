# Quickstart

Let's calculate the Sun's position right now.

```py
import swisseph as swe
from datetime import datetime, timezone

# Get current time
now = datetime.now(timezone.utc)

# Convert to Julian day
jd = swe.julday(
    now.year,
    now.month,
    now.day,
    now.hour + now.minute/60.0 + now.second/3600
    )

# Calculate Sun position (Sun is body 0)
coords, flag = swe.calc_ut(jd, swe.SUN)

# Extract longitude (first element of tuple at index 0)
longitude = coords[0]

print(f"Sun longitude: {longitude:.2f}")
# Example output: Sun longitude: 195.16
```

In the tropical zodiac, this is 15 Libra.

## What just happened?

1. **Julian day**: The Swiss Ephemeris uses Julian day numbers for astronomical time. `swe.julday()` converts from calender dates.
2. **`calc_ut()`**: "UT" means Universal Time (UTC). This function returns a tuple of `(coordinates, flags)`:
    * `coordaintes`: 6-element tuple of `(longitude, latitude, distance, speed_lon, spweed_lat, speed_dist)`
    * `flags`: Return code indicating calculation success.
3. **`swe.SUN`**: A constant for the Sun (value: `0`). See [all available bodies](api/planetary_positions.md/#bodies).
