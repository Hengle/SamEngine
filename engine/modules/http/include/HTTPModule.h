#pragma once

#ifndef HTTP_API
#    if SAM_WINDOWS
#        define HTTP_API __declspec(dllimport)
#    else
#        define HTTP_API
#    endif
#endif

#include "IHTTP.h"