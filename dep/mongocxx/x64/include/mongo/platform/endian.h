/*    Copyright 2014 MongoDB Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "mongo/config.h"

#include <cstring>
#include <boost/static_assert.hpp>

#include "mongo/platform/cstdint.h"

#pragma push_macro("MONGO_UINT16_SWAB")
#pragma push_macro("MONGO_UINT32_SWAB")
#pragma push_macro("MONGO_UINT64_SWAB")
#pragma push_macro("MONGO_LITTLE_ENDIAN")
#pragma push_macro("MONGO_BIG_ENDIAN")
#pragma push_macro("htobe16")
#pragma push_macro("htobe32")
#pragma push_macro("htobe64")
#pragma push_macro("htole16")
#pragma push_macro("htole32")
#pragma push_macro("htole64")
#pragma push_macro("be16toh")
#pragma push_macro("be32toh")
#pragma push_macro("be64toh")
#pragma push_macro("le16toh")
#pragma push_macro("le32toh")
#pragma push_macro("le64toh")

#undef MONGO_UINT16_SWAB
#undef MONGO_UINT32_SWAB
#undef MONGO_UINT64_SWAB
#undef MONGO_LITTLE_ENDIAN
#undef MONGO_BIG_ENDIAN
#undef htobe16
#undef htobe32
#undef htobe64
#undef htole16
#undef htole32
#undef htole64
#undef be16toh
#undef be32toh
#undef be64toh
#undef le16toh
#undef le32toh
#undef le64toh

#define MONGO_LITTLE_ENDIAN 1234
#define MONGO_BIG_ENDIAN 4321

#if defined(_MSC_VER) && (_MSC_VER >= 1300)
# include <cstdlib>
# define MONGO_UINT16_SWAB(v) _byteswap_ushort(v)
# define MONGO_UINT32_SWAB(v) _byteswap_ulong(v)
# define MONGO_UINT64_SWAB(v) _byteswap_uint64(v)
#elif defined(__clang__) && defined(__clang_major__) && defined(__clang_minor__) && \
  (__clang_major__ >= 3) && (__clang_minor__ >= 1)
# if __has_builtin(__builtin_bswap16)
#  define MONGO_UINT16_SWAB(v) __builtin_bswap16(v)
# endif
# if __has_builtin(__builtin_bswap32)
#  define MONGO_UINT32_SWAB(v) __builtin_bswap32(v)
# endif
# if __has_builtin(__builtin_bswap64)
#  define MONGO_UINT64_SWAB(v) __builtin_bswap64(v)
# endif
#elif defined(__GNUC__) && (__GNUC__ >= 4)
# if __GNUC__ >= 4 && defined (__GNUC_MINOR__) && __GNUC_MINOR__ >= 3
#  define MONGO_UINT32_SWAB(v) __builtin_bswap32(v)
#  define MONGO_UINT64_SWAB(v) __builtin_bswap64(v)
# endif
# if __GNUC__ >= 4 && defined (__GNUC_MINOR__) && __GNUC_MINOR__ >= 8
#  define MONGO_UINT16_SWAB(v) __builtin_bswap16(v)
# endif
#elif defined(__sun)
# include <sys/byteorder.h>
# define MONGO_UINT16_SWAB(v) BSWAP_16(v)
# define MONGO_UINT32_SWAB(v) BSWAP_32(v)
# define MONGO_UINT64_SWAB(v) BSWAP_64(v)
#endif

#ifndef MONGO_UINT16_SWAB
# define MONGO_UINT16_SWAB(v) endian::bswap_slow16(v)
#endif

#ifndef MONGO_UINT32_SWAB
# define MONGO_UINT32_SWAB(v) endian::bswap_slow32(v)
#endif

#ifndef MONGO_UINT64_SWAB
# define MONGO_UINT64_SWAB(v) endian::bswap_slow64(v)
#endif

#if MONGO_BYTE_ORDER == MONGO_LITTLE_ENDIAN
# define htobe16(v) MONGO_UINT16_SWAB(v)
# define htobe32(v) MONGO_UINT32_SWAB(v)
# define htobe64(v) MONGO_UINT64_SWAB(v)
# define htole16(v) (v)
# define htole32(v) (v)
# define htole64(v) (v)
# define be16toh(v) MONGO_UINT16_SWAB(v)
# define be32toh(v) MONGO_UINT32_SWAB(v)
# define be64toh(v) MONGO_UINT64_SWAB(v)
# define le16toh(v) (v)
# define le32toh(v) (v)
# define le64toh(v) (v)
#elif MONGO_BYTE_ORDER == MONGO_BIG_ENDIAN
# define htobe16(v) (v)
# define htobe32(v) (v)
# define htobe64(v) (v)
# define htole16(v) MONGO_UINT16_SWAB(v)
# define htole32(v) MONGO_UINT32_SWAB(v)
# define htole64(v) MONGO_UINT64_SWAB(v)
# define be16toh(v) (v)
# define be32toh(v) (v)
# define be64toh(v) (v)
# define le16toh(v) MONGO_UINT16_SWAB(v)
# define le32toh(v) MONGO_UINT32_SWAB(v)
# define le64toh(v) MONGO_UINT64_SWAB(v)
#else
# error "The endianness of target architecture is unknown. " \
        "Please define MONGO_BYTE_ORDER"
#endif

namespace mongo {
namespace endian {

    static inline uint16_t bswap_slow16(uint16_t v) {
        return ((v & 0x00FF) << 8) |
               ((v & 0xFF00) >> 8);
    }

    static inline uint32_t bswap_slow32(uint32_t v) {
        return ((v & 0x000000FFUL) << 24) |
               ((v & 0x0000FF00UL) <<  8) |
               ((v & 0x00FF0000UL) >>  8) |
               ((v & 0xFF000000UL) >> 24);
    }

    static inline uint64_t bswap_slow64(uint64_t v) {
        return ((v & 0x00000000000000FFULL) << 56) |
               ((v & 0x000000000000FF00ULL) << 40) |
               ((v & 0x0000000000FF0000ULL) << 24) |
               ((v & 0x00000000FF000000ULL) <<  8) |
               ((v & 0x000000FF00000000ULL) >>  8) |
               ((v & 0x0000FF0000000000ULL) >> 24) |
               ((v & 0x00FF000000000000ULL) >> 40) |
               ((v & 0xFF00000000000000ULL) >> 56);
    }

} // namespace endian

    template<typename T>
    struct ByteOrderConverter;

    template<>
    struct ByteOrderConverter<uint8_t> {

        typedef uint8_t T;

        inline static T nativeToBig(T t) {
            return t;
        }

        inline static T bigToNative(T t) {
            return t;
        }

        inline static T nativeToLittle(T t) {
            return t;
        }

        inline static T littleToNative(T t) {
            return t;
        }
    };

    template<>
    struct ByteOrderConverter<uint16_t> {

        typedef uint16_t T;

        inline static T nativeToBig(T t) {
            return htobe16(t);
        }

        inline static T bigToNative(T t) {
            return be16toh(t);
        }

        inline static T nativeToLittle(T t) {
            return htole16(t);
        }

        inline static T littleToNative(T t) {
            return le16toh(t);
        }
    };

    template<>
    struct ByteOrderConverter<uint32_t> {

        typedef uint32_t T;

        inline static T nativeToBig(T t) {
            return htobe32(t);
        }

        inline static T bigToNative(T t) {
            return be32toh(t);
        }

        inline static T nativeToLittle(T t) {
            return htole32(t);
        }

        inline static T littleToNative(T t) {
            return le32toh(t);
        }
    };

    template<>
    struct ByteOrderConverter<uint64_t> {

        typedef uint64_t T;

        inline static T nativeToBig(T t) {
            return htobe64(t);
        }

        inline static T bigToNative(T t) {
            return be64toh(t);
        }

        inline static T nativeToLittle(T t) {
            return htole64(t);
        }

        inline static T littleToNative(T t) {
            return le64toh(t);
        }
    };

    template<>
    struct ByteOrderConverter<int8_t> {

        typedef int8_t T;

        inline static T nativeToBig(T t) {
            return t;
        }

        inline static T bigToNative(T t) {
            return t;
        }

        inline static T nativeToLittle(T t) {
            return t;
        }

        inline static T littleToNative(T t) {
            return t;
        }
    };

    template<>
    struct ByteOrderConverter<int16_t> {

        typedef int16_t T;

        inline static T nativeToBig(T t) {
            return htobe16(static_cast<uint16_t>(t));
        }

        inline static T bigToNative(T t) {
            return be16toh(static_cast<uint16_t>(t));
        }

        inline static T nativeToLittle(T t) {
            return htole16(static_cast<uint16_t>(t));
        }

        inline static T littleToNative(T t) {
            return le16toh(static_cast<uint16_t>(t));
        }
    };

    template<>
    struct ByteOrderConverter<int32_t> {

        typedef int32_t T;

        inline static T nativeToBig(T t) {
            return htobe32(static_cast<uint32_t>(t));
        }

        inline static T bigToNative(T t) {
            return be32toh(static_cast<uint32_t>(t));
        }

        inline static T nativeToLittle(T t) {
            return htole32(static_cast<uint32_t>(t));
        }

        inline static T littleToNative(T t) {
            return le32toh(static_cast<uint32_t>(t));
        }
    };

    template<>
    struct ByteOrderConverter<int64_t> {

        typedef int64_t T;

        inline static T nativeToBig(T t) {
            return htobe64(static_cast<uint64_t>(t));
        }

        inline static T bigToNative(T t) {
            return be64toh(static_cast<uint64_t>(t));
        }

        inline static T nativeToLittle(T t) {
            return htole64(static_cast<uint64_t>(t));
        }

        inline static T littleToNative(T t) {
            return le64toh(static_cast<uint64_t>(t));
        }
    };

    template<>
    struct ByteOrderConverter<float> {

        typedef float T;

        inline static T nativeToBig(T t) {
            BOOST_STATIC_ASSERT(sizeof(T) == sizeof(uint32_t));

            uint32_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = htobe32(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T bigToNative(T t) {
            uint32_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = be32toh(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T nativeToLittle(T t) {
            uint32_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = htole32(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T littleToNative(T t) {
            uint32_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = le32toh(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }
    };

    template<>
    struct ByteOrderConverter<double> {

        typedef double T;

        inline static T nativeToBig(T t) {
            BOOST_STATIC_ASSERT(sizeof(T) == sizeof(uint64_t));

            uint64_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = htobe64(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T bigToNative(T t) {
            uint64_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = be64toh(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T nativeToLittle(T t) {
            uint64_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = htole64(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }

        inline static T littleToNative(T t) {
            uint64_t temp;
            std::memcpy(&temp, &t, sizeof(t));
            temp = le64toh(temp);
            std::memcpy(&t, &temp, sizeof(t));
            return t;
        }
    };

    template<typename T>
    inline T nativeToBig(T t) {
        return ByteOrderConverter<T>::nativeToBig(t);
    }

    template<typename T>
    inline T bigToNative(T t) {
        return ByteOrderConverter<T>::bigToNative(t);
    }

    template<typename T>
    inline T nativeToLittle(T t) {
        return ByteOrderConverter<T>::nativeToLittle(t);
    }

    template<typename T>
    inline T littleToNative(T t) {
        return ByteOrderConverter<T>::littleToNative(t);
    }

} // namespace mongo

#undef MONGO_UINT16_SWAB
#undef MONGO_UINT32_SWAB
#undef MONGO_UINT64_SWAB
#undef MONGO_LITTLE_ENDIAN
#undef MONGO_BIG_ENDIAN
#undef htobe16
#undef htobe32
#undef htobe64
#undef htole16
#undef htole32
#undef htole64
#undef be16toh
#undef be32toh
#undef be64toh
#undef le16toh
#undef le32toh
#undef le64toh

#pragma pop_macro("MONGO_UINT16_SWAB")
#pragma pop_macro("MONGO_UINT32_SWAB")
#pragma pop_macro("MONGO_UINT64_SWAB")
#pragma pop_macro("MONGO_LITTLE_ENDIAN")
#pragma pop_macro("MONGO_BIG_ENDIAN")
#pragma pop_macro("htobe16")
#pragma pop_macro("htobe32")
#pragma pop_macro("htobe64")
#pragma pop_macro("htole16")
#pragma pop_macro("htole32")
#pragma pop_macro("htole64")
#pragma pop_macro("be16toh")
#pragma pop_macro("be32toh")
#pragma pop_macro("be64toh")
#pragma pop_macro("le16toh")
#pragma pop_macro("le32toh")
#pragma pop_macro("le64toh")
