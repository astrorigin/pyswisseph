#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDegMidp(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.deg_midp(0, 180), 90)

    def test_02(self):
        self.assertEqual(swe.deg_midp(180, 0), 270)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
