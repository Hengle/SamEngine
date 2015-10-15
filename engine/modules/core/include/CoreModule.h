#pragma once

#ifndef CORE_API
#    if SAM_WINDOWS
#        define CORE_API __declspec(dllimport)
#    else
#        define CORE_API
#    endif
#endif

#include "Class.h"
#include "Data.h"
#include "ILog.h"
#include "IThread.h"
#include "ITicker.h"
#include "RWLock.h"
#include "Types.h"