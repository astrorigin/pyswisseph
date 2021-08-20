#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHouses(unittest.TestCase):

    def test_01(self):
        cusps, ascmc = swe.houses(2452275.499255786, 0, 0, b'P')
        self.assertEqual(len(cusps), 12)
        self.assertEqual(len(ascmc), 8)
        t1 = (191.0989364639854,
                222.65039973002735,
                251.72382204055555,
                279.3768461762848,
                307.79074786727415,
                338.5782564089493,
                11.09893646398541,
                42.650399730027345,
                71.72382204055555,
                99.3768461762848,
                127.79074786727413,
                158.5782564089493)
        t2 = (191.0989364639854,
                99.3768461762848,
                100.20316806332762,
                0.0,
                191.09893646398544,
                191.09893646398544,
                180.0,
                11.09893646398543)
        for i in range(12):
            self.assertAlmostEqual(cusps[i], t1[i])
        for i in range(8):
            self.assertAlmostEqual(ascmc[i], t2[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
