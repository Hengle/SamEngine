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
                .addProperty("originX", &Drawable::GetOriginX, &Drawable::SetOriginX)
                .addProperty("originY", &Drawable::GetOriginY, &Drawable::SetOriginY)
                .addProperty("scaleX", &Drawable::GetScaleX, &Drawable::SetScaleX)
                .addProperty("scaleY", &Drawable::GetScaleY, &Drawable::SetScaleY)
                .addProperty("visible", &Drawable::IsVisilble, &Drawable::SetVisible)
                .addProperty("rotation", &Drawable::GetRotationZ, &Drawable::SetRotationZ)
            .endClass()
            .beginClass<Texture>("Texture")
                .addStaticFunction("FromLocation", [](const std::string &location)
                {
                    return Texture::Create(location);
                }, LUA_ARGS(std::string))
                .addStaticFunction("FromTexture", [](TexturePtr texture, int32 x = 0, int32 y = 0, int32 width = 0, int32 height = 0)
                {
                    return Texture::Create(texture, x, y, width, height);
                }, LUA_ARGS(TexturePtr, _opt<int32>, _opt<int32>, _opt<int32>, _opt<int32>))
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
                .addProperty("width", &Image::GetWidth, &Image::SetWidth)
                .addProperty("height", &Image::GetHeight, &Image::SetHeight)
                .addFunction("Draw", &Image::Draw)
            .endClass()
            .beginExtendClass<Spine, Drawable>("Spine")
                .addConstructor(LUA_SP(SpinePtr), LUA_ARGS(std::string, std::string))
                .addFunction("SetMixTime", &Spine::SetMixTime, LUA_ARGS(std::string, std::string, TickCount))
                .addFunction("SetAnimation", &Spine::SetAnimation, LUA_ARGS(int32, std::string, bool))
                .addFunction("AddAnimation", &Spine::AddAnimation, LUA_ARGS(int32, std::string, bool, _opt<TickCount>))
                .addFunction("GetAnimation", &Spine::GetAnimation, LUA_ARGS(_opt<int32>))
                .addFunction("Clear", &Spine::Clear, LUA_ARGS(_opt<int32>))
                .addFunction("ClearAll", &Spine::ClearAll)
                .addFunction("Update", &Spine::Update, LUA_ARGS(TickCount))
                .addFunction("Draw", &Spine::Draw)
            .endClass()
        .endModule();
    }
}