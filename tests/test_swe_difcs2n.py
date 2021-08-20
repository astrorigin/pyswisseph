#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDifcs2n(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.difcs2n(360 * 360000, 540 * 360000), -64800000)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
