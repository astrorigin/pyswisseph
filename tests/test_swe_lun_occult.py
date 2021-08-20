#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweLunOccult(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2454466.5
        pl = swe.VENUS
        flags = swe.FLG_SWIEPH

        rflags, tret = swe.lun_occult_when_glob(jd, pl, flags, 0)

        self.assertEqual(rflags, 5)
        self.assertEqual(len(tret), 10)
        t1 = (2454531.2969454615, 2454531.3051413987, 2454531.1986291613,
                2454531.395079112, 2454531.1988858227, 2454531.3948235107,
                2454531.2206053897, 2454531.373120672, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        tjdut = tret[0]
        rflags, geopos, attr = swe.lun_occult_where(tjdut, pl, flags)

        self.assertEqual(rflags, 5)
        self.assertEqual(len(geopos), 10)
        t1 = (-132.44808390758698, -3.223940213770285, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(geopos[i], t1[i])

        self.assertEqual(len(attr), 20)
        t1 = (86.75745374029351, 172.52668487931908, 29765.456995447865,
                -3461.9137942605653, 336.20711850149934, 76.84479644566069,
                76.84858704296006, 1.8151476701449225e-05, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

        rflags, tret, attr = swe.lun_occult_when_loc(jd, pl, geopos[:3], flags)

        self.assertEqual(rflags, 32644)
        self.assertEqual(len(tret), 10)
        t1 = (2454531.2969437297, 2454531.259832862, 2454531.260291781,
                2454531.332817605, 2454531.3332567494, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        self.assertEqual(len(attr), 20)
        t1 = (1.0, 172.52667705000783, 1.0, -3461.913793849925,
                336.2047194072532, 76.84454490499999, 76.8483355773885,
                1.4787793334711022e-05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
