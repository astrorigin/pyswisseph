#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGauquelinSector(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        body = swe.MERCURY
        method = 0
        geopos = (121.34, 43.57, 100)
        atpress = 0
        attemp = 0
        flags = swe.FLG_SWIEPH | swe.FLG_TOPOCTR
        sector = swe.gauquelin_sector(2452275.5, body, method, geopos,
                                      atpress, attemp, flags)
        self.assertAlmostEqual(sector, 36.20750588228443)

    def test_02(self):
        body = 'Regulus'
        method = 0
        geopos = (121.34, 43.57, 100)
        atpress = 0
        attemp = 0
        flags = swe.FLG_SWIEPH | swe.FLG_TOPOCTR
        sector = swe.gauquelin_sector(2452275.5, body, method, geopos,
                                      atpress, attemp, flags)
        self.assertAlmostEqual(sector, 16.172209424575335)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
