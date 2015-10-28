#pragma once

#include "AssetModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenAssetModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .beginModule("BlendMode")
                .addConstant("ALPHA", BlendMode::ALPHA)
                .addConstant("ADD", BlendMode::ADD)
                .addConstant("SUBTRACT", BlendMode::SUBTRACT)
                .addConstant("MULTIPLY", BlendMode::MULTIPLY)
                .addConstant("PRE_MULTIPLIED", BlendMode::PRE_MULTIPLIED)
                .addConstant("SCREEN", BlendMode::SCREEN)
                .addConstant("REPLACE", BlendMode::REPLACE)
            .endModule()
            .beginClass<Drawable>("Drawable")
                .addProperty("x", &Drawable::GetPositionX, &Drawable::SetPositionX)
                .addProperty("y", &Drawable::GetPositionY, &Drawable::SetPositionY)
                .addProperty("scaleX", &Drawable::GetScaleX, &Drawable::SetScaleX)
                .addProperty("scaleY", &Drawable::GetScaleY, &Drawable::SetScaleY)
                .addProperty("visible", &Drawable::IsVisilble, &Drawable::SetVisible)
                .addProperty("rotation", &Drawable::GetRotationZ, &Drawable::SetRotationZ)
            .endClass()
            .beginClass<Texture>("Texture")
                .addConstructor(LUA_SP(TexturePtr), LUA_ARGS(ResourceID, _opt<int32>, _opt<int32>, _opt<int32>, _opt<int32>))
                .addProperty("x", &Texture::GetPositionX, &Texture::SetPositionX)
                .addProperty("y", &Texture::GetPositionY, &Texture::SetPositionY)
                .addProperty("width", &Texture::GetWidth, &Texture::SetWidth)
                .addProperty("height", &Texture::GetHeight, &Texture::SetHeight)
                .addProperty("pixelWidth", &Texture::GetPixelWidth)
                .addProperty("pixelHeight", &Texture::GetPixelHeight)
                .addProperty("normalizedLeft", &Texture::GetNormalizedLeft)
                .addProperty("normalizedRight", &Texture::GetNormalizedRight)
                .addProperty("normalizedTop", &Texture::GetNormalizedTop)
                .addProperty("normalizedBottom", &Texture::GetNormalizedBottom)
            .endClass()
            .beginExtendClass<Image, Drawable>("Image")
                .addConstructor(LUA_SP(ImagePtr), LUA_ARGS(_opt<TexturePtr>))
                .addProperty("texture", &Image::GetTexture, &Image::SetTexture)
                .addProperty("blend", &Image::GetBlendMode, &Image::SetBlendMode)
                .addFunction("Draw", &Image::Draw)
            .endClass()
            .beginClass<TextureLoader>("TextureLoader")
                .addStaticFunction("LoadFromData", &TextureLoader::LoadFromData)
                .addStaticFunction("LoadFromLocation", &TextureLoader::LoadFromLocation)
            .endClass()
        .endModule();
    }
}