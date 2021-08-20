#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweGetTidAcc(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        tidacc = swe.get_tid_acc()
        self.assertEqual(tidacc, -25.8)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
