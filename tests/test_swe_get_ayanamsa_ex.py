#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetAyanamsaEx(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        flags = swe.FLG_SWIEPH | swe.FLG_NONUT
        swe.set_sid_mode(swe.SIDM_FAGAN_BRADLEY)
        retflags, daya = swe.get_ayanamsa_ex(2452275.5, flags)
        self.assertEqual(retflags, 66)
        self.assertEqual(retflags, flags)
        self.assertAlmostEqual(daya, 24.768237848066065)

    def test_02(self):
        flags = swe.FLG_SWIEPH
        swe.set_sid_mode(swe.SIDM_FAGAN_BRADLEY)
        retflags, daya = swe.get_ayanamsa_ex(2452275.5, flags)
        self.assertEqual(retflags, 2)
        self.assertEqual(retflags, flags)
        self.assertAlmostEqual(daya, 24.76365543416117)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
