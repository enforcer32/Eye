#pragma once

// Platform Detection
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
	#ifndef _WIN64
		#error "64-Bit Windows Required!"
	#else
		#define EYE_PLATFORM_WINDOWS 1 // Windows
	#endif
#elif defined(__linux__)
	#define EYE_PLATFORM_LINUX 1 // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
	#include <sys/param.h>
	#if defined(BSD)
		#define EYE_PLATFORM_BSD 1 // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
	#endif
#elif defined(__ANDROID__)
	#define EYE_PLATFORM_ANDROID 1 // Android
#elif defined(__hpux)
	#define EYE_PLATFORM_HPUX 1 // HP-UX
#elif defined(_AIX)
	#define EYE_PLATFORM_AIX 1 // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define EYE_PLATFORM_IOS_SIMULATOR 1 // Apple iOS Simulator
	#elif TARGET_OS_IPHONE == 1
		#define EYE_PLATFORM_IOS 1 // Apple iOS
	#elif TARGET_OS_MAC == 1
		#define EYE_PLATFORM_OSX 1 // Apple OSX
	#endif
#elif defined(__sun) && defined(__SVR4)
	#define EYE_PLATFORM_SOLARIS 1 // Oracle Solaris, Open Indiana
#else
	#error "Unsupported Platform"
#endif
