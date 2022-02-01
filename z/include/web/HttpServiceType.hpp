#pragma once

namespace z::Web {
    /// @brief Defines a type of HTTP Service
    enum class HttpServiceType {
        /// @brief Uses UnityWebRequests to handle http calls.
        UnityWebRequests,
        /// @brief Uses libcurl to handle http calls.
        /// @deprecated Not currently implemented.
        LibCurl
    };
} // namespace z::Web