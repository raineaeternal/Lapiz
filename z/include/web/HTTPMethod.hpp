#pragma once

namespace z::Web {
    /// @brief Represents the most common HTTP methods
    enum class HTTPMethod {
        /// @brief HTTP Get Request
        GET,
        /// @brief HTTP Post Request
        POST,
        /// @brief HTTP Put Request
        PUT,
        /// @brief HTTP Patch Request
        PATCH
    };
} // namespace z::Web