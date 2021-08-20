#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweRiseTrans(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        tjdut = 2459414.1041666665 # 2021/07/18 14:30
        pl = swe.MOON
        rsmi = 0
        geopos = (6.57, 43.21, 0) # La Croix Valmer, France
        atpress = 0
        attemp = 0
        horhgt = 0
        flags = 0
        res, tret = swe.rise_trans_true_hor(tjdut, pl, rsmi, geopos,
                                            atpress, attemp, horhgt, flags)
        self.assertEqual(res, 0)
        self.assertAlmostEqual(tret[0], 2459415.105139496)

    def test_02(self):
        tjdut = 2459414.1041666665
        pl = 'Aldebaran'
        rsmi = 0
        geopos = (6.57, 43.21, 0)
        atpress = 0
        attemp = 0
        horhgt = 0
        flags = 0
        res, tret = swe.rise_trans_true_hor(tjdut, pl, rsmi, geopos,
                                            atpress, attemp, horhgt, flags)
        self.assertEqual(res, 0)
        self.assertAlmostEqual(tret[0], 2459414.551462413)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
