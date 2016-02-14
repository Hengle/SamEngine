#if SAM_ANDROID

#include "EGLInput.h"

namespace SamEngine
{
    IKeyboard &EGLInput::GetKeyboard()
    {
        return mKeyboard;
    }

    IMouse &EGLInput::GetMouse()
    {
        return mMouse;
    }
}

#endif