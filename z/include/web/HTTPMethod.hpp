#pragma once

namespace z::web {
    /// @brief Represents the most common HTTP methods
    enum class HTTPMethod {
        /// @brief HTTP Get Request
        GET,
        /// @brief HTTP Post Request
        POST,
        /// @brief HTTP Post Request w/o body checks.
        POST_NBC,
        /// @brief HTTP Put Request
        PUT,
        /// @brief HTTP Patch Request
        PATCH,
        /// @brief HTTP Delete Request
        DELETE
    };
} // namespace z::Web