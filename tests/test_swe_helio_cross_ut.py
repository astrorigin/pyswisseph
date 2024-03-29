#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHelioCrossUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        pl = swe.SATURN
        jdx = swe.helio_cross_ut(pl, 30, 2455334.0, swe.FLG_SWIEPH, False)
        self.assertAlmostEqual(jdx, 2461855.379534041)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
