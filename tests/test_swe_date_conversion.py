#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDateConversion(unittest.TestCase):

    def test_01(self):
        isvalid, jd, dt = swe.date_conversion(2002, 13, 1, 0, b'g')
        self.assertIsInstance(isvalid, bool)
        self.assertFalse(isvalid)
        self.assertEqual(jd, 2452640.5)
        self.assertEqual(dt, (2003, 1, 1, 0.0))

    def test_02(self):
        isvalid, jd, dt = swe.date_conversion(2002, 1, 1, 0, b'g')
        self.assertIsInstance(isvalid, bool)
        self.assertTrue(isvalid)
        self.assertEqual(jd, 2452275.5)
        self.assertEqual(dt, (2002, 1, 1, 0.0))

    def test_invalidcal(self):
        with self.assertRaises(ValueError):
            isvalid, jd, dt = swe.date_conversion(2020, 4, 23, 23.654, b'z')
        with self.assertRaises(TypeError):
            isvalid, jd, dt = swe.date_conversion(2020, 4, 23, 23.654, 'z')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
