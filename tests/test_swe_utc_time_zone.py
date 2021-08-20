#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweUtcTimeZone(unittest.TestCase):

    def test_01(self):
        utc = swe.utc_time_zone(2000, 1, 1, 0, 0, 0, 7)
        t1 = (1999, 12, 31, 17, 0, 0.0)
        self.assertEqual(utc, t1)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
