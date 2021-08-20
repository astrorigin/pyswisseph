#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSidtime0(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        sidtime = swe.sidtime0(2452275.5, 23.4, 121.34)
        self.assertAlmostEqual(sidtime, 14.122424609363085)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
