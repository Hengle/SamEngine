#pragma once

#ifndef EVENT_API
#    if SAM_WINDOWS
#        define EVENT_API __declspec(dllimport)
#    else
#        define EVENT_API
#    endif
#endif

#include "AsyncEventHandler.h"
#include "EventDispatcher.h"
#include "Event.h"
#include "IEventHandler.h"
#include "ThreadAsyncEventHandler.h"