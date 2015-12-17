#pragma once

#include "Renderer/ICanvas.h"

#include <glad/glad.h>
#include <nanovg.h>

namespace SamEngine
{
    class OpenGLCanvas : public ICanvas
    {
    public:
        virtual void Initialize() override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual void BeginFrame() override;

        virtual void EndFrame() override;

        virtual void Arc(float32 cx, float32 cy, float32 r, float32 a0, float32 a1, int32 dir) override;

        virtual void ArcTo(float32 x1, float32 y1, float32 x2, float32 y2, float32 radius) override;

        virtual void BeginPath() override;

        virtual void BezierCurveTo(float32 c1x, float32 c1y, float32 c2x, float32 c2y, float32 x, float32 y) override;

        virtual void ClearRect(float32 x, float32 y, float32 w, float32 h) override;

        virtual void Clip() override;

        virtual void ClosePath() override;

        virtual CanvasGradient CreateLinearGradient(float32 xStart, float32 yStart, float32 xEnd, float32 yEnd) override;

        virtual CanvasGradient CreateRadialGradient(float32 xStart, float32 yStart, float32 radiusStart, float32 xEnd, float32 yEnd, float32 radiusEnd) override;

        virtual void Fill() override;

        virtual void FillRect(float32 x, float32 y, float32 w, float32 h) override;

        virtual void LineTo(float32 x, float32 y) override;

        virtual void MoveTo(float32 x, float32 y) override;

        virtual void QuadraticCurveTo(float32 cpX, float32 cpY, float32 x, float32 y) override;

        virtual void Rect(float32 x, float32 y, float32 w, float32 h) override;

        virtual void Restore() override;

        virtual void Rotate(float32 angle) override;

        virtual void Save() override;

        virtual void Scale(float32 sx, float32 sy) override;

        virtual void Stroke() override;

        virtual void StrokeRect(float32 x, float32 y, float32 w, float32 h) override;

        virtual void Translate(float32 dx, float32 dy) override;

        virtual void Transform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f) override;

        virtual void SetTransform(float32 a, float32 b, float32 c, float32 d, float32 e, float32 f) override;

        virtual CanvasFillStyleType GetFillStyleType() const override;

        virtual IntColor GetColorFillStyle() const override;

        virtual void SetColorFillStyle(IntColor value) override;

        virtual CanvasGradient GetGradientFillStyle() const override;

        virtual void SetGradientFillStyle(CanvasGradient value) override;

        virtual float32 GetGlobalAlpha() const override;

        virtual void SetGlobalAlpha(float32 value) override;

        virtual CanvasCompositeType GetGlobalCompositeOperation() const override;

        virtual void SetGlobalCompositeOperation(CanvasCompositeType value) override;

        virtual CanvasLineCapType GetLineCap() const override;

        virtual void SetLineCap(CanvasLineCapType value) override;

        virtual CanvasLineJoinType GetLineJoin() const override;

        virtual void SetLineJoin(CanvasLineJoinType value) override;

        virtual float32 GetLineWidth() const override;

        virtual void SetLineWidth(float32 value) override;

        virtual float32 GetMiterLimit() const override;

        virtual void SetMiterLimit(float32 value) override;

        virtual CanvasStrokeStyleType GetStrokeStyleType() const override;

        virtual IntColor GetColorStrokeStyle() const override;

        virtual void SetColorStrokeStyle(IntColor value) override;

        virtual CanvasGradient GetGradientStrokeStyle() const override;

        virtual void SetGradientStrokeStyle(CanvasGradient value) override;

    private:
        std::shared_ptr<NVGcontext> mContext{ nullptr };
        CanvasFillStyleType mFillStyleType{ CanvasFillStyleType::COLOR };
        IntColor mColorFillStyle;
        CanvasGradient mGradientFillStyle;
        float32 mGlobalAlpha{ 1.0f };
        CanvasCompositeType mGlobalCompositeOperation{ CanvasCompositeType::SOURCE_OVER };
        CanvasLineCapType mLineCap{ CanvasLineCapType::BUTT };
        CanvasLineJoinType mLineJoin{ CanvasLineJoinType::MITER };
        float32 mLineWidth{ 1.0f };
        float32 mMiterLimit{ 10.0f };
        CanvasStrokeStyleType mStrokeStyleType{ CanvasStrokeStyleType::COLOR };
        IntColor mColorStrokeStyle;
        CanvasGradient mGradientStrokeStyle;
    };
}