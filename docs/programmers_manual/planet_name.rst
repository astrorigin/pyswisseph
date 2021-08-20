========================
Get the name of a planet
========================

This function allows to find a planetary or asteroid name, when the planet
number is given. The function definition is:

.. autofunction:: swisseph.get_planet_name

.. note::

    Another asteroid file named ``seasnam2.txt`` can be found. It contains the
    same names but is sorted by asteroid designation, instead of by number.

    You can recreate that file with the following command:

    .. code-block:: console

        sort -k 1.7 seasnam.txt > seasnam2.txt

Here is a very short sample of the contents of the file ``seasnam.txt``,
followed by another sample of ``seasnam2.txt``, both found at
https://www.astro.com/ftp/swisseph/ephe/.

``seasnam.txt``:

.. literalinclude:: seasnam_sample.txt

``seasnam2.txt``:

.. literalinclude:: seasnam2_sample.txt

..
