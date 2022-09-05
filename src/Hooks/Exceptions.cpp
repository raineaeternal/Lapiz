#include "utilities/logging.hpp"
#include "utilities/hooking.hpp"
#include "System/Exception.hpp"

#include "Zenject/ZenjectException.hpp"

MAKE_AUTO_HOOK_FIND_INSTANCE(ZenjectException_ctor_1, classof(Zenject::ZenjectException*), ".ctor", void,  Zenject::ZenjectException* self, StringW exepMessage) {
    ERROR("ZenjectException: {}", exepMessage);
    ZenjectException_ctor_1(self, exepMessage);
}

MAKE_AUTO_HOOK_FIND_INSTANCE(ZenjectException_ctor_2, classof(Zenject::ZenjectException*), ".ctor", void, Zenject::ZenjectException* self, StringW exepMessage, System::Exception* inner) {
    ERROR("ZenjectException: {}", inner->message);
    ZenjectException_ctor_2(self, exepMessage, inner);
}