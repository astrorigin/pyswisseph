#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweDeltat(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        dt = swe.deltat(2452275.5)
        self.assertAlmostEqual(dt, 0.0007442138247935472)
        self.assertAlmostEqual(dt * 86400, 64.30007446216248)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
