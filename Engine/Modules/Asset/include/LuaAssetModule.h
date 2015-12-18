#pragma once

#include "AssetModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenAssetLuaModule(LuaState state)
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
                .addStaticFunction("FromLocation", [](const std::string &location, bool antiAlias = true, DataPtr data = nullptr)
                {
                    return Texture::Create(location, antiAlias, data);
                }, LUA_ARGS(std::string, _opt<bool>, _opt<DataPtr>))
                .addStaticFunction("FromTexture", [](TexturePtr texture, float32 regionX, float32 regionY, float32 regionWidth, float32 regionHeight,
                    bool rotate = false, float32 offsetX = 0.0f, float32 offsetY = 0.0f, float32 frameWidth = 0.0f, float32 frameHeight = 0.0f)
                {
                    return Texture::Create(texture, regionX, regionY, regionWidth, regionHeight, rotate, offsetX, offsetY, frameWidth, frameHeight);
                }, LUA_ARGS(TexturePtr, float32, float32, float32, float32, _opt<bool>, _opt<float32>, _opt<float32>, _opt<float32>, _opt<float32>))
                .addProperty("width", &Texture::GetWidth)
                .addProperty("height", &Texture::GetHeight)
                .addProperty("pixelWidth", &Texture::GetPixelWidth)
                .addProperty("pixelHeight", &Texture::GetPixelHeight)
                .addProperty("isAntiAlias", &Texture::IsAntiAlias)
                .addProperty("isPreMultipliedAlpha", &Texture::IsPreMultipliedAlpha)
                .addProperty("mipmapCount", &Texture::GetMipmapCount)
                .addProperty("offsetX", &Texture::GetOffsetX)
                .addProperty("offsetY", &Texture::GetOffsetY)
                .addProperty("frameWidth", &Texture::GetFrameWidth)
                .addProperty("frameHeight", &Texture::GetFrameHeight)
            .endClass()
            .beginExtendClass<Image, Drawable>("Image")
                .addConstructor(LUA_SP(ImagePtr), LUA_ARGS(_opt<TexturePtr>))
                .addProperty("texture", &Image::GetTexture, &Image::SetTexture)
                .addProperty("blend", &Image::GetBlendMode, &Image::SetBlendMode)
                .addProperty("width", &Image::GetWidth, &Image::SetWidth)
                .addProperty("height", &Image::GetHeight, &Image::SetHeight)
                .addFunction("Draw", &Image::Draw)
            .endClass()
            .beginClass<SpineAtlas>("SpineAtlas")
                .addConstructor(LUA_SP(SpineAtlasPtr), LUA_ARGS(std::string))
            .endClass()
            .beginClass<SpineSkeletonData>("SpineSkeletonData")
                .addConstructor(LUA_SP(SpineSkeletonDataPtr), LUA_ARGS(std::string, SpineAtlasPtr))
            .endClass()
            .beginExtendClass<Spine, Drawable>("Spine")
                .addConstructor(LUA_SP(SpinePtr), LUA_ARGS(SpineSkeletonDataPtr))
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