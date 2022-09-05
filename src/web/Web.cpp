#include "web/Web.hpp"

#include "utilities/logging.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"


namespace Lapiz {
    void HttpService::GET(std::string url) {
        if (url.empty()) 
            WARN();

        auto request = new UnityEngine::Networking::UnityWebRequest();

        request->
    }
}