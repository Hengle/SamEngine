#pragma once

#include "event/handler.h"

#include <functional>
#include <memory>

namespace sam
{
	class filesystem;

	typedef std::shared_ptr<filesystem> filesystem_ptr;

    class filesystem : public handler
    {
	public:
		typedef std::function<filesystem_ptr()> creator;
    };
}