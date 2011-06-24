/** @file swephelp.d
** @brief D bindings for Swephelp
*/

module swephelp;

version ( Tango )
{
    import tango.stdc.math;
}
version ( Phobos )
{
    import phobos.std.c.math;
}

public import swisseph;


/* *** Stuff that must be implemented in D (macros) *** */

// From swhdatetime.h

double swh_julday( int year, int mon, int day, int hour, int min, int sec, int flag )
{
    return swe_julday( year, mon, day, ((hour)+((min)/60.0)+((sec)/3600.0)), flag );
}

// From swhformat.h

int swh_geolat2c( double coord, char *ret )
{
    return swh_geod2c((coord), 90, (ret));
}

int swh_geolon2c( double coord, char *ret )
{
    swh_geod2c((coord), 180, (ret));
}

// From swhraman.h

int swh_long2rasi( double longitude )
{
    return (cast(int) (swe_degnorm(longitude) / 30.0));
}

int swh_long2navamsa( double longitude )
{
    return (cast(int) (swe_degnorm(longitude) / (10/3.0)) % 12);
}

int swh_rasinorm( int rasi )
{
    return ((rasi) < 0 ?
        ((rasi) + (12 * (1 + cast(int) ((rasi) / -12)))) % 12 : (rasi) % 12);
}

int swh_tatkalika_relation( int r1, int r2 )
{
    return (abs(swh_rasi_dif2((r1), (r2))) <= 3 ? 1 : -1);
}


/* *** Declarations ***  */

extern (C):

// From swhdatetime.h

double swh_jdnow();

int swh_revjul( double jd, int flag, int *dt );

int swh_dt2i( char *dt, int *ret );

// From swhdef.h

/* Aspects */
const SWH_CONJUNCTION     = 0;
const SWH_SQUISEXTILE     = 15;
const SWH_SEMINOVILE      = 20;
const SWH_SQUISQUARE      = 22.5;
const SWH_UNDECILE        = (360/11.0);
const SWH_SEMISEXTILE     = 30;
const SWH_SEMIQUINTILE    = 36;
const SWH_NOVILE          = 40;
const SWH_SEMISQUARE      = 45;
const SWH_SEPTILE         = (360/7.0);
const SWH_SEXTILE         = 60;
const SWH_BIUNDECILE      = ((360/11.0)*2);
const SWH_QUINTILE        = 72;
const SWH_BINOVILE        = 80;
const SWH_SQUARE          = 90;
const SWH_TRIUNDECILE     = ((360/11.0)*3);
const SWH_BISEPTILE       = ((360/7.0)*2);
const SWH_TRINE           = 120;
const SWH_QUADUNDECILE    = ((360/11.0)*4);
const SWH_SESQUISQUARE    = 135;
const SWH_BIQUINTILE      = 144;
const SWH_QUINCUNX        = 150;
const SWH_TRISEPTILE      = ((360/7.0)*3);
const SWH_QUATRONOVILE    = 160;
const SWH_QUINUNDECILE    = ((360/11.0)*5);
const SWH_OPPOSITION      = 180;

/* Signs */
const SWH_ARIES       = 0;
const SWH_TAURUS      = 1;
const SWH_GEMINI      = 2;
const SWH_CANCER      = 3;
const SWH_LEO         = 4;
const SWH_VIRGO       = 5;
const SWH_LIBRA       = 6;
const SWH_SCORPIO     = 7;
const SWH_SAGITTARIUS = 8;
const SWH_CAPRICORN   = 9;
const SWH_AQUARIUS    = 10;
const SWH_PISCES      = 11;

const SWH_MESHA       = SWH_ARIES;
const SWH_VRISHABA    = SWH_TAURUS;
const SWH_MITHUNA     = SWH_GEMINI;
const SWH_KATAKA      = SWH_CANCER;
const SWH_SIMHA       = SWH_LEO;
const SWH_KANYA       = SWH_VIRGO;
const SWH_THULA       = SWH_LIBRA;
const SWH_VRISHIKA    = SWH_SCORPIO;
const SWH_DHANUS      = SWH_SAGITTARIUS;
const SWH_MAKARA      = SWH_CAPRICORN;
const SWH_KUMBHA      = SWH_AQUARIUS;
const SWH_MEENA       = SWH_PISCES;

/* Planets */
const SWH_RAVI        = 0;
const SWH_CHANDRA     = 1;
const SWH_BUDHA       = 2;
const SWH_SUKRA       = 3;
const SWH_KUJA        = 4;
const SWH_GURU        = 5;
const SWH_SANI        = 6;
const SWH_RAHU        = 10;
const SWH_KETU        = -10;

const SWH_SURYA       = SWH_RAVI;
const SWH_SOMA        = SWH_CHANDRA;
const SWH_SOUMYA      = SWH_BUDHA;
const SWH_BHARGAVA    = SWH_SUKRA;
const SWH_ANGARAKA    = SWH_KUJA;
const SWH_BRIHASPATI  = SWH_GURU;
const SWH_MANDA       = SWH_SANI;
const SWH_THAMA       = SWH_RAHU;
const SWH_SIKHI       = SWH_KETU;

/* Nakshatras */
const SWH_ASWINI          = 0;
const SWH_BHARANI         = 1;
const SWH_KRITHIKA        = 2;
const SWH_ROHINI          = 3;
const SWH_MRIGASIRA       = 4;
const SWH_ARIDRA          = 5;
const SWH_PUNARVASU       = 6;
const SWH_PUSHYAMI        = 7;
const SWH_ASLESHA         = 8;
const SWH_MAKHA           = 9;
const SWH_PUBBA           = 10;
const SWH_UTTARA          = 11;
const SWH_HASTA           = 12;
const SWH_CHITTA          = 13;
const SWH_SWATHI          = 14;
const SWH_VISHAKA         = 15;
const SWH_ANURADHA        = 16;
const SWH_JYESTA          = 17;
const SWH_MOOLA           = 18;
const SWH_POORVASHADA     = 19;
const SWH_UTTARASHADA     = 20;
const SWH_SRAVANA         = 21;
const SWH_DHANISHTA       = 22;
const SWH_SATABISHA       = 23;
const SWH_POORVABHADRA    = 24;
const SWH_UTTARABHADRA    = 25;
const SWH_REVATHI         = 26;


// From swhformat.h

int swh_degsplit(double pos, int *ret);

int swh_signtostr(int sign, char *str);

int swh_house_system_name(char hsys, char *str);

int swh_house_system_id(char hsys);

char swh_house_system_char(int hsys);

int swh_sidereal_mode_flag(int sidmode);

int swh_sidereal_mode_id(int sidmode);


// From swhgeo.h

int swh_geoc2d(char *coord, double *ret);

int swh_geod2i(double coord, int *ret);

int swh_geod2c(double coord, int maxdeg, char *ret);


// From swhraman.h

int swh_raman_houses(double asc, double mc, double *ret, int sandhi);

int swh_lord(int sign);

int swh_long2nakshatra(double longitude, int *ret);

int swh_get_nakshatra_name(int nakshatra, char *str);

int swh_rasi_dif(int r1, int r2);

int swh_rasi_dif2(int r1, int r2);

int swh_naisargika_relation(int gr1, int gr2, int *ret);

int swh_residential_strength(double graha, double *bm, double *ret);

double swh_ochchabala(int graha, double sputha);


// From swhsearch.h

int swh_min_retro_time(int planet, char *err);

int swh_max_retro_time(int planet, char *err);

int swh_next_retro(int planet, double jdstart, double step, int backw,
    double dayspan, int flag, double *jdret, double *posret, char *err);

int swh_go_past(int planet, double fixedpt, double jdstart, double step,
    int backw, int flag, double *jdret, double *posret, char *err);

int swh_next_aspect(int planet, double aspect, double fixedpt, double jdstart,
    double step, int backw, double dayspan, int flag, double *jdret,
    double *posret, char *err);

int swh_next_aspect2(int planet, double aspect, double fixedpt, double jdstart,
    double step, int backw, double dayspan, int flag, double *jdret,
    double *posret, char *err);

int swh_next_aspect_with(int planet, double aspect, int other, char *star,
    double jdstart, double step, int backw, double dayspan, int flag,
    double *jdret, double *posret0, double *posret1, char *err);

int swh_next_aspect_with2(int planet, double aspect, int other, char *star,
    double jdstart, double step, int backw, double dayspan, int flag,
    double *jdret, double *posret0, double *posret1, char *err);

int swh_next_aspect_cusp(int planet, char *star, double aspect, int cusp,
    double jdstart, double lat, double lon, int hsys, double step, int backw,
    int flag, double *jdret, double *posret, double *cuspsret, double *ascmcret,
    char *err);

int swh_next_aspect_cusp2(int planet, char *star, double aspect, int cusp,
    double jdstart, double lat, double lon, int hsys, double step, int backw,
    int flag, double *jdret, double *posret, double *cuspsret, double *ascmcret,
    char *err);

int swh_match_aspect(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor);

int swh_match_aspect2(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor);

int swh_match_aspect3(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor);

int swh_match_aspect4(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor);

int swh_years_diff(double jd1, double jd2, int flag, double *years, char *err);

