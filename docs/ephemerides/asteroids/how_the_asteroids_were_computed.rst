===============================
How the asteroids were computed
===============================

To generate our asteroid ephemerides, we have modified the numerical integrator
of Steve Moshier, which was capable to rebuild the DE200 JPL ephemeris.

Orbital elements, with a few exceptions, were taken from the asteroid database
computed by E. Bowell, Lowell Observatory, Flagstaff, Arizona (astorb.dat).
After the introduction of the JPL database mpcorb.dat, we still keep working
with the Lowell data because Lowell elements are given with one more digit,
which can be relevant for long-term integrations.

For a few close-Sun-approaching asteroids like 1566 Icarus, we use the elements
of JPL's DASTCOM database. Here, the Bowell elements are not good for long term
integration because they do not account for relativity.

Our asteroid ephemerides take into account the gravitational perturbations of
all planets, including the major asteroids Ceres, Pallas, and Vesta and also
the Moon.

The mutual perturbations of Ceres, Pallas, and Vesta were included by iterative
integration. The first run was done without mutual perturbations, the second
one with the perturbing forces from the positions computed in the first run.

The precision of our integrator is very high. A test integration of the orbit
of Mars with start date 2000 has shown a difference of only 0.0007 arc second
from DE200 for the year 1600. We also compared our asteroid ephemerides with
data from JPL's on-line ephemeris system "Horizons" which provides asteroid
positions from 1600 on. Taking into account that Horizons does not consider the
mutual perturbations of the major asteroids Ceres, Pallas and Vesta, the
difference is never greater than a few 0.1 arcsec.

(However, the Swisseph asteroid ephemerides do consider those perturbations,
which makes a difference of 10 arcsec for Ceres and 80 arcsec for Pallas. This
means that our asteroid ephemerides are even better than the ones that JPL
offers on the web.)

The accuracy limits are therefore not set by the algorithms of our program but
by the inherent uncertainties in the orbital elements of the asteroids from
which our integrator has to start.

Sources of errors are:

- Only some of the minor planets are known to better than an arc second for
  recent decades. (See also information below on Ceres, Chiron, and Pholus.)

- Bowells elements do not consider relativistic effects, which leads to
  significant errors with long-term integrations of a few close-Sun-approaching
  orbits (except 1566, 2212, 3200, 5786, and 16960, for which we use JPL
  elements that do take into account relativity).

The orbits of some asteroids are extremely sensitive to perturbations by major
planets. E.g. 1862 Apollo becomes chaotic before the year 1870 CE when he
passes Venus within a distance which is only one and a half the distance from
the Moon to the Earth. In this moment, the small uncertainty of the initial
elements provided by the Bowell database grows, so to speak, "into infinity",
so that it is impossible to determine the precise orbit prior to that date.
Our integrator is able to detect such happenings and end the ephemeris
generation to prevent our users working with meaningless data.

..
