#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCotransSp(unittest.TestCase):

    def test_01(self):
        coord = (121.34, 43.57, 1.0, 1.1, 5.5, 1.0)
        xx = swe.cotrans_sp(coord, 23.4)
        self.assertIsInstance(xx, tuple)
        self.assertEqual(len(xx), 6)
        self.assertAlmostEqual(xx[0], 114.11984833491826)
        self.assertAlmostEqual(xx[1], 22.754921351892474)
        self.assertAlmostEqual(xx[2], 1.0)
        self.assertAlmostEqual(xx[3], -0.4936723489509314)
        self.assertAlmostEqual(xx[4], 5.538766604142424)
        self.assertAlmostEqual(xx[5], 1.0)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
