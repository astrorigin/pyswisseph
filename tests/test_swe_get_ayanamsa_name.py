#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestGetAyanamsaName(unittest.TestCase):

    def test_01(self):
        name = swe.get_ayanamsa_name(swe.SIDM_FAGAN_BRADLEY)
        self.assertEqual(name, 'Fagan/Bradley')

    def test_notfound(self):
        name = swe.get_ayanamsa_name(99999)
        self.assertEqual(name, '')


if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
