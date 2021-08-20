#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweJulday(unittest.TestCase):

    def test_01(self):
        jd = swe.julday(2002, 1, 1, 0, swe.GREG_CAL)
        self.assertEqual(jd, 2452275.5)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
