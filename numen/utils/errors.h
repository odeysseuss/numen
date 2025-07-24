#ifndef __ERRNO_H__
#define __ERRNO_H__

enum {
    NML_SUCCESS = 0,
    NML_FAILURE = -1,
    NML_EDOM = 1,     // input domain error
    NML_ERANGE = 2,   // output range error
    NML_EINVAL = 3,   // invalid argument provided by user
    NML_ENOMEM = 4,   // memory allocation error
    NML_EZERODIV = 5, // tried to divide by zero
    NML_ENAN = 6,     // (0.0/0.0)
    NML_EOVRFLW = 7,  // overflow
    NML_EUNDRFLW = 8, // underflow
};

#endif // !__NML_ERRNO_H__
