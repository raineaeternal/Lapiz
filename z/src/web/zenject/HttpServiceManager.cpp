#include "web/zenject/HttpServiceManager.hpp"
#include "web/HttpServiceType.hpp"
#include "zenject/Zenjector.hpp"

using namespace z::web;
using namespace z::web::zenject;

HttpServiceManager::HttpServiceManager(ZenjectManager manager,
                                       ModInfo managerModInfo) {
    _managerModInfo = managerModInfo;
    _zenjectManager = manager;
}
template <class T>
requires CheckType<T, IHttpService>
void HttpServiceManager::addService(ModInfo modInfo) {
    if (!_services.contains(modInfo)) {
        // todo zenject stuff here
        //        Zenjector zenjector = nullptr;
        //        if (zenjector) {
        //            T service = nullptr;
        //            if(zenjector->HttpServiceType) {
        //                if (zenjector->HttpSericeType ==
        //                HttpServiceType::UnityWebRequests) {
        //
        //                }
        //            }
        //        }
    }
}

template <class T>
requires CheckType<T, IHttpService>
    T HttpServiceManager::serviceFromModInfo(const ModInfo &info) {
    return _services[info];
}

void HttpServiceManager::clear() { _services.clear(); }
