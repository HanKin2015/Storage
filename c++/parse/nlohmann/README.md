# nlohmann json

## 1、简介
好用，只需要一个hpp头文件即可使用。
缺点：老项目无法使用最新版版本的hpp头文件，需要使用老版本的，如2.1.1版本

```json.hpp
// C++ language standard detection
// if the user manually specified the used c++ version this is skipped
#if !defined(JSON_HAS_CPP_20) && !defined(JSON_HAS_CPP_17) && !defined(JSON_HAS_CPP_14) && !defined(JSON_HAS_CPP_11)
    #if (defined(__cplusplus) && __cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
        #define JSON_HAS_CPP_20
        #define JSON_HAS_CPP_17
        #define JSON_HAS_CPP_14
    #elif (defined(__cplusplus) && __cplusplus >= 201703L) || (defined(_HAS_CXX17) && _HAS_CXX17 == 1) // fix for issue #464
        #define JSON_HAS_CPP_17
        #define JSON_HAS_CPP_14
    #elif (defined(__cplusplus) && __cplusplus >= 201402L) || (defined(_HAS_CXX14) && _HAS_CXX14 == 1)
        #define JSON_HAS_CPP_14
    #endif
    // the cpp 11 flag is always specified because it is the minimal required version
    #define JSON_HAS_CPP_11
#endif
```