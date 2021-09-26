#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweTidAcc(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        tidacc = (swe.TIDAL_DE200,
                swe.TIDAL_DE403,
                swe.TIDAL_DE404,
                swe.TIDAL_DE405,
                swe.TIDAL_DE406,
                swe.TIDAL_DE421,
                swe.TIDAL_DE422,
                swe.TIDAL_DE430,
                swe.TIDAL_DE431,
                swe.TIDAL_DE441,
                swe.TIDAL_26,
                swe.TIDAL_STEPHENSON_2016,
                swe.TIDAL_DEFAULT,
                swe.TIDAL_MOSEPH,
                swe.TIDAL_SWIEPH,
                swe.TIDAL_JPLEPH)
        values = (-23.8946, -25.58, -25.58, -25.826, -25.826, -25.85,
                -25.85, -25.82, -25.8, -25.936, -26.0, -25.85, -25.8,
                -25.58, -25.8, -25.8)
        for i, acc in enumerate(tidacc):
            swe.set_tid_acc(acc)
            self.assertEqual(swe.get_tid_acc(), values[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
