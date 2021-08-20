#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHousesArmcEx2(unittest.TestCase):

    def test_01(self):
        cusps, ascmc, csp, asp = swe.houses_armc_ex2(121.34, 43.57, 23.4, b'P')
        self.assertEqual(len(cusps), 12)
        self.assertEqual(len(ascmc), 8)
        self.assertEqual(len(csp), 12)
        self.assertEqual(len(asp), 8)
        t1 = (204.11984833491826, 231.64344809042643, 263.8428626994282,
                299.20001710444353, 332.7652475027196, 1.1456557646008605,
                24.119848334918288, 51.64344809042643, 83.84286269942822,
                119.20001710444356, 152.76524750271963, 181.14565576460086)
        t2 = (204.11984833491826, 119.20001710444356, 121.34, 54.8393353009063,
                213.5658324793495, 232.02126521735147, 203.41011079832296,
                52.02126521735148)
        t3 = (276.4139536100446, 299.730979103177, 326.5846451217515,
                346.06208747721655, 338.1223758253722, 308.6247371425512,
                276.4139536100446, 299.730979103177, 326.5846451217515,
                346.06208747721655, 338.1223758253722, 308.6247371425512)
        t4 = (276.4139536100446, 346.06208747721655, 360.98564733498665,
                500.5109719337671, 374.37069005115444, 493.376119298585,
                268.4290225688941, 493.376119298585)
        for i in range(12):
            self.assertAlmostEqual(cusps[i], t1[i])
        for i in range(8):
            self.assertAlmostEqual(ascmc[i], t2[i])
        for i in range(12):
            self.assertAlmostEqual(csp[i], t3[i])
        for i in range(8):
            self.assertAlmostEqual(asp[i], t4[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
