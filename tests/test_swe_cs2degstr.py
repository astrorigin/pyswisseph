#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCs2Degstr(unittest.TestCase):

    def test_01(self):
        s = swe.cs2degstr(98923700)
        self.assertIsInstance(s, str)
        self.assertEqual(s, " 4°47'17")

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
