#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSolcrossUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        x = swe.solcross_ut(30, 2455334.0, swe.FLG_SWIEPH)
        self.assertAlmostEqual(x, 2455671.928764275)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
