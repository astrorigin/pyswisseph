=======================================================
Attributes of occultation for a given position and time
=======================================================

Similar to ``sol_eclipse_where(),`` this function can be used to find out the
geographic position, where, for a given time, a central eclipse is central or
where a non-central eclipse is maximal. With occultations, it tells us, at
which geographic location the occulted body is in the middle of the lunar disc
or closest to it. Because occultations are always visible from a very large
area, this is not very interesting information. But it may become more
interesting as soon as the limits of the umbra (and penumbra) will be
implemented.

.. autofunction:: swisseph.lun_occult_where

..
