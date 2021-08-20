#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDayOfWeek(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.day_of_week(2452275.5), 1)

    def test_02(self):
        self.assertEqual(swe.day_of_week(2459444.0), 1)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
