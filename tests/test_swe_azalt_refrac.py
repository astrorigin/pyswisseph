#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

geo = (12.1, 49.0, 330)
tjdut = 2454503.06
atpress = 0
attemp = 30
flags = swe.FLG_SWIEPH

class TestSweAzaltRefrac(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        pl = swe.SUN
        xx, retflags = swe.calc_ut(tjdut, pl, flags)

        az, true_alt, app_alt = swe.azalt(tjdut, swe.ECL2HOR, geo, atpress,
                                          attemp, xx[:3])
        self.assertAlmostEqual(az, 31.000507789830635)
        self.assertAlmostEqual(true_alt, 19.979725380019925)
        self.assertAlmostEqual(app_alt, 20.01972200258643)

        lon, lat = swe.azalt_rev(tjdut, swe.HOR2ECL, geo, az, true_alt)
        self.assertAlmostEqual(lon, 317.1314505588256)
        self.assertAlmostEqual(lat, -8.170833565488458e-05)

        appalt = swe.refrac(true_alt, atpress, attemp, swe.TRUE_TO_APP)
        self.assertAlmostEqual(appalt, 19.979725380019925)

        appalt, dret = swe.refrac_extended(true_alt, geo[2], atpress, attemp,
                                           10, swe.TRUE_TO_APP)
        self.assertAlmostEqual(appalt, 19.97613868241318)
        self.assertEqual(len(dret), 4)
        self.assertAlmostEqual(dret[0], 19.979725380019925)
        self.assertAlmostEqual(dret[1], 19.97613868241318)
        self.assertAlmostEqual(dret[2], -0.0035866976067475092)
        self.assertAlmostEqual(dret[3], -0.5828252112086314)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
