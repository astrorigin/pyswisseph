#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSetSidMode(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = swe.julday(2021, 8, 20, 12)
        xx, rflags = swe.calc_ut(jd, swe.VENUS)
        self.assertAlmostEqual(xx[0], 185.09289080174835)
        self.assertIsNone(swe.set_sid_mode(swe.SIDM_LAHIRI))
        xx, rflags = swe.calc_ut(jd, swe.VENUS, swe.FLG_SWIEPH|swe.FLG_SIDEREAL)
        self.assertAlmostEqual(xx[0], 160.93755436261293)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
