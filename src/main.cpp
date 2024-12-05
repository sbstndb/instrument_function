#include <iostream>


#include <unordered_map>
#include <chrono>

std::unordered_map<void*, std::chrono::high_resolution_clock::time_point> timers;



void __cyg_profile_func_enter(void* func, void* caller) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void* func, void* caller) __attribute__((no_instrument_function));


int add(int a, int b) {
    return a + b;
}


int main() {
    int result = add(3, 4);
    std::cout << "3 + 4 = " << result << std::endl;
    return 0;
}

