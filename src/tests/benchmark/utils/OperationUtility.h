#ifndef PROJECT_OPERATIONUTILITY_H
#define PROJECT_OPERATIONUTILITY_H

#include <future>
#include <thread>
#include <chrono>
#include <utility>
#include <functional>
#include "OperationsCounter.h"

template <typename Func>
std::pair<bool, unsigned long long> run_with_timeout(Func&& func, int timeout_seconds);

#include "OperationUtility.ipp"

#endif //PROJECT_OPERATIONUTILITY_H 