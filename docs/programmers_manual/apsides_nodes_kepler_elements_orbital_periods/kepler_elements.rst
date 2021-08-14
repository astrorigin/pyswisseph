================================
Kepler elements and orbital data
================================

This function calculates osculating elements (Kepler elements) and orbital
periods for a planet, the Earth-Moon barycenter, or an asteroid. The elements
are calculated relative to the mean ecliptic J2000.

The elements define the orbital ellipse under the premise that it is a two-body
system and there are no perturbations from other celestial bodies. The elements
are particularly bad for the Moon, which is strongly perturbed by the Sun. It
is not recommended to calculate ephemerides using Kepler elements.

.. warning::

    This function should not be used for ephemerides of the perihelion or
    aphelion of a planet. Note that when the position of a perihelion is
    calculated using ``get_orbital_elements()``, this position is not measured
    on the ecliptic, but on the orbit of the planet itself, thus it is not an
    ecliptic position. Also note that the positions of the nodes are always
    calculated relative to the mean equinox 2000 and never precessed to the
    ecliptic or equator of date. For ecliptic positions of a perihelion or
    aphelion or a node, you should use the function ``nod_aps()`` or
    ``nod_aps_ut()`` (See chapter :doc:`apsides_nodes`).

.. autofunction:: swisseph.get_orbital_elements


..
