#pragma once

#include "event/handler.h"

#include <functional>
#include <memory>

namespace sam
{
    typedef handler filesystem;

    typedef std::shared_ptr<filesystem> filesystem_ptr;

	typedef std::function<filesystem_ptr()> filesystem_creator;
}