#pragma once

#include "modloader/shared/modloader.hpp"
#include "web/IHttpService.hpp"
#include "zenject/ZenjectManager.hpp"

namespace z::web::zenject {

    class HttpServiceManager {
      public:
        HttpServiceManager(ZenjectManager manager, ModInfo managerModInfo);

        template <class T>
        requires CheckType<T, IHttpService>
        void addService(ModInfo modInfo);

        template <class T>
        requires CheckType<T, IHttpService>
            T serviceFromModInfo(const ModInfo &info);
        void clear();

      private:
        z::ZenjectManager _zenjectManager;
        ModInfo _managerModInfo;
        std::map<ModInfo, IHttpService> _services = {};
    };
} // namespace z::web::zenject