#include "sabers/SaberModelProvider.hpp"

#include "utilities/saberutil.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberTypeObject.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(Lapiz::Sabers, SaberModelProvider);

using namespace GlobalNamespace;

namespace Lapiz::Sabers {
    SaberModelProvider* SaberModelProvider::instance;
    SaberModelProvider* SaberModelProvider::get_instance() {
        return instance;
    }

    void SaberModelProvider::ctor(Zenject::DiContainer* container, GlobalNamespace::SaberManager* saberManager, ListWrapper<SaberModelRegistrationWrapper*> saberModelRegistrations) {
        instance = this;
        _earlyInittingGlowColors = System::Collections::Generic::HashSet_1<GlobalNamespace::SetSaberGlowColor*>::New_ctor();
        _earlyInittingFakeGlowColors = System::Collections::Generic::HashSet_1<GlobalNamespace::SetSaberFakeGlowColor*>::New_ctor(); 
        
        _container = container;
        _saberManager = saberManager;

        _localLeftContainer = saberManager->get_leftSaber()->GetComponent<SaberModelContainer*>();
        _localRightContainer = saberManager->get_rightSaber()->GetComponent<SaberModelContainer*>();
        auto registration = std::make_shared<SaberModelRegistration>(_localLeftContainer->saberModelControllerPrefab, _localRightContainer->saberModelControllerPrefab, -1);
        _defaultSaberModelRegistration = SaberModelRegistrationWrapper::Make(registration);

        std::vector<SaberModelRegistrationWrapper*> registrations;
        registrations.reserve(saberModelRegistrations.size() + 1);
        registrations.push_back(_defaultSaberModelRegistration);
        registrations.insert(registrations.begin()++, saberModelRegistrations.begin(), saberModelRegistrations.end());

        std::stable_sort(registrations.begin(), registrations.end(), [](SaberModelRegistrationWrapper* a, SaberModelRegistrationWrapper* b){
            return a->_registration->operator <(*b->_registration);
        });
        _activeSaberModelRegistration = registrations[0];
    }

    void SaberModelProvider::dtor() {
        instance = nullptr;
        Finalize();
    }

    GlobalNamespace::SaberModelController* SaberModelProvider::NewModel(std::optional<GlobalNamespace::SaberType> saberType = std::nullopt) {
        auto newModel = CreateNew(saberType.value_or(SaberType::SaberA));
        for (auto glow : newModel->setSaberGlowColors) {
            if (!saberType.has_value())
                _earlyInittingGlowColors->Add(glow);
            glow->saberType = saberType.value_or(SaberType::SaberA);
        }

        for (auto fakeGlow : newModel->setSaberFakeGlowColors) {
            if (!saberType.has_value())
                _earlyInittingFakeGlowColors->Add(fakeGlow);
            fakeGlow->saberType = saberType.value_or(SaberType::SaberA);
        }

        if (!saberType.has_value())
            SaberUtil::SetColor(newModel, {1, 1, 1, 1});
        return newModel;
    }

    GlobalNamespace::SaberModelController* SaberModelProvider::CreateNew(GlobalNamespace::SaberType saberType) {
        GlobalNamespace::SaberModelController* newModel = nullptr;
        auto reg = _activeSaberModelRegistration->_registration;
        if (reg->_leftType && reg->_rightType) {
            auto defaultPrefab = saberType == SaberType::SaberA ? _defaultSaberModelRegistration->_registration->_leftTemplate : _defaultSaberModelRegistration->_registration->_rightTemplate;
            auto t = saberType == SaberType::SaberA ? reg->_leftType : reg->_rightType;
            auto go = UnityEngine::GameObject::New_ctor(t->name);
            go->SetActive(false);

            auto defaultTrail = defaultPrefab->saberTrail;
            auto pseudoTrail = go->AddComponent<SaberTrail*>();

            pseudoTrail->granularity = defaultTrail->granularity;
            pseudoTrail->trailDuration = defaultTrail->trailDuration;
            pseudoTrail->samplingFrequency = defaultTrail->samplingFrequency;
            pseudoTrail->whiteSectionMaxDuration = defaultTrail->whiteSectionMaxDuration;
            pseudoTrail->trailRendererPrefab = defaultTrail->trailRendererPrefab;
            pseudoTrail->set_enabled(false);

            newModel = reinterpret_cast<SaberModelController*>(_container->InstantiateComponent(il2cpp_utils::GetSystemType(t), go));
            newModel->saberTrail = pseudoTrail;
            newModel->setSaberGlowColors = ArrayW<SetSaberGlowColor*>(il2cpp_array_size_t(0));
            newModel->setSaberFakeGlowColors = ArrayW<SetSaberFakeGlowColor*>(il2cpp_array_size_t(0));
            go->SetActive(true);
        } else if (reg->_leftTemplate && reg->_rightTemplate) {
            newModel = _container->InstantiatePrefab(saberType == SaberType::SaberA ? reg->_leftTemplate.ptr() : reg->_rightTemplate.ptr())->GetComponent<SaberModelController*>();
        } else if (reg->_leftInstruction && reg->_rightInstruction) {
            newModel = saberType == SaberType::SaberA ? reg->_leftInstruction() : reg->_rightInstruction();
            _container->InjectGameObject(newModel->get_gameObject());
        } else {
            throw std::runtime_error("Invalid Saber Registration");
        }
        return newModel;
    }

    bool SaberModelProvider::SetSaberGlowColor_Start_Prefix(GlobalNamespace::SetSaberGlowColor* self) {
        if (_earlyInittingGlowColors->Contains(self)) {
            _earlyInittingGlowColors->Remove(self);
            return false;
        }
        return true;
    }

    bool SaberModelProvider::SetSaberFakeGlowColor_Start_Prefix(GlobalNamespace::SetSaberFakeGlowColor* self) {
        if (_earlyInittingFakeGlowColors->Contains(self)) {
            if (self->saberTypeObject)
                self->saberType = self->saberTypeObject->get_saberType();
            
            _earlyInittingFakeGlowColors->Remove(self);
            return false;
        }
        return true;
    }

    bool SaberModelProvider::SaberModelContainer_Start_Prefix(GlobalNamespace::SaberModelContainer* self) {
        if (self != _localLeftContainer && self != _localRightContainer) return;
        if (_activeSaberModelRegistration == _defaultSaberModelRegistration) return;

        self->saberModelControllerPrefab = NewModel(self->saber->get_saberType());
    }
}
