========================================================
Different functions for calculating fixed star positions
========================================================

The function ``fixstar_ut()`` does exactly the same as ``fixstar()`` except
that it expects Universal Time rather than Terrestrial Time (Ephemeris Time) as
an input value. (same as ``calc_ut()`` and ``calc()``, cf.
:doc:`/programmers_manual/planetary_positions/call_parameters`).

In the same way, the function ``fixstar2_ut()`` does the same as ``fixstar2()``
except that it expects Universal Time as input time.

The functions ``fixstar2_ut()`` and ``fixstar2()`` were introduced with SE
2.07. They do the same as ``fixstar_ut()`` and ``fixstar()`` except that they
are a lot faster and have a slightly different behavior, explained below.

For new projects, we recommend using the new functions ``fixstar2_ut()`` and
``fixstar2()``. Performance will be a lot better if a great number of fixed
star calculations are done. If performance is a problem with your old projects,
we recommend replacing the old functions by the new ones. However, the output
should be checked carefully, because the behavior of old and new functions is
not exactly identical.

..
