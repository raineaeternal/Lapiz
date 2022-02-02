#pragma once

#include "web/IHttpService.hpp"

namespace z::web::zenject {
    template <class T>
    requires CheckType<T, IHttpService>
    class ContainerizedHttpService : public IHttpService {
      private:
        T _childService;

      public:
        void setup(T childService);
        std::future<IHttpResponse>
        GetAsync(std::string url, std::function<void(float)> progress) override;
        std::future<IHttpResponse>
        DeleteAsync(std::string url,
                    std::function<void(float)> progress) override;
        std::future<IHttpResponse>
        PostAsync(std::string url, std::string body,
                  std::function<void(float)> progress) override;
        std::future<IHttpResponse>
        PutAsync(std::string url, std::string body,
                 std::function<void(float)> progress) override;
        std::future<IHttpResponse>
        PatchAsync(std::string url, std::string body,
                   std::function<void(float)> progress) override;
    };
} // namespace z::web::zenject