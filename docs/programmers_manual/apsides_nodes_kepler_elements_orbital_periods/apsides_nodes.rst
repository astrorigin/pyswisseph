=================
Apsides and nodes
=================

The functions ``nod_aps_ut()`` and ``nod_aps()`` compute planetary nodes and
apsides (perihelia, aphelia, second focal points of the orbital ellipses).
Both functions do exactly the same except that they expect a different time
parameter.

The definitions are:

.. autofunction:: swisseph.nod_aps_ut

.. autofunction:: swisseph.nod_aps

The parameter ``flags`` allows the same specifications as with the function
``calc_ut()``. I.e., it contains the Ephemeris flag, the heliocentric,
topocentric, speed, nutation flags etc. See chapter
:doc:`/programmers_manual/planetary_positions/options_chosen_by_flag_bits/index`

The parameter ``method`` tells the function what kind of nodes or apsides are
required:

- ``NODBIT_MEAN``: Mean nodes and apsides are calculated for the bodies
  that have them, i.e. for the Moon and the planets Mercury through Neptune,
  osculating ones for Pluto and the asteroids. This is the default method.
- ``NODBIT_OSCU``: Osculating nodes and apsides are calculated for all
  bodies.
- ``NODBIT_OSCU_BAR``: Osculating nodes and apsides are calculated for all
  bodies. With planets beyond Jupiter, the nodes and apsides are calculated
  from barycentric positions and speed. See chapter TODO.

  If this bit is combined with ``NODBIT_MEAN``, mean values are given for
  the planets Mercury - Neptune.
- ``NODBIT_FOPOINT``: The second focal point of the orbital ellipse is
  computed and returned in the array of the aphelion. This bit can be combined
  with any other bit.

..
