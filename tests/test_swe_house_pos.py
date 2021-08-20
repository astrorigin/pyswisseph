#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHousePos(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        tjdut = 2459445.15474537
        geolon = 6.63361
        geolat = 46.52194
        xx, retflags = swe.calc(tjdut, swe.ECL_NUT)
        eps = xx[0]
        armc = swe.degnorm(swe.sidtime(tjdut) * 15 + geolon)
        xx, retflags = swe.calc(tjdut, swe.SUN)
        hpos = swe.house_pos(armc, geolat, eps, xx[:2], b'P')
        self.assertAlmostEqual(hpos, 8.228061149703194)

    def test_02(self):
        hpos = swe.house_pos(0, 0, 0, (0, 0), b'P')
        self.assertAlmostEqual(hpos, 10.000000009259258)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
