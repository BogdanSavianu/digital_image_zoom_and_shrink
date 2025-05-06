#ifndef PROJECT_OPERATIONSCOUNTER_H
#define PROJECT_OPERATIONSCOUNTER_H

class OperationsCounter {
public:
    static unsigned long long count;
    static unsigned long long getCount() { return count; }
    static void reset() { count = 0; }
    static void increment() { count++; }
    static void add(unsigned long long n) { count += n; }
};

#endif //PROJECT_OPERATIONSCOUNTER_H 