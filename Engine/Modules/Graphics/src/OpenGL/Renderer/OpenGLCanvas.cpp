#include "OpenGLCanvas.h"
#include "OpenGLRenderer.h"

#include <WindowModule.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

namespace SamEngine
{
    void OpenGLCanvas::Initialize()
    {
        s_assert(!Available());
        mContext.reset(nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES), nvgDeleteGL3);
    }

    void OpenGLCanvas::Finalize()
    {
        s_assert(Available());
    }

    bool OpenGLCanvas::Available()
    {
        return mContext != nullptr;
    }

    void OpenGLCanvas::BeginFrame()
    {
        s_assert(Available());
        OpenGLRenderer::Get().Reset();
        auto config = GetWindow().GetConfig();
        auto ratio = static_cast<float32>(config.Width) / static_cast<float32>(config.Height);
        nvgBeginFrame(mContext.get(), config.Width, config.Height, ratio);
    }

    void OpenGLCanvas::EndFrame()
    {
        s_assert(Available());
        nvgEndFrame(mContext.get());
    }

    void OpenGLCanvas::Arc(float32 cx, float32 cy, float32 r, float32 a0, float32 a1, int32 dir)
    {
        s_assert(Available());
        nvgArc(mContext.get(), cx, cy, r, a0, a1, dir);
    }

    void OpenGLCanvas::ArcTo(float32 x1, float32 y1, float32 x2, float32 y2, float32 radius)
    {
        s_assert(Available());
        nvgArcTo(mContext.get(), x1, y1, x2, y2, radius);
    }

    void OpenGLCanvas::BeginPath()
    {
        s_assert(Available());
        nvgBeginPath(mContext.get());
    }

    void OpenGLCanvas::BezierCurveTo(float32 c1x, float32 c1y, float32 c2x, float32 c2y, float32 x, float32 y)
    {
        s_assert(Available());
        nvgBezierTo(mContext.get(), c1x, c1y, c2x, c2y, x, y);
    }

    void OpenGLCanvas::ClearRect(float32 x, float32 y, float32 w, float32 h)
    {
        s_assert(Available());
        nvgBeginPath(mContext.get());
        nvgRect(mContext.get(), x, y, w, h);
        nvgClosePath(mContext.get());
        nvgFill(mContext.get());
    }

    void OpenGLCanvas::Clip()
    {
        s_assert(Available());
        // TODO
    }

    void OpenGLCanvas::ClosePath()
    {
        s_assert(Available());
        nvgClosePath(mContext.get());
    }

    CanvasGradient OpenGLCanvas::CreateLinearGradient(float32 xStart, float32 yStart, float32 xEnd, float32 yEnd)
    {
        return { CanvasGradientType::LINEAR, xStart, yStart, 0.0f, xEnd, yEnd, 0.0f };
    }

    CanvasGradient OpenGLCanvas::CreateRadialGradient(float32 xStart, float32 yStart, float32 radiusStart, float32 xEnd, float32 yEnd, float32 radiusEnd)
    {
        return { CanvasGradientType::RADIAL, xStart, yStart, radiusStart, xEnd, yEnd, radiusEnd };
    }

    void OpenGLCanvas::Fill()
    {
        s_assert(Available());
        nvgFill(mContext.get());
    }

    void OpenGLCanvas::FillRect(float32 x, float32 y, float32 w, float32 h)
    {
        s_assert(Available());
        nvgBeginPath(mContext.get());
        nvgRect(mContext.get(), x, y, w, h);
        nvgClosePath(mContext.get());
        nvgFill(mContext.get());
    }

    void OpenGLCanvas::LineTo(float32 x, float32 y)
    {
        s_assert(Available());
        nvgLineTo(mContext.get(), x, y);
    }

    void OpenGLCanvas::MoveTo(float32 x, float32 y)
    {
        s_assert(Available());
        nvgMoveTo(mContext.get(), x, y);
    }

    void OpenGLCanvas::QuadraticCurveTo(float32 cpX, float32 cpY, float32 x, float32 y)
    {
        s_assert(Available());
        nvgQuadTo(mContext.get(), cpX, cpY, x, y);
    }

    void OpenGLCanvas::Rect(float32 x, float32 y, float32 w, float32 h)
    {
        s_assert(Available());
        nvgRect(mContext.get(), x, y, w, h);
    }

    void OpenGLCanvas::Restore()
    {
        s_assert(Available());
        nvgRestore(mContext.get());
    }

    void OpenGLCanvas::Rotate(float32 angle)
    {
        s_assert(Available());
        nvgRotate(mContext.get(), angle);
    }

    void OpenGLCanvas::Save()
    {
        s_assert(Available());
        nvgSave(mContext.get());
    }

    void OpenGLCanvas::Scale(float32 sx, float32 sy)
    {
        s_assert(Available());
        nvgScale(mContext.get(), sx, sy);
    }

    void OpenGLCanvas::Stroke()
    {
        s_assert(Available());
        nvgStroke(mContext.get());
    }

    void OpenGLCanvas::StrokeRect(float32 x, float32 y, float32 w, float32 h)
    {
        s_assert(Available());
        nvgBeginPath(mContext.get());
        nvgRect(mContext.get(), x, y, w, h);
        nvgClosePath(mContext.get());
        nvgStroke(mContext.get());
    }

    void OpenGLCanvas::Translate(float32 dx, float32 dy)
    {
        s_assert(Available());
        nvgTranslate(mContext.get(), dx, dy);
    }

    void OpenGLCanvas::Transform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f)
    {
        s_assert(Available());
        nvgTransform(mContext.get(), a, b, c, d, e, f);
    }

    void OpenGLCanvas::SetTransform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f)
    {
        s_assert(Available());
        nvgResetTransform(mContext.get());
        nvgTransform(mContext.get(), a, b, c, d, e, f);
    }

    CanvasFillStyleType OpenGLCanvas::GetFillStyleType() const
    {
        return mFillStyleType;
    }

    IntColor OpenGLCanvas::GetColorFillStyle() const
    {
        return mColorFillStyle;
    }

    void OpenGLCanvas::SetColorFillStyle(IntColor value)
    {
        s_assert(Available());
        mFillStyleType = CanvasFillStyleType::COLOR;
        mColorFillStyle = value;
        nvgFillColor(mContext.get(), nvgRGB(static_cast<uint8>(value.r), static_cast<uint8>(value.g), static_cast<uint8>(value.b)));
    }

    CanvasGradient OpenGLCanvas::GetGradientFillStyle() const
    {
        return mGradientFillStyle;
    }

    void OpenGLCanvas::SetGradientFillStyle(CanvasGradient value)
    {
        s_assert(Available());
        mFillStyleType = CanvasFillStyleType::GRADIENT;
        mGradientFillStyle = value;
        NVGpaint paint;
        NVGcolor inColor = nvgRGB(static_cast<uint8>(value.StartColor.r), static_cast<uint8>(value.StartColor.g), static_cast<uint8>(value.StartColor.b));
        NVGcolor outColor = nvgRGB(static_cast<uint8>(value.EndColor.r), static_cast<uint8>(value.EndColor.g), static_cast<uint8>(value.EndColor.b));
        if (value.Type == CanvasGradientType::LINEAR)
        {
            paint = nvgLinearGradient(mContext.get(), value.StartX, value.StartY, value.EndX, value.EndY, inColor, outColor);
        }
        else if (value.Type == CanvasGradientType::RADIAL)
        {
//            paint = nvgRadialGradient(mContext.get(), )
        }
        nvgFillPaint(mContext.get(), paint);
    }

    float32 OpenGLCanvas::GetGlobalAlpha() const
    {
        return mGlobalAlpha;
    }

    void OpenGLCanvas::SetGlobalAlpha(float32 value)
    {
        s_assert(Available());
        mGlobalAlpha = value;
        nvgGlobalAlpha(mContext.get(), value);
    }

    CanvasCompositeType OpenGLCanvas::GetGlobalCompositeOperation() const
    {
        return mGlobalCompositeOperation;
    }

    void OpenGLCanvas::SetGlobalCompositeOperation(CanvasCompositeType value)
    {
        s_assert(Available());
        mGlobalCompositeOperation = value;
        // TODO
    }

    CanvasLineCapType OpenGLCanvas::GetLineCap() const
    {
        return mLineCap;
    }

    void OpenGLCanvas::SetLineCap(CanvasLineCapType value)
    {
        s_assert(Available());
        mLineCap = value;
        if (value == CanvasLineCapType::BUTT)
        {
            nvgLineCap(mContext.get(), NVG_BUTT);
        }
        else if (value == CanvasLineCapType::ROUND)
        {
            nvgLineCap(mContext.get(), NVG_ROUND);
        }
        else if (value == CanvasLineCapType::SQUARE)
        {
            nvgLineCap(mContext.get(), NVG_SQUARE);
        }
    }

    CanvasLineJoinType OpenGLCanvas::GetLineJoin() const
    {
        return mLineJoin;
    }

    void OpenGLCanvas::SetLineJoin(CanvasLineJoinType value)
    {
        s_assert(Available());
        mLineJoin = value;
        if (value == CanvasLineJoinType::ROUND)
        {
            nvgLineJoin(mContext.get(), NVG_ROUND);
        }
        else if (value == CanvasLineJoinType::MITER)
        {
            nvgLineJoin(mContext.get(), NVG_MITER);
        }
        else if (value == CanvasLineJoinType::BEVEL)
        {
            nvgLineJoin(mContext.get(), NVG_BEVEL);
        }
    }

    float32 OpenGLCanvas::GetLineWidth() const
    {
        return mLineWidth;
    }

    void OpenGLCanvas::SetLineWidth(float32 value)
    {
        s_assert(Available());
        mLineWidth = value;
        // TODO
    }

    float32 OpenGLCanvas::GetMiterLimit() const
    {
        return mMiterLimit;
    }

    void OpenGLCanvas::SetMiterLimit(float32 value)
    {
        s_assert(Available());
        mMiterLimit = value;
        nvgMiterLimit(mContext.get(), value);
    }

    CanvasStrokeStyleType OpenGLCanvas::GetStrokeStyleType() const
    {
        return mStrokeStyleType;
    }

    IntColor OpenGLCanvas::GetColorStrokeStyle() const
    {
        return mColorFillStyle;
    }

    void OpenGLCanvas::SetColorStrokeStyle(IntColor value)
    {
        s_assert(Available());
        mStrokeStyleType = CanvasStrokeStyleType::COLOR;
        mColorFillStyle = value;
        nvgStrokeColor(mContext.get(), nvgRGB(static_cast<uint8>(value.r), static_cast<uint8>(value.g), static_cast<uint8>(value.b)));
    }

    CanvasGradient OpenGLCanvas::GetGradientStrokeStyle() const
    {
        return mGradientStrokeStyle;
    }

    void OpenGLCanvas::SetGradientStrokeStyle(CanvasGradient value)
    {
        s_assert(Available());
        mStrokeStyleType = CanvasStrokeStyleType::GRADIENT;
        mGradientStrokeStyle = value;
        NVGpaint paint;
        NVGcolor inColor = nvgRGB(static_cast<uint8>(value.StartColor.r), static_cast<uint8>(value.StartColor.g), static_cast<uint8>(value.StartColor.b));
        NVGcolor outColor = nvgRGB(static_cast<uint8>(value.EndColor.r), static_cast<uint8>(value.EndColor.g), static_cast<uint8>(value.EndColor.b));
        if (value.Type == CanvasGradientType::LINEAR)
        {
            paint = nvgLinearGradient(mContext.get(), value.StartX, value.StartY, value.EndX, value.EndY, inColor, outColor);
        }
        else if (value.Type == CanvasGradientType::RADIAL)
        {
//            paint = nvgRadialGradient(mContext.get(), )
        }
        nvgStrokePaint(mContext.get(), paint);
    }
}