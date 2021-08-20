#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHouseName(unittest.TestCase):

    def test_01(self):
        nam = swe.house_name(b'P')
        self.assertEqual(nam, 'Placidus')

    def test_notfound(self):
        nam = swe.house_name(b'?')
        self.assertEqual(nam, '')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
