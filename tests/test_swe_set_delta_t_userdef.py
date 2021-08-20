#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSetDeltaTUserdef(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    @classmethod
    def tearDownClass(cls): # reset for other tests to pass
        swe.set_delta_t_userdef(swe.DELTAT_AUTOMATIC)

    def test_01(self):
        self.assertIsNone(swe.set_delta_t_userdef(0.0008))
        dt = swe.deltat(2452275.5)
        self.assertEqual(dt, 0.0008)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
