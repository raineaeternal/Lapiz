#include "web/implementations/uwr/UWRHttpService.hpp"

#include "System/IO/Path.hpp"
#include "System/Text/Encoding.hpp"
#include "UnityEngine/AsyncOperation.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/Networking/DownloadHandlerBuffer.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/UploadHandlerRaw.hpp"
#include "beatsaber-hook/shared/utils/typedefs-string.hpp"

using namespace z::web;
using namespace z::web::implementations::uwr;
using namespace UnityEngine::Networking;
using namespace UnityEngine;

std::future<IHttpResponse> UWRHttpService::sendAsync(
    HTTPMethod method, std::string url, std::string body = "",
    std::map<std::string, std::string> withHeaders = {},
    std::function<void(float)> downloadProgress = nullptr) {

    StringW newURL = StringW(url);
    if (baseURL.has_value()) {
        newURL = System::IO::Path::Combine(baseURL.value(), newURL);
    }

    DownloadHandler *dlHandler = DownloadHandlerBuffer::New_ctor();

    HTTPMethod originalMethod = method;
    // user may use HTTPMethod::POST_NBC to bypass this.
    if (originalMethod == HTTPMethod::POST && !body.empty()) {
        method = HTTPMethod::PUT;
    }

    UploadHandlerRaw *rawUploadHandler = UploadHandlerRaw::New_ctor(
        System::Text::Encoding::get_UTF8()->GetBytes(body));

    StringW UWR_method;

    switch (method) {
    case HTTPMethod::PUT: UWR_method = "PUT";
    case HTTPMethod::POST:
    case HTTPMethod::POST_NBC: UWR_method = "POST";
    case HTTPMethod::PATCH: UWR_method = "PATCH";
    case HTTPMethod::GET: UWR_method = "GET";
    case HTTPMethod::DELETE: UWR_method = "DELETE";
    }

    UnityWebRequest *request;

    if (method == HTTPMethod::POST_NBC) {
        request = UnityWebRequest::New_ctor(newURL, UWR_method, dlHandler,
                                            rawUploadHandler);
    } else {
        request = UnityWebRequest::New_ctor(newURL, UWR_method, dlHandler,
                                            body.empty() ? nullptr
                                                         : rawUploadHandler);
    }

    request->set_timeout(60);

    for (const auto &item : headers) {
        request->SetRequestHeader(item.first, item.second);
    }

    if (!withHeaders.empty()) {
        for (const auto &item : withHeaders) {
            request->SetRequestHeader(item.first, item.second);
        }
    }

    if (!body.empty()) {
        request->SetRequestHeader("Content-Type", "application/json");
    }

    // unity being an idiot
    if (!body.empty() && originalMethod == HTTPMethod::POST &&
        method == HTTPMethod::PUT) {
        request->set_method(UWR_method);
    }

    float _lastProgress = -1.0f;
    AsyncOperation *asyncOp =
        reinterpret_cast<AsyncOperation *>(request->SendWebRequest());
    while (!asyncOp->get_isDone()) {
        if (downloadProgress && dlHandler) {
            float currentProgress = asyncOp->get_progress();
            if (_lastProgress != currentProgress) {
                downloadProgress(currentProgress);
                _lastProgress = currentProgress;
            }
        }
        // todo pause 10 sec here
    }

    return std::future<IHttpResponse>();
}
