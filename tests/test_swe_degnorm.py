#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDegnorm(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.degnorm(0), 0)

    def test_02(self):
        self.assertEqual(swe.degnorm(360), 0)

    def test_03(self):
        self.assertEqual(swe.degnorm(-1), 359)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
