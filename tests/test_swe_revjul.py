#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweRevjul(unittest.TestCase):

    def test_01(self):
        dt = swe.revjul(2452275.5, swe.GREG_CAL)
        self.assertEqual(dt, (2002, 1, 1, 0.0))

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
