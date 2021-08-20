#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCotrans(unittest.TestCase):

    def test_01(self):
        coord = (121.34, 43.57, 1.0)
        xx = swe.cotrans(coord, 23.4)
        self.assertIsInstance(xx, tuple)
        self.assertEqual(len(xx), 3)
        self.assertAlmostEqual(xx[0], 114.11984833491826)
        self.assertAlmostEqual(xx[1], 22.754921351892474)
        self.assertAlmostEqual(xx[2], 1.0)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
