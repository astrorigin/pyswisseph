#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweHeliacalPhenoUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2452275.5
        geopos = (121.34, 43.57, 100)
        atmo = (0, 0, 0, 0)
        observ = (0, 0, 0, 0, 0, 0)
        objnam = 'Venus'
        eventflg = swe.HELIACAL_RISING
        helflg = swe.FLG_SWIEPH | swe.HELFLAG_OPTICAL_PARAMS
        dret = swe.heliacal_pheno_ut(jd, geopos, atmo, observ, objnam,
                                     eventflg, helflg)
        self.assertEqual(len(dret), 50)
        results = (5.416663816613972,
                5.563551975509116,
                5.418086146718076,
                130.2622919837906,
                3.9434996686342574,
                127.36538544324537,
                1.4731641479797144,
                1.4745864780838183,
                -2.896906540545217,
                3.2503260647091565,
                0.2666957382692506,
                -14.14203621134163,
                2452275.478566518,
                2452275.478567518,
                99999999.0,
                99999999.0,
                0.0,
                0.0,
                0.0,
                0.0014223301041038638,
                -3.9127293193738018,
                2452275.4713436686,
                2452275.478913715,
                -0.007570046465843916,
                99999999.0,
                0.0,
                3.247819358354831,
                99.85299277914767,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(50):
            self.assertAlmostEqual(dret[i], results[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
