#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCsroundsec(unittest.TestCase):

    def test_01(self):
        cs = swe.csroundsec(145)
        self.assertEqual(cs, 100)

    def test_02(self):
        cs = swe.csroundsec(150)
        self.assertEqual(cs, 200)

    def test_03(self):
        cs = swe.csroundsec(595900)
        self.assertEqual(cs, 595900)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
