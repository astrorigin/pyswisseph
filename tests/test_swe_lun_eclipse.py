#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweLunEclipse(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2454466.5
        flags = swe.FLG_SWIEPH
        geopos = (12.1, 49.0, 330)

        rflags, tret = swe.lun_eclipse_when(jd, flags, 0)

        self.assertEqual(rflags, 4)
        self.assertEqual(len(tret), 10)
        t1 = (2454517.6430690456, 0.0, 2454517.57172334, 2454517.7144189165,
                2454517.6258038115, 2454517.6603509136, 2454517.525389122,
                2454517.7608554545, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        tjdut = tret[0]
        rflags, tret, attr = swe.lun_eclipse_when_loc(tjdut, geopos, flags)

        self.assertEqual(rflags, 29584)
        self.assertEqual(len(tret), 10)
        t1 = (2454695.3820517384, 0.0, 2454695.316710297, 2454695.447390333,
                0.0, 0.0, 2454695.2672055247, 2454695.496797575, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        self.assertEqual(len(attr), 20)
        t1 = (0.8076127691060245, 1.8366497324296667, 0.0, 0.0,
                326.9885866287668, 21.362590458352507, 21.402251051495636,
                0.5301609960196174, 0.8076127691060245, 138.0, 28.0, 28.0,
                28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

        rflags, attr = swe.lun_eclipse_how(tjdut, geopos, flags)

        self.assertEqual(rflags, 4)
        self.assertEqual(len(attr), 20)
        t1 = (1.1061093373639495, 2.145134309769692, 0.0, 0.0,
                73.8203145568749, 26.299290272560974, 26.330700027276947,
                0.3801625589840114, 1.1061093373639495, 133.0, 26.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
