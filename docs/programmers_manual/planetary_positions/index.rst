===================
Planetary positions
===================

Before calling one of these functions or any other Swiss Ephemeris function,
it is strongly recommended to call the function ``set_ephe_path()``. Even if
you don’t want to set an ephemeris path and use the Moshier ephemeris, it is
nevertheless recommended to call ``set_ephe_path(None)``, because this function
makes important initializations. If you don’t do that, the Swiss Ephemeris may
work but the results may be not 100% consistent.

.. toctree::

    call_parameters
    bodies
    additional_asteroids
    planetary_moons_and_body_centers
    fictitious_planets
    obliquity_and_nutation

..
