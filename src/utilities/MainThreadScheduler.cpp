#include "utilities/MainThreadScheduler.hpp"
#include <thread>

DEFINE_TYPE(Lapiz::Utilities, MainThreadScheduler);

namespace Lapiz::Utilities {
    std::queue<std::function<void()>> MainThreadScheduler::scheduled;
    std::mutex MainThreadScheduler::scheduleLock;
    static std::thread::id MainThread;

    void MainThreadScheduler::Initialize() {
        MainThread = std::this_thread::get_id();
    }

    void MainThreadScheduler::Schedule(std::function<void()> function) {
        using CurrentThreadIsMainThreadMethod = function_ptr_t<bool>;
        if(std::this_thread::get_id() == MainThread) {
            function();
            return;
        }

        std::lock_guard<std::mutex> lock(scheduleLock);
        scheduled.push(function);
    }

    void MainThreadScheduler::Tick() {
        if (!scheduled.empty()) {
            std::lock_guard<std::mutex> lock(scheduleLock);
            scheduled.front()();
            scheduled.pop();
        }
    }
}
