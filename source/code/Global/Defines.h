#if (defined(__cplusplus) && __cplusplus == 201103L) || defined(__GXX_EXPERIMENTAL_CXX0X__) || (defined(_MSC_VER) && _MSC_VER >= 1800)
#define CPP11 1 // the compiler has support for C++11
#else
#define CPP11 0 // the compiler does not have support for C++11
#endif