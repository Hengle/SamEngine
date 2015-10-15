#pragma once

#ifndef RESOURCE_API
#    if SAM_WINDOWS
#        define RESOURCE_API __declspec(dllimport)
#    else
#        define RESOURCE_API
#    endif
#endif

#include "Resource.h"
#include "ResourceFactory.h"
#include "ResourceManager.h"
#include "ResourceName.h"
#include "ResourcePool.h"
#include "ResourceRegistry.h"