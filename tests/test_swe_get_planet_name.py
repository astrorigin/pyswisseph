#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetPlanetName(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        name = swe.get_planet_name(swe.NEPTUNE)
        self.assertEqual(name, 'Neptune')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
