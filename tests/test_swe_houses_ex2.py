#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHousesEx2(unittest.TestCase):

    def test_01(self):
        cusps, ascmc, csp, asp = swe.houses_ex2(2452275.499255786, 43.23,
                                                12.77, b'P', 0)
        self.assertEqual(len(cusps), 12)
        self.assertEqual(len(ascmc), 8)
        self.assertEqual(len(csp), 12)
        self.assertEqual(len(asp), 8)
        t1 = (197.7589389586125, 224.81302787267524, 256.4076591301128,
                291.2531386724461, 324.9380050470959, 353.97936025175477,
                17.758938958612475, 44.81302787267521, 76.40765913011279,
                111.25313867244611, 144.9380050470959, 173.97936025175477)
        t2 = (197.7589389586125, 111.25313867244611, 112.97316806332762,
                42.79394839801842, 204.79923835131163, 219.659810760679,
                197.11057619698795, 39.659810760679)
        t3 = (278.1656323926639, 300.65922861468, 323.0701701988959,
                339.3784704721397, 334.33238124601553, 309.12605791608553,
                278.1656323926639, 300.65922861468, 323.0701701988959,
                339.3784704721397, 334.33238124601553, 309.12605791608553)
        t4 = (278.1656323926639, 339.3784704721397, 360.98564733498665,
                577.3667034553781, 382.49956811151407, 553.3015456763735,
                268.117199017849, 553.3015456763735)
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
