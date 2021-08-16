#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCalcPctr(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        flags = swe.FLG_SWIEPH | swe.FLG_SPEED
        xx, retflags = swe.calc_pctr(2452275.5, swe.MOON, swe.MERCURY, flags)
        self.assertIsInstance(xx, tuple)
        self.assertIsInstance(retflags, int)
        self.assertEqual(len(xx), 6)
        self.assertEqual(retflags, flags)
        self.assertEqual(retflags, 258)
        self.assertAlmostEqual(xx[0], 115.5945576959893)
        self.assertAlmostEqual(xx[1], 2.0541309173647004)
        self.assertAlmostEqual(xx[2], 1.2326810399357166)
        self.assertAlmostEqual(xx[3], 1.5728585729521045)
        self.assertAlmostEqual(xx[4], -0.05039719564878364)
        self.assertAlmostEqual(xx[5], -0.01808367783365082)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
