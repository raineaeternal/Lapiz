#pragma once

#include "web/HTTPMethod.hpp"
#include "web/IHttpService.hpp"

namespace z::web::implementations::uwr {
    class UWRHttpService : public IHttpService {
      public:
        std::future<IHttpResponse>
        GetAsync(std::string url,
                 std::function<void(float)> progress) override {
            return sendAsync(HTTPMethod::GET, url, nullptr, {}, progress);
        }
        std::future<IHttpResponse>
        DeleteAsync(std::string url,
                    std::function<void(float)> progress) override {
            return sendAsync(HTTPMethod::DELETE, url, nullptr, {}, progress);
        }
        std::future<IHttpResponse>
        PostAsync(std::string url, std::string body,
                  std::function<void(float)> progress) override {
            return sendAsync(HTTPMethod::POST, url, body, {}, progress);
        }
        std::future<IHttpResponse>
        PutAsync(std::string url, std::string body,
                 std::function<void(float)> progress) override {
            return sendAsync(HTTPMethod::PUT, url, body, {}, progress);
        }
        std::future<IHttpResponse>
        PatchAsync(std::string url, std::string body,
                   std::function<void(float)> progress) override {
            return sendAsync(HTTPMethod::PATCH, url, body, {}, progress);
        }
        std::future<IHttpResponse>
        sendAsync(HTTPMethod method, std::string url, std::string body,
                  std::map<std::string, std::string> withHeaders,
                  std::function<void(float)> downloadProgress);
    };
} // namespace z::web::implementations::uwr