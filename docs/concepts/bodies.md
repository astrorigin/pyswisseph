# Planetary Positions

## Bodies

Pass an integer to identify which celestial body to calculate. You can use the named constants or the numeric values directly.


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


### Example using constants
```py
coords, flags = swe.calc_ut(jd, swe.MARS)
```

### Example using numeric values
```py
for planet_id in range(10):
    coords, flags = swe.calc_ut(jd, planet_id)
    print(f"Planet {planet_id}: {coords[0]:.2f}")
```
