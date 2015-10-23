#pragma once

#include "AssetModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenAssetModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .beginClass<Drawable>("Drawable")
                .addProperty("x", &Drawable::GetPositionX, &Drawable::SetPositionX)
                .addProperty("y", &Drawable::GetPositionY, &Drawable::SetPositionY)
                .addProperty("scaleX", &Drawable::GetScaleX, &Drawable::SetScaleX)
                .addProperty("scaleY", &Drawable::GetScaleY, &Drawable::SetScaleY)
                .addProperty("visible", &Drawable::IsVisilble, &Drawable::SetVisible)
                .addProperty("rotation", &Drawable::GetRotation, &Drawable::SetRotation)
            .endClass()
            .beginClass<Texture>("Texture")
                .addConstructor(LUA_SP(TexturePtr), LUA_ARGS(ResourceID))
                .addProperty("x", &Texture::GetPositionX, &Texture::SetPositionX)
                .addProperty("y", &Texture::GetPositionY, &Texture::SetPositionY)
                .addProperty("width", &Texture::GetWidth, &Texture::SetWidth)
                .addProperty("height", &Texture::GetHeight, &Texture::SetHeight)
            .endClass()
            .beginExtendClass<Image, Drawable>("Image")
                .addConstructor(LUA_SP(ImagePtr), LUA_ARGS(_opt<TexturePtr>))
                .addProperty("width", &Image::GetWidth, &Image::SetWidth)
                .addProperty("height", &Image::GetHeight, &Image::SetHeight)
                .addProperty("texture", &Image::GetTexture, &Image::SetTexture)
                .addFunction("Draw", &Image::Draw)
            .endClass()
            .beginClass<TextureLoader>("TextureLoader")
                .addStaticFunction("LoadFromData", &TextureLoader::LoadFromData)
                .addStaticFunction("LoadFromLocation", &TextureLoader::LoadFromLocation)
            .endClass()
        .endModule();
    }
}