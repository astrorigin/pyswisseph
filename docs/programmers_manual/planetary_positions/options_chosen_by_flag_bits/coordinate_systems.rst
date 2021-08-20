=======================================
Coordinate systems, degrees and radians
=======================================

=================== ========================================================================
``FLG_EQUATORIAL``  Returns equatorial positions: right ascension and declination
``FLG_XYZ``         Returns x, y, z coordinates instead of longitude, latitude, and distance
``FLG_RADIANS``     Returns position in radians, not degrees
=================== ========================================================================

E.g. to compute right ascension and declination, write:

.. code-block:: python

    flags = swe.FLG_SWIEPH | swe.FLG_SPEED | swe.FLG_EQUATORIAL

.. note::

    Concerning equatorial coordinates: with sidereal modes ``SIDM_J2000``,
    ``SIDM_B1950``, ``SIDM_J1900``, ``SIDM_GALALIGN_MARDYKS`` or if the
    sidereal flag ``SIDBIT_ECL_T0`` is set, the function provides right
    ascension and declination relative to the mean equinox of the reference
    epoch (J2000, B1950, J1900, etc.).

    With other sidereal modes or ayanamshas right ascension and declination are
    given relative to the mean equinox of date.

..
