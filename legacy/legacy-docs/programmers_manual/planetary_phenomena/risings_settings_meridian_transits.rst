====================================
Risings, settings, meridian transits
====================================

The function ``rise_trans()`` computes the times of rising, setting and
meridian transits for all planets, asteroids, the moon, and the fixed stars.
The function ``rise_trans_true_hor()`` does the same for a local horizon that
has an altitude != 0.

The function returns a rising time of an object:

- if at t0 the object is below the horizon and a rising takes place before
  the next culmination of the object;
- if at t0 the object is above the horizon and a rising takes place between
  the next lower and upper culminations of the object.

And it returns a setting time of an object,

- if at t0 the object is above the horizon and a setting takes place before
  the next lower culmination of the object;

- if at t0 the object is below the horizon and a setting takes place between
  the next upper and lower culminations.

.. note::

    "Culmination" does not mean meridian transit, especially not with the Sun,
    Moon, and planets. The culmination of a moving body with changing
    declination does not take place exactly on the meridian but shortly before
    or after the meridian transit. In polar regions, it even happens that the
    moon "rises" shortly after the culmination, on the west side of the
    meridian. I. e., the upper limb if its disk will become visible for a
    short time. The function ``rise_trans()`` should catch these cases.

.. autofunction:: swisseph.rise_trans

.. autofunction:: swisseph.rise_trans_true_hor

The second function has one additional parameter ``horhgt`` for the height of
the local horizon at the point where the body rises or sets.

The variable ``rsmi`` can have the following values:

=================== =============================================================
Constant name       Comment
=================== =============================================================
``CALC_RISE``
``CALC_SET``
``CALC_MTRANSIT``   Upper meridian transit (southern for northern geo. latitudes)
``CALC_ITRANSIT``   Lower meridian transit (northern, below the horizon)
=================== =============================================================

And the following bits can be added (or'ed) to ``CALC_RISE`` or ``CALC_SET``:

=========================== ===================================================================
Constant name               Comment
=========================== ===================================================================
``BIT_DISC_CENTER``         For rising or setting of disc center
``BIT_DISC_BOTTOM``         For rising or setting of lower limb of disc
``BIT_GEOCTR_NO_ECL_LAT``   Use topocentric position of object and ignore its ecliptic latitude
``BIT_NO_REFRACTION``       If refraction is not to be considered
``BIT_CIVIL_TWILIGHT``      In order to calculate civil twilight
``BIT_NAUTIC_TWILIGHT``     In order to calculate nautical twilight
``BIT_ASTRO_TWILIGHT``      In order to calculate astronomical twilight
``BIT_FIXED_DISC_SIZE``     Neglect the effect of distance on disc size
``BIT_HINDU_RISING``        (``BIT_DISC_CENTER | BIT_NO_REFRACTION | BIT_GEOCTR_NO_ECL_LAT``)
=========================== ===================================================================

.. note::

    ``rsmi`` = 0 will return risings according to Hindu astrology.

The rising times depend on the atmospheric pressure and temperature.
``atpress`` expects the atmospheric pressure in millibar (hectopascal);
``attemp`` the temperature in degrees Celsius.

If ``atpress`` is given the value 0, the function estimates the pressure from
the geographical altitude given in ``geopos[2]`` and ``attemp``.
If ``geopos[2]`` is 0, ``atpress`` will be estimated for sea level.

Function return values are:

- ``0`` if a rising, setting or transit event was found.
- ``-1`` if an error occurred (usually an ephemeris problem).
  *In Python, this raises an exception.*
- ``-2`` if a rising or setting event was not found because the object is
  circumpolar.

Sunrise in astronomy and in Hindu astrology
===========================================

The astronomical sunrise is defined as the time when the upper limb of the
solar disk is seen appearing at the horizon. The astronomical sunset is
defined as the moment the upper limb of the solar disk disappears below the
horizon.

The function ``rise_trans()`` by default follows this definition of
astronomical sunrises and sunsets. Also, astronomical almanacs and newspapers
publish astronomical sunrises and sunset according to this definition.

Hindu astrology and Hindu calendars use a different definition of sunrise and
sunset. They consider the Sun as rising or setting, when the center of the
solar disk is exactly at the horizon. In addition, the Hindu method ignores
atmospheric refraction. Moreover, the geocentric rather than topocentric
position is used and the small ecliptic latitude of the Sun is ignored.

In order to calculate correct Hindu rising and setting times, the flags
``BIT_NO_REFRACTION`` and ``BIT_DISC_CENTER`` must be added (or'ed) to the
parameter ``rsmi``. From Swiss Ephemeris version 2.06 on, a flag
``BIT_HINDU_RISING`` is supported. It includes the flags ``BIT_NO_REFRACTION``,
``BIT_DISC_CENTER`` and ``BIT_GEOCTR_NO_ECL_LAT``.

In order to calculate the sunrise of a given date and geographic location, one
can proceed as in the following program.

.. literalinclude:: sunrise.py
    :language: python

..
