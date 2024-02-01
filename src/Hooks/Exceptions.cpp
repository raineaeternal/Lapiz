#include "utilities/logging.hpp"
#include "utilities/hooking.hpp"
#include "System/Exception.hpp"

#include "Zenject/ZenjectException.hpp"

MAKE_AUTO_HOOK_FIND_INSTANCE(ZenjectException_ctor_1, classof(::Zenject::ZenjectException*), ".ctor", void,  Zenject::ZenjectException* self, StringW exceptionMessage) {
    ERROR("ZenjectException: {}", exceptionMessage);
    ZenjectException_ctor_1(self, exceptionMessage);
}

MAKE_AUTO_HOOK_FIND_INSTANCE(ZenjectException_ctor_2, classof(::Zenject::ZenjectException*), ".ctor", void, Zenject::ZenjectException* self, StringW exceptionMessage, System::Exception* innerException) {
    ERROR("ZenjectException: {}", innerException->_message->ToString());
    ZenjectException_ctor_2(self, exceptionMessage, innerException);
}
