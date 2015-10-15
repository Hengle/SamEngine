#pragma once

#ifndef IO_API
#    if SAM_WINDOWS
#        define IO_API __declspec(dllimport)
#    else
#        define IO_API
#    endif
#endif

#include "Event/IORequestReadEvent.h"
#include "Event/IORequestWriteEvent.h"
#include "Event/IONotifyNewFilesystemEvent.h"
#include "Event/IONotifyReplaceFilesystemEvent.h"
#include "Event/IONotifyDeleteFilesystemEvent.h"
#include "Filesystem/Filesystem.h"
#include "Filesystem/Location.h"
#include "IIO.h"