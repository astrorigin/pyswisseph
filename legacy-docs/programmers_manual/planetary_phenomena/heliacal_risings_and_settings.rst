===============================
Heliacal risings, settings, etc
===============================

The function ``heliacal_ut()`` the Julian day of the next heliacal phenomenon
after a given start date. It works between geographic latitudes 60s – 60n.

.. autofunction:: swisseph.heliacal_ut

Strange phenomena:

Venus' heliacal rising can occur before her heliacal setting. In such cases the
planet may be seen both as a morning star and an evening star for a couple of
days. Example:

.. code-block:: console

    swetest -hev1 -p3 -b1.1.2008 -geopos8,47,900 -at1000,10,20,0.15 -obs21,1 -n1 -lmt

    Venus heliacal rising : 2009/03/23 05:30:12.4 LMT (2454913.729310), visible for: 4.9 min

    swetest -hev2 -p3 -b1.1.2008 -geopos8,47,900 -at1000,10,20,0.15 -obs21,1 -n1 -lmt

    Venus heliacal setting: 2009/03/25 18:37:41.6 LMT (2454916.276175), visible for: 15.1 min

With good visibility and good eye sight (high Snellen ratio), the "evening
first" of the Moon may actually begin in the morning, because the Moon becomes
visible before sunset. Note the LMT and duration of visibility in the following
example:

.. code-block:: console

    swetest -hev3 -p1 -b1.4.2008 -geopos8,47,900 -at1000,10,40,0.15 -obs21,1.5 -n1 -lmt

    Moon evening first : 2008/04/06 10:33:44.3 LMT (2454562.940096), visible for: 530.6 min

Stars that are circumpolar, but come close to the horizon, may have an evening
last and a morning first, but ``heliacal_ut()`` will not find it. It only works
if a star crosses the horizon.

In high geographic latitudes > 55 (?), unusual things may happen. E.g. Mars can
have a morning last appearance. In case the period of visibility lasts for less
than 5 days, the function ``heliacal_ut()`` may miss the morning first.

With high geographic latitudes heliacal appearances of Mercury and Venus become
rarer.

The user must be aware that strange phenomena occur especially for high
geographic latitudes and circumpolar objects and that the function
``heliacal_ut()`` may not always be able to handle them correctly. Special
cases can best be researched using the function ``vis_limit_mag()`` (See
chapter :doc:`magnitude_limit_for_visibility`).

..
