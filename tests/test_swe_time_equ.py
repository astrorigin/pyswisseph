#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweTimeEqu(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        e = swe.time_equ(2452275.5)
        self.assertAlmostEqual(e, -0.0022853565661411796)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
