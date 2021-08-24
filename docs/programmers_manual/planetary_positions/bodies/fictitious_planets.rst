==================
Fictitious planets
==================

Fictitious planets have numbers greater than or equal to 40. The user can
define his or her own fictitious planets. The orbital elements of these planets
must be written into the file ``seorbel.txt``. The function ``calc()`` looks
for the file ``seorbel.txt`` in the ephemeris path set by ``set_ephe_path()``.
If no orbital elements file is found, ``calc()`` uses the built-in orbital
elements of the above mentioned Uranian planets and some other bodies. The
planet number of a fictitious planet is defined as:

.. code-block:: python

    pl = swe.FICT_OFFSET - 1 + nth_fictitious_planet

e.g. for Kronos:

.. code-block:: python

    pl = 40 - 1 + 4 = 43

The file ``seorbel.txt`` has the following structure:

.. literalinclude:: seorbel.txt

All orbital elements except epoch and equinox may have T terms, where
``T = (tjd – epoch) / 36525``

(See, e.g., Vulcan, the second last elements set (not the "Uranian" Vulcanus
but the intramercurian hypothetical planet Vulcan).)
``T * T``, ``T2``, ``T3`` are also allowed.

The equinox can either be entered as a Julian day or as ``J1900`` or
``B1950`` or ``J2000`` or, if the equinox of date is required, as
``JDATE``. If you use T terms, note that precession has to be taken into
account with ``JDATE``, whereas it has to be neglected with fixed equinoxes.

No T term is required with the mean anomaly, i.e. for the speed of the body,
because our software can compute it from semi-axis and gravity. However, a mean
anomaly T term had to be added with Vulcan because its speed is not in
agreement with the laws of physics. In such cases, the software takes the speed
given in the elements and does not compute it internally.

From version 1.62 on, the software also accepts orbital elements for fictitious
bodies that move about the Earth. As an example, study the last elements set in
the excerpt of ``seorbel.txt`` above. After the name of the body, ``", geo"``
has to be added.

..
