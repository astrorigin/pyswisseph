#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCs2Lonlatstr(unittest.TestCase):

    def test_01(self):
        s = swe.cs2lonlatstr(98923700, b' ', b'.')
        self.assertEqual(s, "274 47'17")

    def test_02(self):
        s = swe.cs2lonlatstr(-98923700, b' ', b'.')
        self.assertEqual(s, "274.47'17")

    def test_exception(self):
        with self.assertRaises(TypeError):
            s = swe.cs2lonlatstr(0, ' ', b'.')
        with self.assertRaises(TypeError):
            s = swe.cs2lonlatstr(0, b' ', '. ')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
