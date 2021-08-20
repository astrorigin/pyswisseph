#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import swisseph as swe
import unittest

class TestSweSolEclipse(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        swe.set_ephe_path()

    def test_01(self):
        jd = 2454466.5
        flags = swe.FLG_SWIEPH

        res, tret = swe.sol_eclipse_when_glob(jd, flags, 0)

        self.assertEqual(res, 9)
        self.assertEqual(len(tret), 10)
        t1 = (2454503.663211855, 2454503.6311452035, 2454503.5686268248,
                2454503.758220716, 2454503.638833451, 2454503.6878238786,
                2454503.641705153, 2454503.6849778416, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        tjdut = tret[0]
        rflags, geopos, attr = swe.sol_eclipse_where(tjdut, flags)

        self.assertEqual(rflags, 9)
        self.assertEqual(len(geopos), 10)
        t1 = (-150.2657563045994, -67.54726332710979,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(geopos[i], t1[i])

        self.assertEqual(len(attr), 20)
        t1 = (0.9808845283315087, 0.9657677495562372, 0.9327073460829188,
                123.54231134128423, 88.56597938283562, 16.22875801863979,
                16.283962210232154, 0.0010808703550863033, 0.9657677495562372,
                121.0, 60.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

        rflags, tret, attr = swe.sol_eclipse_when_loc(jd, geopos[:3], flags)

        self.assertEqual(rflags, 8072)
        self.assertEqual(len(tret), 10)
        t1 = (2454503.663290394, 2454503.6195803564, 2454503.662529968,
                2454503.664052095, 2454503.705140964,
                0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(10):
            self.assertAlmostEqual(tret[i], t1[i])

        self.assertEqual(len(attr), 20)
        t1 = (0.9820490545500833, 0.9657656089841425, 0.9327032114965115,
                123.53921693495896, 88.53993924248994, 16.21794102890504,
                16.273181670269107, 0.00045073507822495805, 0.9657656089841425,
                121.0, 60.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

        rflags, attr = swe.sol_eclipse_how(tjdut, geopos[:3], flags)

        self.assertEqual(rflags, 137)
        self.assertEqual(len(attr), 20)
        t1 = (0.9808845283315087, 0.9657677495562372, 0.9327073460829188,
                123.54231134128423, 88.56597938283562, 16.22875801863979,
                16.283962210232154, 0.0010808703550863033, 0.9657677495562372,
                121.0, 60.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
        for i in range(20):
            self.assertAlmostEqual(attr[i], t1[i])

if __name__ == '__main__':
    unittest.main()

# vi: sw=4 ts=4 et
