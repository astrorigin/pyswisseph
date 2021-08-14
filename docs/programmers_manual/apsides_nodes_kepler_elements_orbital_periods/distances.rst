=========
Distances
=========

This function calculates the maximum possible distance, the minimum possible
distance, and the current true distance of planet, the EMB, or an asteroid.
The calculation can be done either heliocentrically or geocentrically. With
heliocentric calculations, it is based on the momentary Kepler ellipse of the
planet. With geocentric calculations, it is based on the Kepler ellipses of the
planet and the EMB. The geocentric calculation is rather expensive...

.. autofunction:: swisseph.orbit_max_min_true_distance

..
