=========================
Delta T related functions
=========================

The Julian day number, you compute from a birth date, will be Universal Time
(UT, former GMT) and can be used to compute the star time and the houses.
However, for the planets and the other factors, you have to convert UT to
Ephemeris time (ET).

.. autofunction:: swisseph.deltat_ex

.. autofunction:: swisseph.deltat

.. autofunction:: swisseph.get_tid_acc

.. autofunction:: swisseph.set_tid_acc

.. autofunction:: swisseph.set_delta_t_userdef

Future updates of Delta T
=========================

Delta T values for future years can only be estimated. Strictly speaking, the
Swiss Ephemeris has to be updated every year after the new Delta T value for
the past year has been published by the IERS. We will do our best and hope to
update the Swiss Ephemeris every year. However, if the user does not want to
wait for our update or does not download a new version of the Swiss Ephemeris
he can add new Delta T values in the file ``swe_deltat.txt``, which has to be
located in the Swiss Ephemeris ephemeris path.

.. literalinclude:: swe_deltat.txt

..
