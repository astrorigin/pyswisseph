=============
The True Node
=============

The 'true' lunar node is usually considered the osculating node element of the
momentary lunar orbit. I.e., the axis of the lunar nodes is the intersection
line of the momentary orbital plane of the Moon and the plane of the ecliptic.
Or in other words, the nodes are the intersections of the two great circles
representing the momentary apparent orbit of the Moon and the ecliptic.

The nodes are considered important because they are connected with eclipses.
They are the meeting points of the Sun and the Moon. From this point of view, a
more correct definition might be: The axis of the lunar nodes is the
intersection line of the momentary orbital plane of the Moon and the momentary
orbital plane of the Sun.

This makes a difference, although a small one. Because of the monthly motion of
the Earth around the Earth-Moon barycenter, the Sun is not exactly on the
ecliptic but has a latitude, which, however, is always below an arc second.
Therefore the momentary plane of the Sun's motion is not identical with the
ecliptic. For the true node, this would result in a difference in longitude of
several arc seconds. However, Swiss Ephemeris computes the traditional version.

The advantage of the 'true' nodes against the mean ones is that when the Moon
is in exact conjunction with them, it has indeed a zero latitude. This is not
so with the mean nodes.

In the strict sense of the word, even the "true" nodes are true only twice a
month, viz. at the times when the Moon crosses the ecliptic. Positions given
for the times in between those two points are based on the idea that celestial
orbits can be approximated by elliptical elements or great circles. The monthly
oscillation of the node is explained by the strong perturbation of the lunar
orbit by the Sun. A different approach for the "true" node that would make
sense, would be to interpolate between the true node passages. The monthly
oscillation of the node would be suppressed, and the maximum deviation from the
conventional "true" node would be about 20 arc minutes.

Precision of the true node
==========================

The true node can be computed from all of our three ephemerides. If you want a
precision of the order of at least one arc second, you have to choose either
the JPL or the Swiss Ephemeris.

Maximum differences
===================

=============================================== ================
JPL-derived node – Swiss-Ephemeris-derived node ~ 0.1 arc second
JPL-derived node – Moshier-derived node         ~ 70 arc seconds
=============================================== ================

(PLACALC was not better either. Its error was often > 1 arc minute.)

Distance of the true lunar node: The distance of the true node is calculated on
the basis of the osculating ellipse of date.

Small discontinuities in ephemeris of true node and apogee based on compressed file
===================================================================================

If our compressed lunar ephemeris files semo*.se1 are used, then small
discontinuities occur every 27.55 days at the segment boundaries of the
compressed lunar orbit. The errors are small, but can be inconvenient if a
smooth function is required for the osculating node and apogee. This problem
does not occur if an original JPL ephemeris or the Moshier ephemeris is used.

..
