#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSplitDeg(unittest.TestCase):

    def test_00(self):
        x = swe.split_deg(123.123, 0)
        t1 = (123, 7, 22, 0.8000000000167731, 1)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_01(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_ROUND_SEC)
        t1 = (123, 7, 23, 23, 1)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_02(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_ROUND_MIN)
        t1 = (123, 7, 52, 52, 1)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_03(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_ROUND_DEG)
        t1 = (123, 37, 22, 22, 1)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_04(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_ZODIACAL)
        t1 = (3, 7, 22, 0.8000000000167731, 4)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_05(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_NAKSHATRA)
        t1 = (3, 7, 22, 0.8000000001126963, 9)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

    def test_06(self):
        x = swe.split_deg(123.123, swe.SPLIT_DEG_KEEP_SIGN)
        t1 = (123, 7, 22, 0.8000000000167731, 1)
        for i in range(5):
            if i == 3: self.assertAlmostEqual(x[i], t1[i])
            else: self.assertEqual(x[i], t1[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
