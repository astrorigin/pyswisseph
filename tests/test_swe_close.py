#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweClose(unittest.TestCase):

    def test(self):
        self.assertIsNone(swe.close())

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
