#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCsnorm(unittest.TestCase):

    def test_01(self):
        cs = swe.csnorm(360 * 360000)
        self.assertEqual(cs, 0)

    def test_02(self):
        cs = swe.csnorm(540 * 360000)
        self.assertEqual(cs, 64800000)
        self.assertEqual(cs, swe.csnorm(180 * 360000))

    def test_03(self):
        cs = swe.csnorm(-720 * 360000)
        self.assertEqual(cs, 0)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
