#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetCurrentFileData(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        xx, retflags = swe.calc(2452275.5, swe.SUN, swe.FLG_SWIEPH)
        path, start, end, denum = swe.get_current_file_data(1)
        self.assertIn("semo_18.se1", path)
        self.assertAlmostEqual(start, 2378487.555370702)
        self.assertAlmostEqual(end, 2597656.457452471)
        self.assertEqual(denum, 431)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
