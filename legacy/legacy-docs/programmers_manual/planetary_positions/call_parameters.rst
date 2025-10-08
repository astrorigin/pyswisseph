===================
The call parameters
===================

``calc_ut()`` was introduced with Swisseph version 1.60 and makes planetary
calculations a bit simpler. For the steps required, see the chapter
:doc:`/programmers_manual/steps_to_get_a_planets_position`.

``calc_ut()`` and ``calc()`` work exactly the same way except that ``calc()``
requires Ephemeris Time (more accurate: Terrestrial Time (TT)) as a parameter
whereas ``calc_ut()`` expects Universal Time (UT). For common astrological
calculations, you will only need ``calc_ut()`` and will not have to think any
more about the conversion between Universal Time and Ephemeris Time.

``calc_ut()`` and ``calc()`` compute positions of planets, asteroids, lunar
nodes and apogees. They are defined as follows:

.. autofunction:: swisseph.calc_ut

.. autofunction:: swisseph.calc

``calc_pctr()`` calculates planetocentric positions of planets, i. e. positions
as observed from some different planet, e.g. Jupiter-centric ephemerides. The
function can actually calculate any object as observed from any other object,
e.g. also the position of some asteroid as observed from another asteroid or
from a planetary moon. The function declaration is as follows:

.. autofunction:: swisseph.calc_pctr

A detailed description of these variables will be given in the following
sections.

..
