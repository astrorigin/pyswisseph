#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSwePhenoUt(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2454503.6
        attr = swe.pheno_ut(jd, swe.SUN, swe.FLG_SWIEPH)
        res = (0.0, 0.0, 0.0, 0.5406109972747988, -26.890234268000295, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], res[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
