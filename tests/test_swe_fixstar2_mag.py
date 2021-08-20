#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweFixstar2Mag(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        mag, retnam = swe.fixstar2_mag('Sirius')
        self.assertEqual(mag, -1.46)
        self.assertEqual(retnam, 'Sirius,alCMa')

    def test_notfound(self):
        with self.assertRaises(swe.Error):
            mag, retnam = swe.fixstar2_mag('xyz7')

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
