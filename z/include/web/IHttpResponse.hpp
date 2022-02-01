#pragma once

#include <future>
#include <optional>

namespace z::Web {
    class IHttpResponse {
      public:
        /// @brief The HTTP response code.
        int code;
        /// @brief Whether or not the reuqest was successful or not.
        bool successful;
        /// @brief Read the body as a string.
        virtual std::future<std::string> readAsStringAsync() = 0;
        /// @brief Read the body as a byte array.
        virtual std::future<std::byte[]> readAsBytesAsync() = 0;
        /// @brief The error of the response. This will first try to grab the
        /// error from an 'error' json field at the root, then go to the http
        /// response, and then will go to the native client.
        virtual std::future<std::optional<std::string>> error() = 0;
    };
} // namespace z::Web