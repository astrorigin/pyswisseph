#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHeliacalUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2452275.5
        geopos = (121.34, 43.57, 100)
        atmo = (0, 0, 0, 0)
        observ = (0, 0, 0, 0, 0, 0)
        obj = 'Venus'
        eventtp = swe.HELIACAL_RISING
        flags = swe.FLG_SWIEPH | swe.HELFLAG_OPTICAL_PARAMS
        beg, opt, end = swe.heliacal_ut(jd, geopos, atmo, observ, obj,
                                        eventtp, flags)
        self.assertAlmostEqual(beg, 2452586.417484313)
        self.assertAlmostEqual(opt, 2452586.424000514)
        self.assertAlmostEqual(end, 2452586.431350049)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
