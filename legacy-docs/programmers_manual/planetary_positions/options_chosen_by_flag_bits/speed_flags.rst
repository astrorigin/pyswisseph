===========
Speed flags
===========

``calc()`` does not compute speed if you do not add the speed flag
``FLG_SPEED``. E.g:

.. code-block:: python

    flags |= swe.FLG_SPEED

The computation of speed is usually cheap, so you may set this bit by default
even if you do not need the speed.

..
