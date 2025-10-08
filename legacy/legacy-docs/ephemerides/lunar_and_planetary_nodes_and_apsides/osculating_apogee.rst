==================================================================
The Osculating Apogee (astrological True Lilith or True Dark Moon)
==================================================================

The position of 'true Lilith' is given in the New International Ephemerides
(NIE, Editions St. Michel) and in Francis Santoni 'Ephemerides de la lune noire
vraie 1910-2010' (Editions St. Michel, 1993). Both Ephemerides coincide
precisely.

The relation of this point to the mean apogee is not exactly of the same kind
as the relation between the true node and the mean node. Like the 'true' node,
it can be considered as an osculating orbital element of the lunar motion. But
there is an important difference: The apogee contains the concept of the
ellipse, whereas the node can be defined without thinking of an ellipse. As has
been shown above, the node can be derived from orbital planes or great circles,
which is not possible with the apogee. Now ellipses are good as a description
of planetary orbits because planetary orbits are close to a two-body problem.
But they are not good for the lunar orbit which is strongly perturbed by the
gravity of the Sun (three-body problem). The lunar orbit is far from being an
ellipse!

The osculating apogee is 'true' twice a month: when it is in exact conjunction
with the Moon, the Moon is most distant from the Earth; and when it is in exact
opposition to the Moon, the Moon is closest to the Earth. The motion in between
those two points, is an oscillation with the period of a month. This
oscillation is largely an artifact caused by the reduction of the Moon's orbit
to a two-body problem. The amplitude of the oscillation of the osculating
apogee around the mean apogee is +/- 30 degrees, while the actual apogee's
deviation from the mean one never exceeds 5 degrees.

There is a small difference between the NIE's 'true Lilith' and our osculating
apogee, which results from an inaccuracy in NIE. The error reaches 20 arc
minutes. According to Santoni, the point was calculated using 'les 58 premiers
termes correctifs au perigée moyen' published by Chapront and Chapront-Touzé.
And he adds: "Nous constatons que même en utilisant ces 58 termes correctifs,
l'erreur peut atteindre 0,5d!" (p. 13) We avoid this error, computing the
orbital elements from the position and the speed vectors of the Moon. (By the
way, there is also an error of +/- 1 arc minute in NIE's true node. The reason
is probably the same.)

Precision
=========

The osculating apogee can be computed from any one of the three ephemerides.
If a precision of at least one arc second is required, one has to choose either
the JPL or the Swiss Ephemeris.

Maximum differences
===================

=================================================== ===================================
JPL-derived apogee – Swiss-Ephemeris-derived apogee ~ 0.9 arc second
JPL-derived apogee – Moshier-derived apogee         ~ 360 arc seconds  = 6 arc minutes!
=================================================== ===================================

There have been several other attempts to solve the problem of a 'true' apogee.
They are not included in the SWISSEPH package. All of them work with a
correction table.

They are listed in Santoni's 'Ephemerides de la lune noire vraie' mentioned
above. With all of them, a value is added to the mean apogee depending on the
angular distance of the Sun from the mean apogee. There is something to this
idea. The actual apogees that take place once a month differ from the mean
apogee by never more than 5 degrees and seem to move along a regular curve that
is a function of the elongation of the mean apogee.

However, this curve does not have exactly the shape of a sine, as is assumed by
all of those correction tables. And most of them have an amplitude of more than
10 degrees, which is a lot too high. The most realistic solution so far was the
one proposed by Henry Gouchon in "Dictionnaire Astrologique", Paris 1992, which
is based on an amplitude of 5 degrees.

In "Meridian" 1/95, Dieter Koch has published another table that pays regard to
the fact that the motion does not precisely have the shape of a sine.
(Unfortunately, "Meridian" confused the labels of the columns of the apogee and
the perigee.)

Small discontinuities in ephemeris of true node and apogee based on compressed file
===================================================================================

See remarks in chapter :doc:`true_node`.

..
