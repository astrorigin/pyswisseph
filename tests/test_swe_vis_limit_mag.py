#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweVisLimitMag(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2452275.5
        geopos = (121.34, 43.57, 100)
        atmo = (0, 0, 0, 0)
        obs = (0, 0, 0, 0, 0, 0)
        obj = 'Venus'
        flags = swe.FLG_SWIEPH | swe.HELFLAG_OPTICAL_PARAMS
        res, dret = swe.vis_limit_mag(jd, geopos, atmo, obs, obj, flags)
        self.assertEqual(res, 0)
        self.assertEqual(len(dret), 10)
        t1 = (-8.216269236527388, 5.416663816613972, 130.2622919837906,
                3.9434996686342574, 127.36538544324537, 9.190664958012636,
                291.859517243866, -3.9127293193738018, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(dret[i], t1[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
