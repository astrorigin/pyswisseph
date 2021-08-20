#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweFixstar2(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        flags = swe.FLG_SWIEPH | swe.FLG_SPEED
        xx, retnam, retflags = swe.fixstar2('Sirius', 2452275.5, flags)
        self.assertIsInstance(xx, tuple)
        self.assertEqual(len(xx), 6)
        self.assertAlmostEqual(xx[0], 104.11214970774336)
        self.assertAlmostEqual(xx[1], -39.60552633160544)
        self.assertAlmostEqual(xx[2], 543929.8571829783)
        self.assertAlmostEqual(xx[3], 7.988048904595391e-05)
        self.assertAlmostEqual(xx[4], -4.9099417570858335e-05)
        self.assertAlmostEqual(xx[5], -0.004141746210127001)
        self.assertEqual(retnam, 'Sirius,alCMa')
        self.assertEqual(retflags, 258)
        self.assertEqual(retflags, flags)

    def test_notfound(self):
        with self.assertRaises(swe.Error):
            xx, retnam, retflags = swe.fixstar2('xyz7', 2452275.5)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
