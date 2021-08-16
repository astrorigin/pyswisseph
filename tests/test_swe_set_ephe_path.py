#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSetEphePath(unittest.TestCase):

    def test_none(self):
        self.assertIsNone(swe.set_ephe_path(None))

    def test_noparam(self):
        self.assertIsNone(swe.set_ephe_path())

    def test_param(self):
        self.assertIsNone(swe.set_ephe_path("/path"))

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
