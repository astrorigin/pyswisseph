#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweCs2Timestr(unittest.TestCase):

    def test_01(self):
        s = swe.cs2timestr(8496000, b':', False)
        self.assertEqual(s, "23:36:00")

    def test_02(self):
        s = swe.cs2timestr(8496000, b':', True)
        self.assertEqual(s, "23:36")

    def test_exception(self):
        with self.assertRaises(TypeError):
            s = swe.cs2timestr(0, b'::', True)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
