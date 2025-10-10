# Bodies

For the functions `swe.calc_ut`, `swe.calc`, and `swe.calc_pctr`, you'll need to pass an integer to identify which celestial body to calculate. You can use the named constants or the numeric values directly. These numbers are defined in [`swephexp.h`](https://github.com/aloistr/swisseph/blob/master/swephexp.h).

## Major bodies and asteroids

| Constant | Value | Body |
|----------|-------|------|
| `swe.SUN` | 0 | Sun |
| `swe.MOON` | 1 | Moon |
| `swe.MERCURY` | 2 | Mercury |
| `swe.VENUS` | 3 | Venus |
| `swe.MARS` | 4 | Mars |
| `swe.JUPITER` | 5 | Jupiter |
| `swe.SATURN` | 6 | Saturn |
| `swe.URANUS` | 7 | Uranus |
| `swe.NEPTUNE` | 8 | Neptune |
| `swe.PLUTO` | 9 | Pluto |
| `swe.MEAN_NODE` | 10 | Mean lunar node |
| `swe.TRUE_NODE` | 11 | True lunar node |
| `swe.MEAN_APOG` | 12 | Mean lunar apogee (Lilith) |
| `swe.OSCU_APOG` | 13 | Osculating lunar apogee (Lilith) |
| `swe.EARTH`   | 14 | Earth |
| `swe.CHIRON`    | 15    | Chiron    |
| `swe.PHOLUS`    | 16    | Pholus    |
| `swe.CERES`    | 17    | Ceres    |
| `swe.PALLAS`    | 18    | Pallas Athena    |
| `swe.JUNO`    | 19    | Juno    |
| `swe.VESTA`    | 20    | Vesta    |


#### Example using constants
```py
coords, flags = swe.calc_ut(jd, swe.MARS)
print("Mars: {coords[0]}")
```

#### Example using numeric values
```py
for planet_id in range(10):
    coords, flags = swe.calc_ut(jd, planet_id)
    print(f"Planet {planet_id}: {coords[0]}")
```


## Custom asteroids and minor planets

To calculate the position of an asteroid or minor planet not listed in the standard bodies, you must combine the constant `swe.AST_OFFSET` with the asteroid's catalogue number.

The catalogue number is added to the offset (`swe.AST_OFFSET = 10000`) to form the correct body ID (`ipl`) for use in functions like `swe.calc_ut()`. The names and catalogue numbers can be referenced in the Swiss Ephemeris file [`seasnam.txt`](https://github.com/aloistr/swisseph/blob/master/ephe/seasnam.txt).

### Construction

The required integer ID (`ipl`) is constructed using

```
ipl = swe.AST_OFFSET + catalogue number
```

### Example: Asteroid 433 Eros

```{code-block} python
:linenos:

import swisseph as swe
# The body ID for Eros
EROS_ID = swe.AST_OFFSET + 433  # EROS_ID is 10433

# Use the calculated ID in your position function
jd = swe.julday(2025, 1, 1)
coords, flag = swe.calc_ut(jd, EROS_ID)

print(f"Eros Longitude: {coords[0]}")
```


### Configuration

To access these minor objects, you'll have to download additional ephemeris files and set their path as described [in the installation instructions](../installation.md#configuration-using-extended-ephemeris-data).

## See also

- Swiss Ephemeris Programming Interface: [Bodies (int ipl)](https://www.astro.com/swisseph/swephprg.htm#_Toc112948960)
- All major bodies: [`swephexp.h`](https://github.com/aloistr/swisseph/blob/master/swephexp.h)
- All additional asteroids: [`seasnam.txt`](https://github.com/aloistr/swisseph/blob/master/ephe/seasnam.txt)
