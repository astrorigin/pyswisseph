#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDifrad2n(unittest.TestCase):

    def test_01(self):
        d = swe.difrad2n(6.283185, 9.424777)
        self.assertAlmostEqual(d, -3.141592000000001)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
