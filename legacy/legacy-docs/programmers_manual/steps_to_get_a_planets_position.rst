================================================
The programming steps to get a planet's position
================================================

To compute a celestial body or point with *Pyswisseph*, you have to do the
following steps. The details of the functions will be explained in the
following chapters.

.. code-block:: python

    # import the library
    import swisseph as swe
    # set the directory path of the ephemeris files
    swe.set_ephe_path("/usr/local/share/sweph/ephe")
    # from the birth date, compute the julian day number
    jul_day_ut = swe.julday(year, month, day, hour, gregflag)
    # compute a planet or other bodies
    xx, retflags = swe.calc_ut(jul_day_ut, planet_no, flags)
    # or a fixed star
    xx, retnam, retflags = swe.fixstar_ut(star_nam, jul_day_ut, flags)

If you want to work with Ephemeris Time, you have to proceed as follows
instead.

.. code-block:: python

    # if necessary, convert universal time (ut) to ephemeris time (et)
    jul_day_et = jul_day_ut + swe.deltat(jul_day_ut)
    # then compute a planet or other bodies
    xx, retflags = swe.calc(jul_day_et, planet_no, flags)
    # or a fixed star
    xx, retnam, retflags = swe.fixstar(star_nam, jul_day_et, flags)
    # at the end of your computations close all files and free memory
    swe.close()

Here is a miniature sample script.

.. literalinclude:: swemini.py
    :language: python

.. note::

    Throughout this manual, expect to see the module name ``swisseph``
    imported as ``swe``, which is shorter and reminds of the ``swe_`` prefix
    of the C API.

..
