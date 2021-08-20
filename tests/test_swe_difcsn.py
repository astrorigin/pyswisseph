#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestDifcsn(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.difcsn(360 * 360000, 540 * 360000), 64800000);

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
