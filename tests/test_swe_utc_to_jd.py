#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweUtcToJd(unittest.TestCase):

    def test_01(self):
        jdet, jdut = swe.utc_to_jd(2000, 1, 1, 0, 0, 0, swe.GREG_CAL)
        self.assertAlmostEqual(jdet, 2451544.5007428704)
        self.assertAlmostEqual(jdut, 2451544.5000041146)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
