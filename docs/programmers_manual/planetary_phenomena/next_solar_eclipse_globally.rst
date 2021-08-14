====================================
Find the next solar eclipse globally
====================================

This function requires the time parameter ``tjdut`` in Universal Time and also
yields the return values ``tret`` in UT. For conversions between ET and UT, use
the function ``deltat()``. TODO

.. note::

    An implementation of this function with parameters in Ephemeris Time would
    have been possible. The question when the next solar eclipse will happen
    anywhere on Earth is independent of the rotational position of the Earth
    and therefore independent of Delta T. However, the function is often used
    in combination with other eclipse functions (see :doc:`example`), for which
    input and output in ET makes no sense, because they concern local
    circumstances of an eclipse and therefore are dependent on the rotational
    position of the Earth. For this reason, UT has been chosen for the time
    parameters of all eclipse functions.

.. autofunction:: swisseph.sol_eclipse_when_glob

The parameter ``ecltype`` specifies the eclipse type wanted. It can be a
combination of the following bits:

 - ``swe.ECL_CENTRAL``
 - ``swe.ECL_NONCENTRAL``
 - ``swe.ECL_TOTAL``
 - ``swe.ECL_ANNULAR``
 - ``swe.ECL_PARTIAL``
 - ``swe.ECL_ANNULAR_TOTAL`` (equals ``swe.ECL_HYBRID``)
 - ``swe.ECL_ALLTYPES_SOLAR`` (or ``0`` for any type)

Recommended values for ``ecltype``:

 - Search for any eclipse, no matter which: ``ecltype = 0``
 - Search a total eclipse (nb: non-central total eclipses are very rare):
   ``ecltype = swe.ECL_TOTAL | swe.ECL_CENTRAL | swe.ECL_NONCENTRAL``
 - Search an annular eclipse: ``ecltype = swe.ECL_ANNULAR | swe.ECL_CENTRAL |
   swe.ECL_NONCENTRAL``
 - Search an annular-total (hybrid) eclipse: ``ecltype = swe.ECL_ANNULAR_TOTAL
   | swe.ECL_CENTRAL | swe.ECL_NONCENTRAL``
 - Search a partial eclipse: ``ecltype = swe.ECL_PARTIAL``

..
