=======================================================
The Planets X of Leverrier, Adams, Lowell and Pickering
=======================================================

These are the hypothetical planets that have led to the discovery of Neptune
and Pluto or at least have been brought into connection with them. Their
enormous deviations from true Neptune and Pluto may be interesting for
astrologers who work with hypothetical bodies. E.g. Leverrier and Adams are
good only around the 1840ies, the discovery epoch of Neptune. To check this,
call the program swetest as follows:

.. code-block:: console

    $ swetest -p8 -dU -b1.1.1770 -n8 -s7305 -hel -fPTLBR -head

(i.e.: compute planet 8 (Neptune) - planet 'U' (Leverrier), from 1.1.1770, 8
times, in 7305-day-steps, heliocentrically. You can do this from the Internet
web page swetest.htm. The output will be:)


======= =========== ======================= ======================= =========================
--      Date        Difference_longitude    Difference_latitude     Difference_solar_distance
======= =========== ======================= ======================= =========================
Nep-Lev 01.01.1770  -18°0'52.3811           0°55'0.0332             -6.610753489
Nep-Lev 01.01.1790  -8°42'9.1113            1°42'55.7192            -4.257690148
Nep-Lev 02.01.1810  -3°49'45.2014           1°35'12.0858            -2.488363869
Nep-Lev 02.01.1830  -1°38'2.8076            0°35'57.0580            -2.112570665
Nep-Lev 02.01.1850  1°44'23.0943            -0°43'38.5357           -3.340858070
Nep-Lev 02.01.1870  9°17'34.4981            -1°39'24.1004           -5.513270186
Nep-Lev 02.01.1890  21°20'56.6250           -1°38'43.1479           -7.720578177
Nep-Lev 03.01.1910  36°27'56.1314           -0°41'59.4866           -9.265417529
======= =========== ======================= ======================= =========================

One can see that the error is in the range of 2 degrees between 1830 and 1850
and grows very fast beyond that period.

..
