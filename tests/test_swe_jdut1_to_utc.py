#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweJdut1ToUtc(unittest.TestCase):

    def test_01(self):
        y, m, d, h, mi, s = swe.jdut1_to_utc(2452275.499255786, swe.GREG_CAL)
        self.assertEqual(y, 2001)
        self.assertEqual(m, 12)
        self.assertEqual(d, 31)
        self.assertEqual(h, 23)
        self.assertEqual(mi, 58)
        self.assertEqual(s, 55.815998911857605)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
