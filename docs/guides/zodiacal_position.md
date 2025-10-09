# Zodiacal Position

When we [calculated the current position of the Sun](../quickstart.md), `pyswisseph` output the body's **ecliptic longitude** from Earth's point of view—in our example, `196.1388645301424` **decimal degrees** (DD). This absolute longitude is measured counter-clockwise along the ecliptic plane, starting from the vernal equinox.

The 12 signs of the zodiac are `30`-degree segments of this `360`-degree circle. Each segment is an "alias" for a specific longitude range. The **tropical zodiac** places **`0` Aries** at the vernal equinox (`0.0 DD), while the **sideral zodiac** uses an offset (ayanamsa) that may reference fixed stars.

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

Let's take our Sun position and translate it to zodiacal position and DMS.

```py
import swisseph as swe
from datetime import datetime, timezone

now = datetime.now(timezone.utc)

jd = swe.julday(
    now.year,
    now.month,
    now.day,
    now.hour + now.minute/60 + now.second/3600
    )

coords, flag = swe.calc_ut(jd, swe.SUN)

longitude = coords[0]

# split longitude into degrees and signs
dms = swe.split_deg(longitude, swe.SPLIT_DEG_ZODIACAL)

# index the signs
sign_order = (
            "Ari", "Tau", "Gem", "Can",
            "Leo", "Vir", "Lib", "Sco",
            "Sag", "Cap", "Aqu", "Pis"
            )

sign_name = sign_order[dms[4]]

# format output
print(f"{dms[0]} {sign_name} {dms[1]} {dms[2]}")
```

## Understanding the `swe.split_deg` output

The `swe.split_deg` function, when called with the `swe.SPLIT_DEG_ZODIACAL` flag, returns a **5-element tuple** containing the `0`-based zodiacal position:

| Index | Name              | Description                                       | Example (for 16 Lib 8 19) |
| ----- | ----------------- | ------------------------------------------------- | ------------------------- |
| **0** | Degrees           | The `0-29` degree within the sign.                | `16`                      |
| **1** | Minutes           | The minutes `0-59`.                               | `8`                       |
| **2** | Seconds           | The seconds `0-59`.                               | `19`                      |
| **3** | `f of s`          | The fraction of a second (unused in this example) | `0.912388...`             |
| **4** | **Sign Index**    | The `0-11` index of the zodiac sign.              | `6`                       |

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

By using this index to access the `sign_order` tuple, we successfully translated the raw output into the human-readable string: **`16 Lib 8 19`**.
