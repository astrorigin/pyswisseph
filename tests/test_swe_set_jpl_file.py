#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSetJplFile(unittest.TestCase):

    def test_01(self):
        self.assertIsNone(swe.set_jpl_file('de431.eph'))

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
