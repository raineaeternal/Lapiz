#include "web/zenject/ContainerizedHttpService.hpp"

using namespace z::web::zenject;
using namespace z::web;

template <class T>
requires CheckType<T, IHttpService>
void ContainerizedHttpService<T>::setup(T childService) {
    this->_childService = childService;
}
template <class T>
requires CheckType<T, IHttpService> std::future<IHttpResponse>
ContainerizedHttpService<T>::GetAsync(std::string url,
                                      std::function<void(float)> progress) {
    return this->_childService->GetAsync(url, progress);
}
template <class T>
requires CheckType<T, IHttpService> std::future<IHttpResponse>
ContainerizedHttpService<T>::DeleteAsync(std::string url,
                                         std::function<void(float)> progress) {
    return this->_childService->DeleteAsync(url, progress);
}
template <class T>
requires CheckType<T, IHttpService> std::future<IHttpResponse>
ContainerizedHttpService<T>::PostAsync(std::string url, std::string body,
                                       std::function<void(float)> progress) {
    return this->_childService->PostAsync(url, body, progress);
}
template <class T>
requires CheckType<T, IHttpService> std::future<IHttpResponse>
ContainerizedHttpService<T>::PutAsync(std::string url, std::string body,
                                      std::function<void(float)> progress) {
    return this->_childService->PutAsync(url, body, progress);
}
template <class T>
requires CheckType<T, IHttpService> std::future<IHttpResponse>
ContainerizedHttpService<T>::PatchAsync(std::string url, std::string body,
                                        std::function<void(float)> progress) {
    return this->_childService->PatchAsync(url, body, progress);
}