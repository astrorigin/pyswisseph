# House Systems

`swe.houses` takes four arguments:

- `jd`: Julian day
- `lat`: Latitude in decimal degrees (north positive)
- `lon`: Longitude in decimal degrees (east positive)
- `hsys`: House system identifier (1-byte character, e.g. b'P')

```{code-block} python
:emphasize-lines: 10
import swisseph as swe

# Zollikon, Switzerland
lat, lng = 47.33, 8.58

# 1997 Sept 30 14:00 UTC
jd = 2450722.0833377214

# b'W' is the byte for Whole Sign Houses
cusps, ascmc = swe.houses(jd, lat, lng, b'W')
print(f"Whole Sign House Cusps: {cusps}")

# Output:
# Whole Sign House Cusps: (270.0, 300.0, 330.0, 0.0, 30.0, 60.0, 90.0, 120.0, 150.0, 180.0, 210.0, 240.0)
```

`hsys` specifies which **house division system** to use. Each system is identified by a **single byte code**:


| Code              | House system          |
| ----------------- | --------------------- |
| `'P'`             | Placidus              |
| `'K'`             | Koch                  |
| `'O'`             | Porphyry              |
| `'R'`             | Regiomontanus         |
| `'C'`             | Campanus              |
| `'A'` or `'E'`    | Equal (cusp 1 = ASC)  |
| `'W'`             | Whole sign            |


A complete alphabetical list of all 24 available house systems[^1]:

| Code              | House system                              |
| ----------------- | ----------------------------------------- |
| `'B'`             | Alcabitus                                 |
| `'Y'`             | APC                                       |
| `'X'`             | Axial rotation                            |
| `'H'`             | Azimuthal/horizontal                      |
| `'C'`             | Campanus                                  |
| `'F'`             | Carter "Poli-equatorial"                  |
| `'A'` or `'E'`    | Equal (cusp 1 = ASC)                      |
| `'D'`             | Equal MC (cusp 10 = MC)                   |
| `'N'`             | Equal (cusp 1 = 0 Aries)                  |
| `'G'`             | Gaquelin sector                           |
| `'I'`             | Sunshine (Makransky, solution Treindl)     |
| `'i'`             | Sunshine (Makransky, solution Makransky)   |
| `'K'`             | Koch                                      |
| `'U'`             | Krusinski-Pisa-Goelzer                    |
| `'M'`             | Morinus                                   |
| `'P'`             | Placidus                                  |
| `'T'`             | Polich/Page ("topocentric")               |
| `'O'`             | Porphyry                                  |
| `'L'`             | Pullen SD (sinusoidal delta)              |
| `'Q'`             | Pullen SR (sinusoidal ratio)              |
| `'R'`             | Regiomontanus                             |
| `'S'`             | Sripati                                   |
| `'V'`             | Vehlow equal (ASC at 15 H1)               |
| `'W'`             | Whole sign            |


[^1]: [House cusp calculation](https://www.astro.com/swisseph/swephprg.htm#_Toc112949022), Swiss Ephemeris Programming Interface
