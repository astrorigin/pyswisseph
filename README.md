# pyswisseph

This is the Python extension to the Swiss Ephemeris by Astrodienst.

The Swiss Ephemeris is the de-facto standard library for astrological calculations. It is a high-precision ephemeris, based up on the DE431 ephemerides from NASA's Jet Propulsion Laboratory (JPL), and covering the time range 13201 BC to AD 17191.

## Usage Examples

### Quickstart (PyPI)

For most standard calculations (Sun, Moon, Planets), you do not need to manually set the ephemeris path, as necessary data files are included with the PyPI distribution.

This example shows how to calculate the **Sun's ecliptic longitude** by first converting the date to a Julian day:

```python
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
    date.second
)

# 2. Calculate the position of the Sun (swe.SUN)
coords, flags = swe.calc_ut(jd_tt, swe.SUN)
longitude = coords[0]

# 3. Print the results
print(f"Julian day: {jd}")
print(f"Sun Ecliptic Longitude (DD): {longitude}")

# Output:
# Julian day: 2450722.0833377214
# Sun Ecliptic Longitude (DD): 187.44207682576493
```

### Advanced Usage

For advanced usage, including calculating asteroids or historical eclipses, you may need to download the full ephemeris files and use `swe.set_ephe_path()`.

```python
import swisseph as swe

# 1. Set path to ephemeris files
swe.set_ephe_path('/usr/share/sweph/ephe')

# 2. Find time of next lunar eclipse
jd = swe.julday(2007, 3, 3) # julian day
res = swe.lun_eclipse_when(jd)
ecltime = swe.revjul(res[1][0])
print(ecltime)
# Output: (2007, 3, 3, 23.347926892340183)

# 3. Get ecliptic position of asteroid 13681 "Monty Python"
jd = swe.julday(2008, 3, 21)
xx, rflags = swe.calc_ut(jd, swe.AST_OFFSET+13681)
print(xx[0])
# Output: 0.09843983166646618
```

## Links

- **Pyswisseph docs**: [https://astrorigin.com/pyswisseph](https://astrorigin.com/pyswisseph)
- **PyPI**: [https://pypi.org/project/pyswisseph](https://pypi.org/project/pyswisseph)
- **Astrodienst**: [https://astro.com/swisseph/swephinfo_e.htm](https://astro.com/swisseph/swephinfo_e.htm)

## Source code

Clone the GitHub repository with the command

```bash
git clone --recurse-submodules https://github.com/astorigin/pyswisseph
```

## Licensing

The Pyswisseph package adopts the GNU Affero Public License version 3. See the `LICENSE.txt` file.

The original swisseph library is distributed under a dual licensing system: GNU Affero General Public License, or Swiss Ephemeris Professional License. For more information, see file `libswe/LICENSE`.

## Test Suite

For now, the tests can be run with the standard `python3 setup.py test` command. For them to pass successfully, you need a basic set of ephemerides files installed somewhere on your system:

- `seas_18.se1`
- `sefstars.txt`
- `semo_18.se1`
- `sepl_18.se1`

All downloadable from [https://github.com/aloistr/swisseph/tree/master/ephe](https://github.com/aloistr/swisseph/tree/master/ephe).

The path to the directory containing those files must be indicated in the environment variable `SE_EPHE_PATH`.

For example, on a system with the `env` command, you can do:

```bash
env SE_EPHE_PATH="/usr/share/sweph/ephe" python3 setup.py test
```

## Credits

- **Author**: Stanislas Marquis, [stan@astrorigin.com](mailto:stan@astrorigin.com)
- **PyPI/CI**: Jonathan de Jong, [jonathan@automatia.nl](mailto:jonathan@automatia.nl)
