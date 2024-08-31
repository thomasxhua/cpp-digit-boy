#ifndef TDEV_H
#define TDEV_H

#include <iostream>

// DEBUG LEVELS
//
// - 0: No debug information
// - 1: Show only error and prints
// - 2: Show all debug information including pauses
//
#define TDEV_DEBUG_LEVEL 2

#if TDEV_DEBUG_LEVEL == 0
    #define PRINT(x)
    #define ERROR(x)
    #define DELOG(x)
    #define DEVAR(x)
    #define PAUSE()
#elif TDEV_DEBUG_LEVEL == 1
    #define PRINT(x) std::cout<<x
    #define ERROR(x) PRINT("(ERROR) "<<x<<std::endl)
    #define DELOG(x)
    #define DEVAR(x)
    #define PAUSE()
#elif TDEV_DEBUG_LEVEL == 2
    #define PRINT(x) std::cout<<x
    #define ERROR(x) PRINT("(ERROR) "<<x<<std::endl)
    #define DELOG(x) PRINT("(DELOG) "<<x<<std::endl)
    #define DEVAR(x) DELOG(#x<<": "<<x)
    #define PAUSE()  std::cin.get()
#endif

#endif

