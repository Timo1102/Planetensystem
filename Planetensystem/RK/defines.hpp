#ifndef _RK_DEFINES_HPP_
#define _RK_DEFINES_HPP_

#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN32__)) && !defined(RK_SYSTEM_WINDOWS)
#define RK_SYSTEM_WINDOWS
#define RK_NAMESPACE_SYSTEM Windows
#elif defined(__linux__) && !defined(RK_SYSTEM_LINUX)
#define RK_SYSTEM_LINUX
#define RK_NAMESPACE_SYSTEM Linux
#elif defined(TARGET_OS_MAC) && !defined(RK_SYSTEM_MAC)
#define RK_SYSTEM_MAC
#define RK_NAMESPACE_SYSTEM Mac
#elif (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)) && !defined(RK_SYSTEM_IPHONE)
#define RK_SYSTEM_IPHONE
#define RK_NAMESPACE_SYSTEM Iphone
#else
#error Unrecognized system
#endif

#if !defined(RK_NAMESPACE_SYSTEM)
#error Unrecognized system namespace
#endif

#if defined(__GNUC__) && !defined(RK_COMPILER_GCC)
#define RK_COMPILER_GCC
#elif defined(_MSC_VER) && !defined(RK_COMPILER_MSC)
#define RK_COMPILER_MSC
#else
#error Unrecognized compiler
#endif

#if (defined(_M_X64) || defined(__amd64__)) && !defined(RK_CPU_X64)
#define RK_CPU_X64
#elif (defined(_M_IX86) || defined(__i386__)) && !defined(RK_CPU_X86)
#define RK_CPU_X86
#else
#error Unrecognized CPU
#endif

#if !defined(RK_EXPORT)
#if defined(RK_COMPILER_MSC)
#define RK_EXPORT __declspec(dllexport)
#elif defined(RK_COMPILER_GCC) && defined(RK_SYSTEM_WINDOWS)
#define RK_EXPORT __attribute__((dllexport))
#elif defined(RK_COMPILER_GCC)
#define RK_EXPORT
#endif
#endif

#if !defined(RK_IMPORT)
#if defined(RK_COMPILER_MSC)
#define RK_IMPORT __declspec(dllimport)
#elif defined(RK_COMPILER_GCC) && defined(RK_SYSTEM_WINDOWS)
#define RK_IMPORT __attribute__((dllimport))
#elif defined(RK_COMPILER_GCC)
#define RK_IMPORT
#endif
#endif

#if !defined(RK_LIBRARY)
#if defined(_WINDLL) || defined(DLL_EXPORT)
#define RK_LIBRARY RK_EXPORT
#else
#define RK_LIBRARY RK_IMPORT
#endif
#endif

#if defined(_DEBUG)
#define RK_DEBUG
#endif

#endif
