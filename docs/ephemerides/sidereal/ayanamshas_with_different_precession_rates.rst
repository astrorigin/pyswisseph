==========================================
Ayanamshas with different precession rates
==========================================

Some Hindu astrologers use ayanamshas based on a special precession rate which
is different from the modern precession algorithm used by the Swiss Ephemeris,
usually the precession rate used by the inventor of these particular
ayanamshas. They should be aware, however, that this approach makes only sense
if the tropical ephemeris they use is based on exactly the same precession
model. It is wrong to assume that tropical ephemerides are an absolute datum.

Modern ephemerides are generated relative to the sidereal reference frame ICRF
(International Celestial Reference Frame), which is close to the mean equinox
on 1 Jan. 2000, 12:00 TT. These sidereal "raw" ephemerides are transformed into
tropical ephemerides using a modern precession model. There are several such
models. Precession IAU 1976 (Lieske) is still used by JPL Horizons. The current
standard model recommended by the IAU is IAU 2006 (Capitaine). The Swiss
Ephemeris currently uses the precession model Vondrák (2011), which is
particularly good for very-long-term ephemerides. It follows that tropical
ephemerides will be different depending on the precession model that is used to
generate them. The differences will be extremely small for planetary positions
in current decades and centuries, but will grow considerably for remote epochs.
It also follows that if sidereal positions are calculated using a precession
model different from the one that was used to create the tropical ephemerides,
this is an inconsistent approach. In principle, the same precession model
should be used for ayanamsha as was used for the creation of the underlying
tropical ephemeris.

Now, we have the following problem: Some ayanamshas were defined at a time when
a different precession model was in use, either the precession model of Simon
Newcomb (1895) or the precession model IAU 1976. Using different precession
models, we will have differences in all the three, tropical planetary
positions, sidereal ephemeris positions, and ayanamsha values. Let us study
these differences in a table that shows all the three for an ayanamsha that has
its zero date on the equinox of the year 291 CE, on 21 March jul., 6:03 TT.
(V stands for precession Vondrák; N for precession Newcomb):

+-----------+-----------------------+-------------------+-----------------------+---------------+
| Year      | diff.trop.long.Sun    | diff.ayanamsha    | diff.sid.long.Sun     | ~minus        |
|           | (prec V-N) in "       | (prec V-N) in "   | (prec V-N) in "       | 17.650216"    |
+===========+=======================+===================+=======================+===============+
| -3000     | 81.648098             | 64.059809         | 17.588289             | -0.061927     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| -2500     | 77.891205             | 60.280286         | 17.610918             | -0.039297     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| -2000     | 67.756729             | 50.128935         | 17.627794             | -0.022422     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| -1500     | 55.131415             | 37.492205         | 17.639210             | -0.011006     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| -1000     | 42.521677             | 24.875658         | 17.646019             | -0.004197     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| -500      | 31.328666             | 13.679394         | 17.649271             | -0.000944     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 0         | 22.109197             | 4.458959          | 17.650238             | 0.000022      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| equ. 291  | 17.650216             | 0.000000          | 17.650216             | 0.000000      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 500       | 14.821773             | -2.828337         | 17.650110             | -0.000106     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 1000      | 9.060393              | -8.589402         | 17.649795             | -0.000421     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 1500      | 4.277578              | -13.372189        | 17.649767             | -0.000449     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 1700      | 2.525093              | -15.124766        | 17.649859             | -0.000357     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 1800      | 1.671280              | -15.978645        | 17.649925             | -0.000291     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 1900      | 0.829937              | -16.820066        | 17.650003             | -0.000213     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2000      | 0.000011              | -17.650081        | 17.650093             | -0.000123     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2100      | -0.818850             | -18.469044        | 17.650194             | -0.000022     |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2200      | -1.626143             | -19.276451        | 17.650307             | 0.000091      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2300      | -2.420577             | -20.071012        | 17.650435             | 0.000219      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2400      | -3.199913             | -20.850493        | 17.650580             | 0.000364      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 2500      | -3.960945             | -21.611692        | 17.650747             | 0.000531      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 3000      | -7.300452             | -24.952670        | 17.652218             | 0.002002      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 3500      | -9.010479             | -26.666760        | 17.656281             | 0.006065      |
+-----------+-----------------------+-------------------+-----------------------+---------------+
| 4000      | -7.165941             | -24.832623        | 17.666682             | 0.016466      |
+-----------+-----------------------+-------------------+-----------------------+---------------+

*As can be seen, the choice of precession model has a noticeable impact on
tropical ephemerides and the ayanamsha value. However, the difference in
sidereal ephemerides remains almost constant for the whole period considered.*

Now, let us assume this ayanamsha was introduced at a time when Newcomb
precession was used, but we use tropical positions based on the modern
precession model by Vondrak. If we still want to keep the sidereal ephemerides
unchanged, the above table shows that we need not necessarily use the old
precession model of Newcomb; instead, we can use modern precession Vondrák
instead, but have to subtract a constant value of 17.65022". The sidereal
ephemeris will then remain identical, but the tropical ephemeris and the
ayanamsha will change. Here, we must understand that the ayanamsha should not
be taken as an absolute value, it should only indicate the difference between
our tropical and our sidereal ephemeris. *With a future update of the precession
model in the Swiss Ephemeris, the tropical ephemeris and ayanamsha will change,
but the sidereal ephemeris will not*, because the ayanamsha value will be
adjusted automatically.

Let us also study an explicit comparison of tropical and sidereal positions of
the Sun based on both precession models Vondrák (V) and Newcomb (N) and also
using the above-mentioned correction to the ayanamsha:

=========== =================== =================== ===============
epoch       tropical Sun        sidereal Sun        ayanamsha
=========== =================== =================== ===============
-1000 V     271°14'15.75001     289°05'52.63883     342°08'23.11118
-1000 N     271°14'58.27229     289°05'52.63457     342°09'05.63773
eq291 V     359°59'42.34978     0°00'00.00000       359°59'42.34978
eq291 N     0°00'00.00000       0°00'00.00000       0°00'00.00000
1900 V      280°08'54.75103     257°46'10.69049     22°22'44.06054
1900 N      280°08'55.58096     257°46'10.69027     22°22'44.89070
2000 V      279°51'44.39186     256°05'12.79708     23°46'31.59478
2000 N      279°51'44.39187     256°05'12.79695     23°46'31.59492
=========== =================== =================== ===============

As can be seen, the tropical positions of the Sun and the ayanamshas, resulting
from the two different precession models, are identical only at the initial
epoch of the JPL ephemeris, on 1 Jan. 2000, whereas at other epochs they are
different from each oher. On the other hand, the sidereal positions of the Sun
are practically identical at all times, independently of the precession model
chosen.

Unfortunately, this makes the search for the "correct ayanamsha" even more
confused than many believe. Sidereal astrologers use to ask the question
whether Lahiri or Krishnamurti or whatever ayanamsha should be used, and they
believe that the ayanamsha can be defined by some fixed value at some initial
epoch. However, this is not correct. The start value or start date of an
ayanamsha, as well as its value on any other date, depend on the precession
model inherent in the tropical ephemeris used. This fact is usually forgotten.

Note, however, that this correction method is not used with all ayanamshas. The
above example uses the equinox of the year 291 as zero ayanamsha date, which is
actually the initial date of the Krishnamurti/Senthilathiban ayanamsha. In
reality, the described correction method is not applied here. The ayanamsha is
calculated using the current precession model of the Swiss Ephemeris (Vondrak
2011) without any correction. Sidereal ephemerides will be allowed to change
whenever the precession model will be updated.

Nor should the correction be done with the definition of Lahiri ayanamsha as
given by Lahiri himself in the preface of the 1980 edition of his "Indian
ephemeris", where zero ayanamsha is defined as the mean Sun on the equinox in
the year 285. When the Swiss Ephemeris updates the precession model, then the
zero ayanamsha date will have to be corrected, and the ayanamsha calculation
will also be done using the new precession model without any correction. This
will have some impact on sidereal ephemerides, however an unavoidable one.

Moreover, a correction is not required with True Chitra Paksha ayanamsha and
some other ayanamshas where the ayanamsha is based on the real position of a
fixed star. When the Swiss Ephemeris updates the precession model, this will
have practically no impact on the sidereal ephemerides or ayanamsha.

On the other hand, with the other definition of Lahiri ayanamsha as used by
Indian Astronomical Ephemeris, a correction will be required because the
definition is not based on some astronomical object or event, but on an
arbitrary value at an arbitrary epoch, based on the precession model IAU 1976.
A small correction will therefore be required to the ayanamsha in order to
provide identical sidereal positions while using our standard precession model
Vondrák 2011.

For each ayanamsha, a decision has to be taken individually what kind of
approach is required.

We hope that the Swiss Ephemeris, from version 2.09 on, handles this correctly,
and the user should not have to worry about precession models. One should be
aware, however, that the values given for some ayanamshas will be different
from those given in older literature. The reason is that the older literature
defines the ayanamsha value based on a different tropical ephemeris (and
precession model) than the Swiss Ephemeris.

The following ayanamshas have been corrected since version 2.09 by the
following values:

=================== =========== ===========
Ayanamsha           Correction  Prec. model
=================== =========== ===========
0 Fagan-Bradley     0.41256"    Newcomb
1 Lahiri            -0.13036"   IAU 1976
3 Raman             0.82800"    Newcomb
5 Krishnamurti      0.82800"    Newcomb
43 Lahiri (1967)    0.82800"    Newcomb
=================== =========== ===========

..
