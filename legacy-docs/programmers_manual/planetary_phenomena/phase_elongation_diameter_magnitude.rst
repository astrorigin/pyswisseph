==========================================================================
Phase, phase angle, elongation, apparent diameter, apparent magnitude, etc
==========================================================================

These functions compute phase, phase angle, elongation, apparent diameter,
apparent magnitude for the Sun, the Moon, all planets and asteroids. The two
functions do exactly the same but expect a different time parameter.

.. note::

    the lunar magnitude is quite a complicated thing, but our algorithm is
    very simple. The phase of the moon, its distance from the Earth and the
    sun is considered, but no other factors.

    ``flags`` also allows ``FLG_TRUEPOS``, ``FLG_HELCTR``

.. autofunction:: swisseph.pheno_ut

.. autofunction:: swisseph.pheno

..
