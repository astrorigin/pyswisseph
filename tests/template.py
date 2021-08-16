#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestX(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    pass

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
