#pragma once

#include "GraphicsDefine.h"

#include <CoreModule.h>

struct NVGcontext;

namespace SamEngine
{
    enum class CanvasFillStyleType
    {
        COLOR,
        GRADIENT,
    };

    enum class CanvasCompositeType
    {
        COPY,
        DARKER,
        DESTINATION_ATOP,
        DESTINATION_IN,
        DESTINATION_OUT,
        DESTINATION_OVER,
        LIGHTER,
        SOURCE_ATOP,
        SOURCE_IN,
        SOURCE_OUT,
        SOURCE_OVER,
        XOR,
    };

    enum class CanvasLineCapType
    {
        BUTT,
        ROUND,
        SQUARE,
    };

    enum class CanvasLineJoinType
    {
        ROUND,
        BEVEL,
        MITER,
    };

    enum class CanvasStrokeStyleType
    {
        COLOR,
        GRADIENT,
    };

    enum class CanvasGradientType
    {
        LINEAR,
        RADIAL,
    };

    struct GRAPHICS_API CanvasGradient
    {
        CanvasGradientType Type{ CanvasGradientType::LINEAR };
        float32 StartX{ 0.0f };
        float32 StartY{ 0.0f };
        float32 StartRadius{ 0.0f };
        float32 EndX{ 0.0f };
        float32 EndY{ 0.0f };
        float32 EndRadius{ 0.0f };
        IntColor StartColor;
        IntColor EndColor;

        CanvasGradient() {}

        CanvasGradient(CanvasGradientType type, float32 xStart, float32 yStart, float32 radiusStart, float32 xEnd, float32 yEnd, float32 radiusEnd) :
            Type(type),
            StartX(xStart),
            StartY(yStart),
            StartRadius(radiusStart),
            EndX(xEnd),
            EndY(yEnd),
            EndRadius(radiusEnd) {}

        void AddColorStop(float32 offset, IntColor color)
        {
            if (offset == 0)
            {
                StartColor = color;
            }
            else if (offset == 1)
            {
                EndColor = color;
            }
        }
    };

    class GRAPHICS_API ICanvas
    {
    public:
        virtual ~ICanvas() {}

        virtual void Initialize() = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual void Arc(float32 cx, float32 cy, float32 r, float32 a0, float32 a1, int32 dir) = 0;

        virtual void ArcTo(float32 x1, float32 y1, float32 x2, float32 y2, float32 radius) = 0;

        virtual void BeginPath() = 0;

        virtual void BezierCurveTo(float32 c1x, float32 c1y, float32 c2x, float32 c2y, float32 x, float32 y) = 0;

        virtual void ClearRect(float32 x, float32 y, float32 w, float32 h) = 0;

        virtual void Clip() = 0;

        virtual void ClosePath() = 0;

        virtual CanvasGradient CreateLinearGradient(float32 xStart, float32 yStart, float32 xEnd, float32 yEnd) = 0;

        virtual CanvasGradient CreateRadialGradient(float32 xStart, float32 yStart, float32 radiusStart, float32 xEnd, float32 yEnd, float32 radiusEnd) = 0;

        virtual void Fill() = 0;

        virtual void FillRect(float32 x, float32 y, float32 w, float32 h) = 0;

        virtual void LineTo(float32 x, float32 y) = 0;

        virtual void MoveTo(float32 x, float32 y) = 0;

        virtual void QuadraticCurveTo(float32 cpX, float32 cpY, float32 x, float32 y) = 0;

        virtual void Rect(float32 x, float32 y, float32 w, float32 h) = 0;

        virtual void Restore() = 0;

        virtual void Rotate(float32 angle) = 0;

        virtual void Save() = 0;

        virtual void Scale(float32 sx, float32 sy) = 0;

        virtual void Stroke() = 0;

        virtual void StrokeRect(float32 x, float32 y, float32 w, float32 h) = 0;

        virtual void Translate(float32 dx, float32 dy) = 0;

        virtual void Transform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f) = 0;

        virtual void SetTransform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f) = 0;

        virtual CanvasFillStyleType GetFillStyleType() const = 0;

        virtual IntColor GetColorFillStyle() const = 0;

        virtual void SetColorFillStyle(IntColor value) = 0;

        virtual CanvasGradient GetGradientFillStyle() const = 0;

        virtual void SetGradientFillStyle(CanvasGradient value) = 0;

        virtual float32 GetGlobalAlpha() const = 0;

        virtual void SetGlobalAlpha(float32 value) = 0;

        virtual CanvasCompositeType GetGlobalCompositeOperation() const = 0;

        virtual void SetGlobalCompositeOperation(CanvasCompositeType value) = 0;

        virtual CanvasLineCapType GetLineCap() const = 0;

        virtual void SetLineCap(CanvasLineCapType value) = 0;

        virtual CanvasLineJoinType GetLineJoin() const = 0;

        virtual void SetLineJoin(CanvasLineJoinType value) = 0;

        virtual float32 GetLineWidth() const = 0;

        virtual void SetLineWidth(float32 value) = 0;

        virtual float32 GetMiterLimit() const = 0;

        virtual void SetMiterLimit(float32 value) = 0;

        virtual CanvasStrokeStyleType GetStrokeStyleType() const = 0;

        virtual IntColor GetColorStrokeStyle() const = 0;

        virtual void SetColorStrokeStyle(IntColor value) = 0;

        virtual CanvasGradient GetGradientStrokeStyle() const = 0;

        virtual void SetGradientStrokeStyle(CanvasGradient value) = 0;
    };
}