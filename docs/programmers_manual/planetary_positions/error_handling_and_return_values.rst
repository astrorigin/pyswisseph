================================
Error handling and return values
================================

``calc()`` (as well as ``calc_ut()``, ``fixstar()``, and ``fixstar_ut()``)
returns a 32-bit integer value. This value is >= 0, if the function call was
successful, and if not, an exception (``Error``) is raised with a message.

An exception is raised in one of the following cases:

- if an illegal body number has been specified
- if a Julian day beyond the ephemeris limits has been specified
- if the length of the ephemeris file is not correct (damaged file)
- on read error, e.g. a file index points to a position beyond file length
  (data on file are corrupt)
- if the copyright section in the ephemeris file has been destroyed

If any of these errors occurs, the type of error is indicated by a
corresponding message.

On success, the return code contains flag bits that indicate what kind of
computation has been done. This value will usually be equal to the flags,
however sometimes may differ from them. If an option specified by the flags
cannot be fulfilled or makes no sense, ``calc()`` just does what can be done.
E.g., if you specify that you want JPL ephemeris, but ``calc()`` cannot find
the ephemeris file, it tries to do the computation with any available
ephemeris. The ephemeris actually used will be indicated in the returned flags.
So, to make sure that ``calc()`` has found the ephemeris required, you may want
to check, e.g.:

.. code-block:: python

    try:
        xx, retflags = swe.calc_ut(jdut, pl, swe.FLG_JPLEPH)
    except swe.Error as err:
        # fatal error occurred
        handle_error(err)
    if not retflags & swe.FLG_JPLEPH:
        # JPL ephemeris was not used...
        go_on()

The returned flags are useful for debugging purposes or for understanding what
exactly has been done by the function.

Some flags may be removed, if they are incompatible with other flags, e.g.:

- if two or more ephemerides are combined
- if the topocentric flag is combined with the heliocentric or the barycentric
  flag.
- etc.

Some flags may be added in the following cases:

- If no ephemeris flag was specified, the returned flags contain
  ``FLG_SWIEPH``
- With J2000 calculations or other sidereal calculations, the no-nutation flag
  ``FLG_NONUT`` is added
- With heliocentric and barycentric calculations, the flags for "no
  aberration" ``FLG_NOABERR`` and "no light deflection" ``FLG_NOGDEFL``
  are added.

 ..
