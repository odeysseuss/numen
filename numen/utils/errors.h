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
    NML_ENULLMEM = 9, // null pointer
};

#define is_null(...)                                        \
    do {                                                          \
        void *_pointers[] = {__VA_ARGS__};                        \
        size_t _count = sizeof(_pointers) / sizeof(_pointers[0]); \
        for (size_t _i = 0; _i < _count; _i++) {                  \
            if (_pointers[_i] == NULL)                            \
                return NML_ENULLMEM;                              \
        }                                                         \
    } while (0)

#endif // !__NML_ERRNO_H__
