==============================
Magnitude limit for visibility
==============================

The function ``vis_limit_mag()`` determines the limiting visual magnitude in
dark skies. If the visual magnitude mag of an object is known for a given date
(e. g. from a call of function ``pheno_ut()``, and if mag is smaller than the
value returned by ``vis_limit_mag()``, then it is visible.

.. autofunction:: swisseph.vis_limit_mag

..
