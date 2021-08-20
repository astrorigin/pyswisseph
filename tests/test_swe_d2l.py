#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweD2l(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.d2l(90.4), 90)

    def test_02(self):
        self.assertEqual(swe.d2l(90.5), 91)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
