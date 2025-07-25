#ifndef __CONST_H__
#define __CONST_H__

#ifdef USE_DOUBLE_PRECISION
#define nml_t double
#define kEPSILON 1e-12
#else
#define nml_t float
#define kEPSILON 1e-6
#endif // USE_DOUBLE_PRECISION

/*
* +------------------------------+
* |--- Mathematical constants ---|
* +------------------------------+
*/

// pi
static const nml_t kPI = 3.14159265358979323846264338328;

// pi/2
static const nml_t kPI_2 = 1.57079632679489661923132169164;

// pi/4
static const nml_t kPI_4 = 0.78539816339744830961566084582;

// pi/3
static const nml_t kPI_3 = 1.04719755119659774615421446109;

// pi/6
static const nml_t kPI_6 = 0.52359877559829887307710723054;

// 2pi
static const nml_t k2PI = 6.28318530717958647692528676655;

// pi/180
static const nml_t kPI_180 = 0.01745329251994329576923690768;

// 180/pi
static const nml_t k180_PI = 57.2957795130823208767981548141;

// e
static const nml_t kE = 2.71828182845904523536028747135;

// log_2(e)
static const nml_t kLOG2E = 1.44269504088896340735992468100;

// log_10(e)
static const nml_t kLOG10E = 0.43429448190325182765112891892;

// Euler-Mascheroni constant
static const nml_t kEULER = 0.57721566490153286060651209008;

#endif // !__CONST_H__
