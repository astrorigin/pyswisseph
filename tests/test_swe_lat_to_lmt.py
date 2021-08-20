#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweLatToLmt(unittest.TestCase):

    def test_01(self):
        jdlmt = swe.lat_to_lmt(2452275.4978254, 121.34)
        self.assertAlmostEqual(jdlmt, 2452275.500000003)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
