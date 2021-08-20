#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweRadnorm(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.radnorm(0), 0.0)

    def test_02(self):
        self.assertEqual(swe.radnorm(6.2831853071796), 0.0)

    def test_03(self):
        x = swe.radnorm(-0.017453292519943)
        self.assertAlmostEqual(x, 6.265732014659643)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
