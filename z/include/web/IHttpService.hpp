#pragma once

#include <future>
#include <map>
#include <optional>

#include "IHttpResponse.hpp"

template <class Type, class BaseClass>
concept CheckType = std::is_base_of<BaseClass, Type>::value;

namespace z::web {
    class IHttpService {
      public:
        /// @brief The Authorization Bearer token for your requests (primarily
        /// used for auth). Defaults to null.
        std::optional<std::string> token;

        /// @brief The base URL to prefix all requests with. Defaults to null.
        std::optional<std::string> baseURL;

        /// @brief The user agent for your requests. By default, it will be set
        /// to: '[Mod Name]/[Mod Version] ([IHttpService Provider Name]; [Lapiz
        /// Version]; Beat Saber; [Beat Saber Version])
        std::optional<std::string> userAgent;

        /// @brief The default headers for your requests. Token and UserAgent
        /// are synchronized with this.
        std::map<std::string, std::string> headers;

        /// @brief Creates a HTTP GET request.
        /// @param url The URL to send a GET request to.
        /// @param progress A callback that returns progress throughout the
        /// request.
        /// @returns A future with the response.
        virtual std::future<IHttpResponse>
        GetAsync(std::string url,
                 std::function<void(float)> progress = nullptr) = 0;

        /// @brief Creates a HTTP DELETE request.
        /// @param url The URL to send a DELETE request to.
        /// @param progress A callback that returns progress throughout the
        /// request.
        /// @returns A future with the response.
        virtual std::future<IHttpResponse>
        DeleteAsync(std::string url,
                    std::function<void(float)> progress = nullptr) = 0;

        /// @brief Creates a HTTP POST request.
        /// @param url The URL to send a POST request to.
        /// @param body The body of the POST request (UTF-8)
        /// @param progress A callback that returns progress throughout the
        /// request.
        /// @returns A future with the response.
        virtual std::future<IHttpResponse>
        PostAsync(std::string url, std::string body,
                  std::function<void(float)> progress = nullptr) = 0;

        /// @brief Creates a HTTP PUT request.
        /// @param url The URL to send a PUT request to.
        /// @param body The body of the PUT request (UTF-8)
        /// @param progress A callback that returns progress throughout the
        /// request.
        /// @returns A future with the response.
        virtual std::future<IHttpResponse>
        PutAsync(std::string url, std::string body,
                 std::function<void(float)> progress = nullptr) = 0;

        /// @brief Creates a HTTP PATCH request.
        /// @param url The URL to send a PATCH request to.
        /// @param body The body of the PATCH request (UTF-8)
        /// @param progress A callback that returns progress throughout the
        /// request.
        /// @returns A future with the response.
        virtual std::future<IHttpResponse>
        PatchAsync(std::string url, std::string body,
                   std::function<void(float)> progress = nullptr) = 0;
    };
} // namespace z::Web