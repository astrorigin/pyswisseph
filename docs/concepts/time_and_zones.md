# Time Zones and Julian Day Conversions

Handling time zones and Daylight Saving Time (DST) correctly is the most critical step in accurate astronomical calculation. The underling C library only accepts two types of time: **Julian day (JD)** and **universal time (UTC)**.

This section explains two methods for converting a user's local time to the necessary input format.

## Method 1: Python's `datetime` with `tzinfo` (Recommended)

This method uses Python's robust time zone system to accurately convert localized time to Universal Time (UTC) before passing it to `pyswisseph`. This approach is necessary because time zones frequently change their offsets due to political reasons and DST.

1. A user provides a local date/time and a time zone name (e.g., `'America/Los_Angeles'`).
2. Python's built-in `zoneinfo` (or external libraries like `pytz`) handles the complex historical logic, correctly determining the UTC offset and DST status for that specific moment.
3. The local time is converted to a precise, non-ambiguous UTC time.
4. This UTC time is then converted to a **Julian day (JD)** using one of the library's conversion functions (e.g., `swe.julday()` or `swe.utc_to_jd()`).

**Pros**

- **DST and history-aware**: Guarantees accuracy by accounting for DST changes and historical time zone definitions.
- **Intuitive**: Users input their known time zone name, not a raw, shifting numeric offset.

```{code-block} python
import swisseph as swe
from datetime import datetime
from zoneinfo import ZoneInfo # Standard since Python 3.9

# 1. Define the localized datetime
dt_local = datetime(1997, 9, 30, 14, 0, tzinfo=ZoneInfo('Europe/Zurich'))

# 2. Convert to UTC
dt_utc = dt_local.astimezone(ZoneInfo("UTC"))

# 3. Convert UTC to Julian Day (JD)
jd = swe.julday(dt_utc.year, dt_utc.month, dt_utc.day,
                dt_utc.hour + dt_utc.minute/60 + dt_utc.second/3600)

# Use jd for calculations...
```

## Method 2: Using `swe.utc_time_zone()`

The `swe.utc_time_zone()` function in the C library is designed to calculate a Julian Day when the exact numeric difference from UTC is already known. It takes a single numeric offset in hours (e.g., `−5.0`, `+10.5`).

**Cons**

- **No DST logic**: The function does **not** check for or adjust DST. If you pass a fixed offset (e.g., `-5.0` hours) for a place that observes DST, your calculation will be off by one hour for have the year.
- **Manual input**: Your (or the calling application) are responsible for manually calculating and passing the correct offset.

**When to use**

This function is only safe to use when the input time is guaranteed to be in a constant, non-DST-observing time zone (like GMT/UT or the Korean Peninsula) or when you are manually handling the DST logic yourself for fixed historical calculations.

```{code-block} python
import swisseph as swe

# Example: Time in Eastern Standard Time (EST, constant -5 hours offset)
# Note: If the actual date was during DST (EDT, -4 hours), this would be incorrect.
year, month, day, hour = 2025, 1, 1, 12
offset_hours = -5.0

jd = swe.utc_time_zone(year, month, day, hour, offset_hours)

# Use jd for calculations...
```
