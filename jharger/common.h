#ifndef __JH_COMMON_H__
#define __JH_COMMON_H__

#define WRITE_DIGITS(num, buf, offset) \
    { \
        long __sf_l = 1000000000, __sf_h = 10000000000; \
        while(__sf_h >= 10) { \
            if(__sf_l <= num) { \
                buf[offset] = '0' + ((num % __sf_h) - (num % __sf_l)) / __sf_l; \
                offset++;  \
            } \
            __sf_h /= 10; \
            __sf_l /= 10; \
        } \
    }

#endif
