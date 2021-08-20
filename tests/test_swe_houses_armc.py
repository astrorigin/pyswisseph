#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHousesArmc(unittest.TestCase):

    def test_01(self):
        cusps, ascmc = swe.houses_armc(0, 0, 23.4, b'P')
        self.assertEqual(len(cusps), 12)
        self.assertEqual(len(ascmc), 8)
        t1 = (90.0,
                117.9175900855148,
                147.82641197634797,
                180.0,
                212.17358802365203,
                242.0824099144852,
                270.0,
                297.9175900855148,
                327.82641197634797,
                0.0,
                32.17358802365204,
                62.0824099144852)
        t2 = (90.0, 0.0, 0.0, 180.0, 90.0, 90.0, 180.0, 270.0)
        for i in range(12):
            self.assertAlmostEqual(cusps[i], t1[i])
        for i in range(8):
            self.assertAlmostEqual(ascmc[i], t2[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
