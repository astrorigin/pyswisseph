#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSidtime(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        sidtime = swe.sidtime(2452275.5)
        self.assertAlmostEqual(sidtime, 6.69812123973034)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
