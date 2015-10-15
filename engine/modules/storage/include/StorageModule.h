#pragma once

#ifndef STORAGE_API
#    if SAM_WINDOWS
#        define STORAGE_API __declspec(dllimport)
#    else
#        define STORAGE_API
#    endif
#endif

#include "IStorage.h"