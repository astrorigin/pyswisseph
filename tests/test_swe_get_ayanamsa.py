#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetAyanamsa(unittest.TestCase):

    def test_01(self):
        swe.set_sid_mode(swe.SIDM_FAGAN_BRADLEY)
        ay = swe.get_ayanamsa(2452275.5)
        self.assertAlmostEqual(ay, 24.768237848066065)

    def test_02(self):
        swe.set_sid_mode(swe.SIDM_LAHIRI)
        ay = swe.get_ayanamsa(2452275.5)
        self.assertAlmostEqual(ay, 23.88503020705366)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
