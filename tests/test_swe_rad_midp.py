#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweRadMidp(unittest.TestCase):

    def test_01(self):
        x = swe.rad_midp(0, 3.14159)
        self.assertEqual(x, 1.570795)

    def test_02(self):
        x = swe.rad_midp(3.14159, 0)
        self.assertEqual(x, 1.570795)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
