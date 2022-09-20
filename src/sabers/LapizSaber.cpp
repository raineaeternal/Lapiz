#include "sabers/LapizSaber.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/LayerMask.hpp"
#include "GlobalNamespace/TimeHelper.hpp"
#include "GlobalNamespace/SaberMovementData.hpp"
#include "utilities/saberutil.hpp"
DEFINE_TYPE(Lapiz::Sabers, LapizSaber);

namespace Lapiz::Sabers {
    void LapizSaber::Construct(GlobalNamespace::NoteCutter* noteCutter, GlobalNamespace::ColorManager* colorManager, SaberModelProvider* saberModelProvider) {
        _noteCutter = noteCutter;
        _colorManager = colorManager;
        _saberModelProvider = saberModelProvider;
    }

    void LapizSaber::Update() {
        if (_saber && _saber->m_CachedPtr.m_value && _saber->get_gameObject()->get_activeInHierarchy()) {
            auto topTransform = _saber->saberBladeTopTransform;
            auto bottomTransform = _saber->saberBladeBottomTransform;

            auto topPosition = _saber->saberBladeTopPos = topTransform->get_position();
            auto bottomPosition = _saber->saberBladeBottomPos = bottomTransform->get_position();

            auto time = GlobalNamespace::TimeHelper::get_time();
            _trailSaberMovementData->AddNewData(topPosition, bottomPosition, time);

            if (_saber->get_enabled()) {
                _saber->get_movementData()->AddNewData(topPosition, bottomPosition, time);
                _noteCutter->Cut(_saber);
            }
        }

        if (!_colorProcessNextFrame.empty()) {
            _colorProcessNextFrame.front()();
            _colorProcessNextFrame.pop();
        }
    }
    
    void LapizSaber::LateUpdate() {
        _constructedThisFrame = false;
    }

    void LapizSaber::SetType(GlobalNamespace::SaberType saberType) {
        _saberTypeObject->saberType = saberType;
        SaberUtil::SetColor(_saberModelController, _colorManager->ColorForSaberType(saberType));
    }

    void LapizSaber::SetColor(UnityEngine::Color color) {
        if (!_constructedThisFrame) {
            SaberUtil::SetColor(_saberModelController, color);
            if (colorUpdated) colorUpdated(_saber, color);
        } else {
            _colorProcessNextFrame.push([this, color](){
                SaberUtil::SetColor(_saberModelController, color);
                if (colorUpdated) colorUpdated(_saber, color);
            });
        }
    }

    void LapizSaber::Setup(System::Type* backingType, GlobalNamespace::SaberType saberType) {
        auto gameObject = get_gameObject();
        _saberTypeObject = gameObject->AddComponent<GlobalNamespace::SaberTypeObject*>();
        _saber = reinterpret_cast<GlobalNamespace::Saber*>(gameObject->AddComponent(backingType));
        static int layer = UnityEngine::LayerMask::NameToLayer("Saber");
        gameObject->set_layer(layer);

        _saber->saberType = _saberTypeObject;

        auto top = UnityEngine::GameObject::New_ctor("Top")->get_transform();
        auto bottom = UnityEngine::GameObject::New_ctor("Bottom")->get_transform();

        top->SetParent(get_transform());
        bottom->SetParent(get_transform());

        top->set_position({0, 0, 1});

        _saber->saberBladeTopTransform = top;
        _saber->handleTransform = bottom;
        _saber->saberBladeBottomTransform = bottom;

        _saber->saberBladeTopPos = top->get_position();
        _saber->saberBladeBottomPos = bottom->get_position();

        _saberTypeObject->saberType = saberType;
        _saberModelController = _saberModelProvider->NewModel(saberType);
        _saberModelController->Init(get_transform(), _saber);

        _trailSaberMovementData = GlobalNamespace::SaberMovementData::New_ctor();
        _saberModelController->saberTrail->movementData = _trailSaberMovementData->i_IBladeMovementData();
        _constructedThisFrame = true;
    }
}