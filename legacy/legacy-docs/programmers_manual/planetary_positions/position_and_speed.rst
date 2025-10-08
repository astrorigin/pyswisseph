==================
Position and Speed
==================

``calc()`` returns the coordinates of position and velocity in a tuple:

======= =============================== ========================================
Index   Ecliptic position               Equatorial position (``FLG_EQUATORIAL``)
======= =============================== ========================================
0       Longitude                       Right ascension
1       Latitude                        Declination
2       Distance in AU                  Distance in AU
3       Speed in longitude (deg/day)    Speed in right ascension (deg/day)
4       Speed in latitude (deg/day)     Speed in declination (deg/day)
5       Speed in distance (AU/day)      Speed in distance (AU/day)
======= =============================== ========================================

If you need rectangular coordinates (``FLG_XYZ``), ``calc()`` returns
``(x, y, z, dx, dy, dz)`` in AU.

Once you have computed a planet, e.g., in ecliptic coordinates, its equatorial
position or its rectangular coordinates are available, too. You can get them
very cheaply (little CPU time used), calling again ``calc()`` with the same
parameters, but adding ``FLG_EQUATORIAL`` or ``FLG_XYZ`` to the flags,
``calc()`` will not compute the body again, just return the data specified from
internal storage.

..
