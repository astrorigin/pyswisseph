=====================================================
Functions to find crossings of planets over positions
=====================================================

These functions find the next crossing of the Sun over a given ecliptic
position:

.. autofunction:: swisseph.solcross

.. autofunction:: swisseph.solcross_ut

These functions find the next crossing of the Moon over a given ecliptic
position:

.. autofunction:: swisseph.mooncross

.. autofunction:: swisseph.mooncross_ut

.. note::

    These flag bits in ``flags`` can be useful:

    - ``swe.FLG_TRUEPOS``
    - ``swe.FLG_NONUT``
    - ``swe.FLG_EQUATORIAL`` (``x2cross`` is a rectascension value, a point on
      the equator, and not on the ecliptic)

    The precision is 1 milliarcsecond, i.e. at the returned time the Sun
    (or Moon) is closer than 0.001 arcsec to ``x2cross``.

These functions find the next crossing of the Moon over its true node, i.e.
crossing through the ecliptic:

.. autofunction:: swisseph.mooncross_node

.. autofunction:: swisseph.mooncross_node_ut

There are currently no functions for geocentric crossings of other planets.
Their movement is more complex because they can become stationary and
retrograde and make multiple crossings in a short period of time.

There are however functions for heliocentric crossings over a position
``x2cross``:

.. autofunction:: swisseph.helio_cross

.. autofunction:: swisseph.helio_cross_ut

..
