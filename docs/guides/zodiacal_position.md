# Zodiacal Position

When we [calculated the current position of the Sun](../quickstart.md), `pyswisseph` output the body's **ecliptic longitude** from Earth's point of view—in our example, `196.1388645301424` **decimal degrees** (DD). This absolute longitude is measured counter-clockwise along the ecliptic plane, starting from the vernal equinox.

The 12 signs of the zodiac are `30`-degree segments of this `360`-degree circle. Each segment is an "alias" for a specific longitude range. The **tropical zodiac** places **`0` Aries** at the vernal equinox (`0.0` DD), while the **sideral zodiac** uses an offset (ayanamsa) that may reference fixed stars.

Tropically, the starting absolute longitude of each sign is:


| Tropical sign | Starting ecliptic longitude (DD)  |
| ------------- | --------------------------------- |
| Aries         | `0.0`                             |
| Taurus        | `30.0`                            |
| Gemini        | `60.0`                            |
| Cancer        | `90.0`                            |
| Leo           | `120.0`                           |
| Virgo         | `150.0`                           |
| Libra         | `180.0`                           |
| Scorpio       | `210.0`                           |
| Sagittarius   | `240.0`                           |
| Capricorn     | `270.0`                           |
| Aquarius      | `300.0`                           |
| Pisces        | `330.0`                           |

Thus, `196.1388645301424` DD is a complete position if you only need absolute coordinates. However, to translate this to the more common **degrees-minutes-seconds** (DMS) format **relative to the sign** (where the degrees reset to `0` at the cusp of each sign), `pyswisseph` provides the function `swe.split_deg` that takes DD positions and **flag constant**. The flats tell the function *how* to split the degree value.

We will use `swe.SPLIT_DEG_ZODIACAL`, which tells the function to reset the degrees at the start of each sign and append the sign's index to the result.

## Ecliptic longitude DD -> sign DMS

Let's take our Sun position and translate it to zodiacal position and DMS.

```{code-block} python
:linenos:
:emphasize-lines: 26

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

# 5. Split longitude into degrees and signs
dms = swe.split_deg(longitude, swe.SPLIT_DEG_ZODIACAL)

# 6. Index the signs
sign_order = (
            "Ari", "Tau", "Gem", "Can",
            "Leo", "Vir", "Lib", "Sco",
            "Sag", "Cap", "Aqu", "Pis"
            )

# 7. Get sign name from index
sign_name = sign_order[dms[4]]

# 8. Format output
print(f"{dms[0]} {sign_name} {dms[1]} {dms[2]}")

# Example output:
# 16 Lib 38 15
```

## Understanding the `swe.split_deg` output

The `swe.split_deg` function, when called with the `swe.SPLIT_DEG_ZODIACAL` flag, returns a **5-element tuple** containing the `0`-based zodiacal position:

| Index | Name              | Description                                       |
| ----- | ----------------- | ------------------------------------------------- |
| **0** | Degrees           | The `0-29` degree within the sign.                |
| **1** | Minutes           | The minutes `0-59`.                               |
| **2** | Seconds           | The seconds `0-59`.                               |
| **3** | `f of s`          | The fraction of a second (unused in this example) |
| **4** | **Sign Index**    | The `0-11` index of the zodiac sign.              |

The sign index at `dms[4]` corresponds to the `0`-based array/tuple index:

- `0`: Aries
- `1`: Taurus
- `2`: Gemini
- `3`: Cancer
- `4`: Leo
- `5`: Virgo
- `6`: Libra
- `7`: Scorpio
- `8`: Sagittarius
- `9`: Capricorn
- `10`: Aquarius
- `11`: Pisces

By using this index to access the `sign_order` tuple, we successfully translated the raw output into the human-readable string: **`16 Lib 38 15`**.
