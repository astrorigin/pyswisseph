#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweVersion(unittest.TestCase):

    def test_type(self):
        self.assertIsInstance(swe.version, str)

    def test_split(self):
        parts = swe.version.split('.')
        self.assertEqual(len(parts), 3)
        se_version_major = int(parts[0])
        se_version_minor = int(parts[1])
        se_version_path = int(parts[2])
        self.assertEqual(se_version_major, 2)
        self.assertEqual(se_version_minor, 10)
        self.assertEqual(se_version_path, 3)

class TestSwe__Version__(unittest.TestCase):

    def test_type(self):
        self.assertIsInstance(swe.__version__, int)

    def test_length(self):
        version = str(swe.__version__)
        self.assertEqual(len(version), 8)

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
