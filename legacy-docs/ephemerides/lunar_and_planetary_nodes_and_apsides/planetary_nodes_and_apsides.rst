===========================
Planetray nodes and apsides
===========================

Differences between the Swiss Ephemeris and other ephemerides of the osculation
nodes and apsides are probably due to different planetary ephemerides being
used for their calculation. Small differences in the planetary ephemerides lead
to greater differences in nodes and apsides.

Definitions of the nodes
========================

.. Methods described in small font are not supported by the Swiss Ephemeris software.

The lunar nodes are defined by the intersection axis of the lunar orbital plane
with the plane of the ecliptic. At the lunar nodes, the Moon crosses the plane
of the ecliptic and its ecliptic latitude changes sign. There are similar nodes
for the planets, but their definition is more complicated. Planetary nodes can
be defined in the following ways:

- They can be understood as an axis defined by the intersection line of two
  orbital planes. E.g., the nodes of Mars are defined by the intersection line
  of the orbital plane of Mars with the plane of the ecliptic (or the orbital
  plane of the Earth).

.. note::

    However, as Michael Erlewine points out in his elaborate web page on this
    topic (http://thenewage.com/resources/articles/interface.html), planetary
    nodes could be defined for any couple of planets. E.g. there is also an
    intersection line for the two orbital planes of Mars and Saturn. Such
    non-ecliptic nodes have not been implemented in the Swiss Ephemeris.

Because such lines are, in principle, infinite, the heliocentric and the
geocentric positions of the planetary nodes will be the same. There are
astrologers that use such heliocentric planetary nodes in geocentric charts.

The ascending and the descending node will, in this case, be in precise opposition.

- There is a second definition that leads to different geocentric ephemerides.
  The planetary nodes can be understood, not as an infinite axis, but as the
  two points at which a planetary orbit intersects with the ecliptic plane.

For the lunar nodes and heliocentric planetary nodes, this definition makes no
difference from the definition 1). However, it does make a difference for
geocentric planetary nodes, where, the nodal points on the planets orbit are
transformed to the geocenter. The two points will not be in opposition anymore,
or they will roughly be so with the outer planets. The advantage of these nodes
is that when a planet is in conjunction with its node, then its ecliptic
latitude will be zero. This is not true when a planet is in geocentric
conjunction with its heliocentric node. (And neither is it always true for
inner the planets, for Mercury and Venus.)

.. note::

    There is another possibility, not implemented in the Swiss ephemeris: E.g.,
    instead of considering the points of the Mars orbit that are located in the
    ecliptic plane, one might consider the points of the Earth's orbit that are
    located in the orbital plane of Mars. If one takes these points
    geocentrically, the ascending and the descending node will always form an
    approximate square. This possibility has not been implemented in the Swiss
    Ephemeris.

- Third, the planetary nodes could be defined as the intersection points of the
  plane defined by their momentary geocentric position and motion with the
  plane of the ecliptic. Here again, the ecliptic latitude would change sign at
  the moment when the planet were in conjunction with one of its nodes. This
  possibility has not been implemented in the Swiss Ephemeris.

Possible definitions for apsides and focal points
=================================================

The lunar apsides - the lunar apogee and lunar perigee - have already been
discussed further above. Similar points exist for the planets, as well, and
they have been considered by astrologers. Also, as with the lunar apsides,
there is a similar disagreement:

One may consider either the planetary apsides, i.e. the two points on a
planetary orbit that are closest to the Sun and most distant from the Sun,
resp. The former point is called the "perihelion" and the latter one the
"aphelion". For a geocentric chart, these points could be transformed from the
heliocenter to the geocenter.

However, Bernard Fitzwalter and Raymond Henry prefer to use the second focal
points of the planetary orbits. And they call them the "black stars" or the
"black Suns of the planets". The heliocentric positions of these points are
identical to the heliocentric positions of the aphelia, but geocentric
positions are not identical, because the focal points are much closer to the
Sun than the aphelia. Most of them are even inside the Earth orbit.

The Swiss Ephemeris supports both points of view.

Special case: the Earth
=======================

The Earth is a special case. Instead of the motion of the Earth herself, the
heliocentric motion of the Earth-Moon-Barycenter (EMB) is used to determine the
osculating perihelion.

There is no node of the Earth orbit itself.

There is an axis around which the Earth's orbital plane slowly rotates due to
planetary precession. The position points of this axis are not calculated by
the Swiss Ephemeris.

Special case: the Sun
=====================

In addition to the Earth (EMB) apsides, our software computes so-to-say
"apsides" of the solar orbit around the Earth, i.e. points on the orbit of the
Sun where it is closest to and where it is farthest from the Earth. These
points form an opposition and are used by some astrologers, e.g. by the Dutch
astrologer George Bode or the Swiss astrologer Liduina Schmed. The "perigee",
located at about 13 Capricorn, is called the "Black Sun", the other one, in
Cancer, is called the "Diamond".

So, for a complete set of apsides, one might want to calculate them for the Sun
and the Earth and all other planets.

Mean and osculating positions
=============================

There are serious problems about the ephemerides of planetary nodes and
apsides. There are mean ones and osculating ones. Both are well-defined points
in astronomy, but this does not necessarily mean that these definitions make
sense for astrology. Mean points, on the one hand, are not true, i.e. if a
planet is in precise conjunction with its mean node, this does not mean it be
crossing the ecliptic plane exactly that moment. Osculating points, on the
other hand, are based on the idealization of the planetary motions as two-body
problems, where the gravity of the Sun and a single planet is considered and
all other influences neglected. There are no planetary nodes or apsides, at
least today, that really deserve the label "true".

Mean positions
==============

Mean nodes and apsides can be computed for the Moon, the Earth and the planets
Mercury – Neptune. They are taken from the planetary theory VSOP87. Mean points
cannot be calculated for Pluto and the asteroids, because there is no planetary
theory for them.

Although the Nasa has published mean elements for the planets Mercury – Pluto
based on the JPL ephemeris DE200, we do not use them (so far), because their
validity is limited to a 250 year period, because only linear rates are given,
and because they are not based on a planetary theory.

(http://ssd.jpl.nasa.gov/elem_planets.html, "mean orbit solutions from a 250
yr. least squares fit of the DE 200 planetary ephemeris to a Keplerian orbit
where each element is allowed to vary linearly with time")

The differences between the DE200 and the VSOP87 mean elements are
considerable, though:

=========== ======= =========== =========
Planet      Node    Perihelion  (comment)
=========== ======= =========== =========
Mercury     3"      4"
Venus       3"      107"
Earth       --      35"
Mars        74"     4"
Jupiter     330"    1850"
Saturn      178"    1530"
Uranus      806"    6540"
Neptune     225"    11600"      (>3 deg!)
=========== ======= =========== =========

Osculating nodes and apsides
============================

Nodes and apsides can also be derived from the osculating orbital elements of a
body, the parameters that define an ideal unperturbed elliptic (two-body) orbit
for a given time. Celestial bodies would follow such orbits if perturbations
were to cease suddenly or if there were only two bodies (the Sun and the planet)
involved in the motion and the motion were an ideal ellipse. This ideal
assumption makes it obvious that it would be misleading to call such nodes or
apsides "true". It is more appropriate to call them "osculating". Osculating
nodes and apsides are "true" only at the precise moments, when the body passes
through them, but for the times in between, they are a mere mathematical
construct, nothing to do with the natre of an orbit.

We tried to solve the problem by interpolating between actual passages of the
planets through their nodes and apsides. However, this method works only well
with Mercury. With all other planets, the supporting points are too far apart
as to allow a sensible interpolation.

There is another problem about heliocentric ellipses. E.g. Neptune's orbit has
often two perihelia and two aphelia (i. e. minima and maxima in heliocentric
distance) within one revolution. As a result, there is a wild oscillation of
the osculating or "true" perihelion (and aphelion), which is not due to a
transformation of the orbital ellipse but rather due to the deviation of the
heliocentric orbit from an elliptic shape. Neptune's orbit cannot be adequately
represented by a heliocentric ellipse.

In actuality, Neptune's orbit is not heliocentric at all. The double perihelia
and aphelia are an effect of the motion of the Sun about the solar system
barycenter. This motion is a lot faster than the motion of Neptune, and Neptune
cannot react to such fast displacements of the Sun. As a result, Neptune seems
to move around the barycenter (or a mean Sun) rather than around the real Sun.
In fact, Neptune's orbit around the barycenter is therefore closer to an
ellipse than his orbit around the Sun. The same is also true, though less
obvious, for Saturn, Uranus and Pluto, but not for Jupiter and the inner
planets.

This fundamental problem about osculating ellipses of planetary orbits does of
course not only affect the apsides but also the nodes.

As a solution, it seems reasonable to compute the osculating elements of slow
planets from their barycentric motions rather than from their heliocentric
motions. This procedure makes sense especially for Neptune, but also for all
planets beyond Jupiter. It comes closer to the mean apsides and nodes for
planets that have such points defined. For Pluto and all trans-Saturnian
asteroids, this solution may be used as a substitute for "mean" nodes and
apsides. Note, however, that there are considerable differences between
barycentric osculating and mean nodes and apsides for Saturn, Uranus, and
Neptune. (A few degrees! But heliocentric ones are worse.)

Anyway, neither the heliocentric nor the barycentric ellipse is a perfect
representation of the nature of a planetary orbit. So, astrologers should not
expect anything very reliable here either!

The best choice of method will probably be:

- For Mercury – Neptune: mean nodes and apsides.
- For asteroids that belong to the inner asteroid belt: osculating nodes/apsides
  from a heliocentric ellipse.
- For Pluto and transjovian asteroids: osculating nodes/apsides from a
  barycentric ellipse.

The modes of the Swiss Ephemeris function swe_nod_aps()
=======================================================

The function swe_nod_aps() can be run in the following modes:

1. Mean positions are given for nodes and apsides of Sun, Moon, Earth, and the
   planets up to Neptune. Osculating positions are given with Pluto and all
   asteroids. This is the default mode.
2. Osculating positions are returned for nodes and apsides of all planets.
3. Same as 2), but for planets and asteroids beyond Jupiter, a barycentric
   ellipse is used.
4. Same as 1), but for Pluto and asteroids beyond Jupiter, a barycentric ellipse
   is used.

For the reasons given above, method 4) seems to make best sense.

In all of these modes, the second focal point of the ellipse can be computed
instead of the aphelion.

..
