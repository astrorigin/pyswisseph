#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDifdegn(unittest.TestCase):

    def test_01(self):
        self.assertEqual(swe.difdegn(360.5, 540), 180.5)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
