=========================
Get fixed stars magnitude
=========================

The following functions calculate the magnitude of a fixed star.

.. autofunction:: swisseph.fixstar_mag

.. autofunction:: swisseph.fixstar2_mag

For the definition and use of the parameter star see function ``fixstar()``:
:doc:`fixed_stars_positions`

The new function ``fixstar2_mag()`` (since SE 2.07) is more efficient if great
numbers of fixed stars are calculated.

Strictly speaking, the magnitudes returned by this function are valid for the
year 2000 only. Variations in brightness due to the star's variability or due
to the increase or decrease of the star's distance cannot be taken into
account. With stars of constant absolute magnitude, the change in brightness
can be ignored for the historical period. E.g. the current magnitude of Sirius
is -1.46. In 3000 BCE it was -1.44.

..
