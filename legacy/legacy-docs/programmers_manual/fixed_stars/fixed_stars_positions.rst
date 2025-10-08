=========================
Get fixed stars positions
=========================

The fixed stars functions only work if the fixed stars data file
``sefstars.txt`` is found in the ephemeris path. If the file ``sefstars.txt``
is not found, the old file ``fixstars.cat`` is searched and used instead, if
present. However, it is strongly recommended to *not* use the old file anymore.
The data in the file are outdated, and the algorithms are also not as accurate
as those used with the file ``sefstars.txt``.

That file is found there: https://www.astro.com/ftp/swisseph/ephe/

.. autofunction:: swisseph.fixstar_ut

.. autofunction:: swisseph.fixstar

.. autofunction:: swisseph.fixstar2_ut

.. autofunction:: swisseph.fixstar2

Distances are given in AU. (To convert them from AU to lightyears or parsec,
you can use the following constants: ``swe.AUNIT_TO_LIGHTYEAR`` and
``swe.AUNIT_TO_PARSEC``.)

The daily motions of the fixed stars contain components of precession,
nutation, aberration, parallax and the proper motions of the stars.

If a star is found, its name is returned in the following format:
``traditional_name,nomenclature_name`` e.g. ``"Aldebaran,alTau"``.

The nomenclature name is usually the so-called Bayer designation or the
Flamsteed designation, in some cases also Henry Draper (HD) or other
designations.

As for the explanation of the other parameters, see the documentation for
``calc()``:
:doc:`/programmers_manual/planetary_positions/options_chosen_by_flag_bits/the_use_of_flag_bits`

.. note::

    Barycentric positions are not implemented. The difference between
    geocentric and heliocentric fixed star position is noticeable and arises
    from parallax and gravitational deflection.

Search behaviors of the functions
=================================

The function has three modes to search for a star in the file ``sefstars.txt``:

**Behavior of new functions fixstar2() and fixstar2_ut()**

- star contains a traditional name: the first star in the file ``sefstars.txt``
  is used whose traditional name fits the given name. All names are mapped to
  lower case before comparison and white spaces are removed.

  *Changed behavior:* The search string must match the complete star name. If
  you want to use a partial string, you have to add the wildcard character
  ``%`` to the search string, e.g. ``aldeb%``. (The old functions treat each
  search string as ending with a wildcard.)

  The ``%`` can only be used at the end of the search string and only with
  the traditional star name, not with nomenclature names (i.e. not with Bayer
  or Flamsteed designations).

  Both the full traditional name and the nomenclature name are returned,
  separated by a comma. E.g. if star is given the value ``aldeb``, then
  ``fixstar()`` returns ``Aldebaran,alTau``. That string can also be used for
  a new search of the same star.

- star contains a comma, followed by a nomenclature name, e.g. ``,alTau``: the
  search string is understood to be the nomenclature name (the second field in
  a star record). Letter case is observed in the comparison for nomenclature
  names.

- star contains a positive number (in ASCII string format, e.g. ``"234"``):
  *Changed behavior:* The numbering of stars follows a sorted list of
  nomenclature names. (With the old functions, the n-th star of the fixed
  star file is returned.)

**Behavior of old functions fixstar() and fixstar_ut()**

- star contains a traditional name: the first star in the file ``sefstars.txt``
  is used whose traditional name fits the given name. All names are mapped to
  lower case before comparison and white spaces are removed.

  If star has n characters, only the first n characters of the traditional
  name field are compared.

  Both the full traditional name and the nomenclature name are returned,
  separated by a comma. E.g. if star is given the value ``aldeb``, then
  ``fixstar()`` returns ``Aldebaran,alTau``. That string can also be used for
  a new search of the same star.

- star begins with a comma, followed by a nomenclature name, e.g. ``,alTau``:
  the search string is understood to be the nomenclature name (the second
  field in a star record). Letter case is observed in the comparison for
  nomenclature names. Here again, star name is returned, e.g.
  ``Aldebaran,alTau``.

- star contains a positive number (in ASCII string format, e.g. ``"234"``):
  The star data in the 234-th non-comment line in the file ``sefstars.txt``
  are used. Comment lines that begin with ``#`` and are ignored. Here again,
  star name is returned as traditional name and nomenclature name,
  separated by a comma, e.g. ``Aldebaran,alTau``.

For correct spelling of nomenclature names, see file ``sefstars.txt``.
Nomenclature names are usually Bayer designations and are composed of a Greek
letter and the name of a star constellation. The Greek letters were originally
used to write numbers, therefore they actually number the stars of the
constellation. The abbreviated nomenclature names we use in ``sefstars.txt``
are constructed from two lowercase letters for the Greek letter (e.g. ``al``
for ``alpha``; except ``omi`` and ``ome``) and three letters for the
constellation (e.g. ``Tau`` for ``Tauri``).

The searching of stars by sequential number (instead of name or nomenclature
name) is a practical feature if one wants to list all stars:

.. code-block:: python

    for i in range(1, 10000): # any number greater than number of lines in sefstars.txt
        star = '%d' % i
        try:
            xx, retnam, retflags = swe.fixstar2_ut(star, tjd, flags)
        except swe.Error:
            break
        # do something with star positions ...

The functions should survive damaged ``sefstars.txt`` files which contain
illegal data and star names exceeding the accepted length. Such fields are cut
to acceptable length.

You may edit the star catalogue and move the stars you prefer to the top of the
file. With older versions of the Swiss Ephemeris, this will increase the speed
of computations. The search mode is linear through the whole star file for each
call of ``fixstar()``.

However, since SE 2.07 with the new functions ``fixstar2()`` and
``fixstar2_ut()``, this won't speed up calculations anymore, and the
calculation speed will be the same for all stars.

Reference
=========

There are a few special entries in the file ``sefstars.txt`` too. The file is
included here for reference:

.. literalinclude:: sefstars.txt

..
