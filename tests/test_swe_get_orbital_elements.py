#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetOrbitalElements(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        tjdet = 2452275.5
        pl = swe.MERCURY
        flags = swe.FLG_SWIEPH | swe.FLG_HELCTR
        elem = swe.get_orbital_elements(tjdet, pl, flags)
        self.assertEqual(len(elem), 50)
        results = (0.3870973114030973,
                0.20564082670656994,
                7.0048323528425,
                48.32860267825048,
                29.134014946238988,
                77.46261762448947,
                284.23849955213836,
                260.55807731881237,
                272.46706882819836,
                1.701117176627804,
                0.24085023933428615,
                4.0923600982534065,
                0.24085768924789555,
                -115.87662942301525,
                2452206.0441132435,
                0.3074943002702738,
                0.46670032253592075,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(50):
            self.assertAlmostEqual(elem[i], results[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
