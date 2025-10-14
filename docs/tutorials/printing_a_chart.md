# Tutorial: Printing a Text Chart

This tutorial combines the concepts from [Zodiacal Position](zodiacal_position.md) (`swe.calc_ut`, `swe.split_deg`) and [Angles and Houses](angles_and_houses.md) (`swe.houses`). You can feel free to skip all the commented-out `print()` statements; they're mostly here for verification, especially if you're using the Python interpreter in interactive mode.

## Define constants and calculate Julian day

We're going to calculate the zodiacal positions of the 10 planets, ascendant and midheaven of [the initial release of the Swiss Ephemeris C library](https://www.astro.com/swisseph/swephchart_e.htm) underlying `pyswisseph`, which has the following birth information:

- 1997 September 30
- 4:00 p.m. CEST (UTC+2) -> 14:00 UTC
- Zollikon, Switzerland -> 47.33 N, 8.58 E

```{literalinclude} ../../examples/tutorial.py
:language: python
:start-after: START SETUP
:end-before: END SETUP
:emphasize-lines: 6,9-11
```

- `b'W'`: This is the byte character for **whole sign houses**, but anything works here since cusps are irrelevant to this tutorial.
- `swe.utc_to_jd()`: Explained in [Quickstart](../quickstart.md) that `jd_tt` is more accurate than `jd_ut` given by `swe.julday`.


## Calculate ascendant and midheaven longitudes

```{literalinclude} ../../examples/tutorial.py
:language: python
:start-after: START ASCMC
:end-before: END ASCMC
:emphasize-lines: 1
```

- `swe_houses()`: We only need the tuple at index `1`, `ascmc`, and only its first two elements, so we unpack them into a new list called `angles` for later concatenation.

## Calculate planetary longitudes

```{literalinclude} ../../examples/tutorial.py
:language: python
:start-after: START PLANETS
:end-before: END PLANETS
:emphasize-lines: 1-12,16,17
```

- `PLANET_IDS`: This dictionary explicitly uses constants, but you can easily loop over a range as described in [Bodies](../concepts/bodies.md).
- `swe.calc_ut()`: `coords[0]` gives ecliptic longitude.

## Convert longitudes to DMS

```{literalinclude} ../../examples/tutorial.py
:language: python
:start-after: START DMS
:end-before: END DMS
:emphasize-lines: 5
```

- `swe.split_deg`: Described in [Zodiacal Position](zodiacal_position.md). This tuple is `(degrees, minutes, seconds, fraction_of_seconds, sign index)` where `sign_index` is an integer from `0` to `11`.
- `SIGNS`: This tuple makes `sign_index` legible in printing.

## Format and print output

```{literalinclude} ../../examples/tutorial.py
:language: python
:start-after: START PRINT
:emphasize-lines: 1,6-8
```

- `OBJECT_NAMES`: Concatenates the dictionary keys from `PLANET_IDS` with our `angles` list.
- `dms_split`: This is where we get `sign_index` at index 4.

### Expected output

If you ran the complete script (`tutorial.py`), the final output should look like this:

```
--- Chart Positions (System: W) ---
Sun       7 Lib 26 31
Moon     25 Vir 18 39
Mercury  27 Vir 02 04
Venus    21 Sco 15 06
Mars      1 Sag 09 16
Jupiter  12 Aqu 11 20
Saturn   17 Ari 39 36
Uranus    4 Aqu 48 58
Neptune  27 Cap 12 01
Pluto     3 Sag 27 38
AC       20 Cap 26 15
MC       20 Sco 22 32
```

### Tutorial app

You can input your own birth information in the `if __name__ = "__main__"` block of `tutorial_app.py`:

```{literalinclude} ../../examples/tutorial_app.py
:language: python
:lines: 67-74
```
