============================
Topocentric planet positions
============================

.. autofunction:: swisseph.set_topo

This function must be called before topocentric planet positions for a certain
birth place can be computed. It tells Swiss Ephemeris, what geographic position
is to be used. Geographic longitude and latitude must be in degrees, the
altitude above sea must be in meters. Neglecting the altitude can result in an
error of about 2 arc seconds with the Moon and at an altitude 3000 m. After
calling ``set_topo()``, add ``FLG_TOPOCTR`` to ``flags`` and call ``calc()`` as
with an ordinary computation. E.g.:

.. code-block:: python

    swe.set_topo(lon, lat, alt)
    flags |= swe.FLG_TOPOCTR
    xx, retflags = swe.calc(tjd, pl, flags)

The parameters set by ``set_topo()`` survive ``close()``.

..
