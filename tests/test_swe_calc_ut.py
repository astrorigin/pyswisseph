#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCalcUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        flags = swe.FLG_SWIEPH | swe.FLG_SPEED
        xx, retflags = swe.calc_ut(2452275.499255786, swe.SUN, flags)
        self.assertIsInstance(xx, tuple)
        self.assertIsInstance(retflags, int)
        self.assertEqual(len(xx), 6)
        self.assertEqual(retflags, 258)
        self.assertEqual(retflags, flags)
        self.assertAlmostEqual(xx[0], 280.38296810621137)
        self.assertAlmostEqual(xx[1], 0.0001496807056552454)
        self.assertAlmostEqual(xx[2], 0.9832978391484491)
        self.assertAlmostEqual(xx[3], 1.0188772348975301)
        self.assertAlmostEqual(xx[4], 1.7232637573749195e-05)
        self.assertAlmostEqual(xx[5], -1.0220875853441474e-05)

    def test_exception(self):
        with self.assertRaises(swe.Error):
            swe.calc_ut(2452275.499255786, -2)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
