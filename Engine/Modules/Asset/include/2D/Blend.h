#pragma once

#include <GraphicsModule.h>

namespace SamEngine
{
    enum class BlendMode : uint8
    {
        ALPHA,
        ADD,
        SUBTRACT,
        MULTIPLY,
        PRE_MULTIPLIED,
        SCREEN,
        REPLACE,
    };

    class ASSET_API Blend
    {
    public:
        static void Apply(BlendMode mode);

        static void Alpha();

        static void Add();

        static void Subtract();

        static void Multiply();

        static void PreMultiplied();

        static void Screen();

        static void Replace();
    };

    inline void Blend::Apply(BlendMode mode)
    {
        switch (mode)
        {
        case BlendMode::ALPHA:
            Alpha();
            break;
        case BlendMode::ADD:
            Add();
            break;
        case BlendMode::SUBTRACT:
            Subtract();
            break;
        case BlendMode::MULTIPLY:
            Multiply();
            break;
        case BlendMode::PRE_MULTIPLIED:
            PreMultiplied();
            break;
        case BlendMode::SCREEN:
            Screen();
            break;
        case BlendMode::REPLACE:
            Replace();
            break;
        default:
            break;
        }
    }

    inline void Blend::Alpha()
    {
        BlendState state;
        state.Enabled = true;
        state.SrcRGBFactor = BlendFactor::SRC_ALPHA;
        state.DstRGBFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
        state.DstAlphaFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::Add()
    {
        BlendState state;
        state.Enabled = true;
        state.SrcRGBFactor = BlendFactor::SRC_ALPHA;
        state.DstRGBFactor = BlendFactor::ONE;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::Subtract()
    {
        BlendState state;
        state.Enabled = true;
        state.RGBOperation = BlendOperation::REVERSE_SUBTRACT;
        state.AlphaOperation = BlendOperation::REVERSE_SUBTRACT;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::Multiply()
    {
        BlendState state;
        state.Enabled = true;
        state.SrcRGBFactor = BlendFactor::DST_COLOR;
        state.SrcAlphaFactor = BlendFactor::DST_COLOR;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::PreMultiplied()
    {
        BlendState state;
        state.Enabled = true;
        state.DstRGBFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
        state.DstAlphaFactor = BlendFactor::ONE_MINUS_SRC_ALPHA;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::Screen()
    {
        BlendState state;
        state.Enabled = true;
        state.DstRGBFactor = BlendFactor::ONE_MINUS_SRC_COLOR;
        state.DstAlphaFactor = BlendFactor::ONE_MINUS_SRC_COLOR;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }

    inline void Blend::Replace()
    {
        BlendState state;
        state.Enabled = true;
        GetGraphics().GetRenderer().ApplyBlendState(state);
    }
}