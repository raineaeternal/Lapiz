#include "customtypes/MainThreadScheduler.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

DEFINE_TYPE(z, MainThreadScheduler);

std::vector<std::function<void()>> z::MainThreadScheduler::scheduledMethods;
std::mutex z::MainThreadScheduler::scheduledMethodsMutex;

void z::MainThreadScheduler::Update() {
    std::lock_guard<std::mutex> lock(scheduledMethodsMutex);
    if (scheduledMethods.size() > 0) {
        for (std::function<void()> method : scheduledMethods) {
            method();
        }
        scheduledMethods.clear();
    }
}