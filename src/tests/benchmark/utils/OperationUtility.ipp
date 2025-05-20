#include "OperationUtility.h"

template<typename Func>
std::pair<bool, unsigned long long> run_with_timeout(Func&& func, int timeout_seconds) {
    std::promise<unsigned long long> result_promise;
    auto result_future = result_promise.get_future();

    std::thread worker([&]() {
        try {
            func();
            result_promise.set_value(OperationsCounter::count);
        } catch (...) {
            try {
                result_promise.set_exception(std::current_exception());
            } catch (...) {}
        }
    });

    worker.detach();

    if (result_future.wait_for(std::chrono::seconds(timeout_seconds)) == std::future_status::ready) {
        return {true, result_future.get()};
    } else {
        return {false, 0};
    }
}