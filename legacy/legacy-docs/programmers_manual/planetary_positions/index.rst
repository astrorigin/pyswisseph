===================
Planetary positions
===================

Before calling one of these functions or any other Swiss Ephemeris function,
it is strongly recommended to call the function ``set_ephe_path()``. Even if
you don't want to set an ephemeris path and use the Moshier ephemeris, it is
nevertheless recommended to call ``set_ephe_path(None)``, because this function
makes important initializations. If you don't do that, the Swiss Ephemeris may
work but the results may be not 100% consistent.

.. toctree::
    :maxdepth: 3

    call_parameters
    bodies/index
    options_chosen_by_flag_bits/index
    position_and_speed
    error_handling_and_return_values

..
