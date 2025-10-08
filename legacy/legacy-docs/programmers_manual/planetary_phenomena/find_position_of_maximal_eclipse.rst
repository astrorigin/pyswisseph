================================
Find position of maximal eclipse
================================

This function can be used to find out the geographic position, where, for a
given time, a central eclipse is central or where a non-central eclipse is
maximal.

If you want to draw the eclipse path of a total or annular eclipse on a map,
first compute the start and end time of the total or annular phase with
``sol_eclipse_when_glob()``, then call ``sol_eclipse_how()`` for several time
intervals to get geographic positions on the central path. The northern and
southern limits of the umbra and penumbra are not implemented yet.

.. autofunction:: swisseph.sol_eclipse_where

..
