#pragma once

#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/SaberTrail.hpp"
#include "GlobalNamespace/TubeBloomPrePassLight.hpp"
#include "GlobalNamespace/SetSaberGlowColor.hpp"
#include "GlobalNamespace/SetSaberGlowColor_PropertyTintColorPair.hpp"
#include "GlobalNamespace/SetSaberFakeGlowColor.hpp"
#include "GlobalNamespace/Parametric3SliceSpriteController.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/MaterialPropertyBlock.hpp"

namespace SaberUtil {
    static UnityEngine::Color GetColor(GlobalNamespace::SaberModelController* saberModelController) {
        return saberModelController->saberTrail->color;
    }

    static UnityEngine::Color ColorWithAlpha(UnityEngine::Color color, float alpha) {
        color.a = alpha;
        return color;
    }

    static void SetColors(GlobalNamespace::SetSaberFakeGlowColor* setSaberFakeGlowColor, UnityEngine::Color color) {
            auto parametricSpriteController = setSaberFakeGlowColor->parametric3SliceSprite;
            auto tint = setSaberFakeGlowColor->tintColor;
            parametricSpriteController->color = color * tint;
            parametricSpriteController->Refresh();
    }
    
    static void SetColors(GlobalNamespace::SetSaberGlowColor* setSaberGlowColor, UnityEngine::Color color) {
            auto meshRenderer = setSaberGlowColor->meshRenderer;
            auto materialPropertyBlock = setSaberGlowColor->materialPropertyBlock;
            auto propertyTintPairs = setSaberGlowColor->propertyTintColorPairs;
        
            if (!materialPropertyBlock || !materialPropertyBlock->m_Ptr.m_value) {
                materialPropertyBlock = UnityEngine::MaterialPropertyBlock::New_ctor();
                setSaberGlowColor->materialPropertyBlock = materialPropertyBlock;
            }

            for (auto tintPair : propertyTintPairs)
                materialPropertyBlock->SetColor(tintPair->property, color * tintPair->tintColor);

            meshRenderer->SetPropertyBlock(materialPropertyBlock);
    }

    static void SetColor(GlobalNamespace::SaberModelController* saberModelController, UnityEngine::Color color) {
        auto trail = saberModelController->saberTrail;

        auto light = saberModelController->saberLight;
        auto glowColors = saberModelController->setSaberGlowColors;
        auto fakeGlowColors = saberModelController->setSaberFakeGlowColors;

        float beforeAlpha = trail->color.a;
        trail->color = trail->colorOverwrite ? trail->forcedColor : ColorWithAlpha(color, beforeAlpha);
        for (auto glow : glowColors)
            SetColors(glow, color);
        for (auto fakeGlow : fakeGlowColors)
            SetColors(fakeGlow, color);
        if (light && light->m_CachedPtr.m_value)
            light->set_color(color);
    }
}