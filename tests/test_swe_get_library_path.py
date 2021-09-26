#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from platform import system
import swisseph as swe
import unittest

class TestSweGetLibraryPath(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        path = swe.get_library_path()
        if system() != 'Windows':
            self.assertIn('swisseph', path)
        else:
            self.assertNotEqual(path, '')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
