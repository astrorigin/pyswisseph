#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweFixstar2Ut(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        flags = swe.FLG_SWIEPH | swe.FLG_SPEED | swe.FLG_EQUATORIAL
        xx, retnam, retflags = swe.fixstar2_ut('Polaris', 2452275.5, flags)
        self.assertIsInstance(xx, tuple)
        self.assertEqual(len(xx), 6)
        self.assertAlmostEqual(xx[0], 38.64742459858111)
        self.assertAlmostEqual(xx[1], 89.27646936051526)
        self.assertAlmostEqual(xx[2], 27356067.783757936)
        self.assertAlmostEqual(xx[3], -0.005939286663743433)
        self.assertAlmostEqual(xx[4], 7.651842909477333e-05)
        self.assertAlmostEqual(xx[5], -0.008465268179057073, places=4)
        self.assertEqual(retnam, 'Polaris,alUMi')
        self.assertEqual(retflags, 2306)
        self.assertEqual(retflags, flags)

    def test_notfound(self):
        with self.assertRaises(swe.Error):
            xx, retnam, retflags = swe.fixstar2_ut('xyz7', 2452275.5)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
