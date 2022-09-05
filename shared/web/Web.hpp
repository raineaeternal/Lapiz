#pragma once

namespace Lapiz {
    class HttpService {
        void GET(std::string url);

        void POST(std::string url);

        void PUT(std::string url);

        void DELETE(std::string url);
    }
}
