#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweLmtToLat(unittest.TestCase):

    def test_01(self):
        jdlat = swe.lmt_to_lat(2452275.5, 121.34)
        self.assertAlmostEqual(jdlat, 2452275.497825397)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
