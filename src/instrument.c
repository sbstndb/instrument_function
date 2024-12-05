#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define MAX_FUNCTIONS 128 

typedef struct {
    void* func;             // function address
    struct timespec start;  
} FunctionTiming;

static FunctionTiming function_timings[MAX_FUNCTIONS];
static int function_count = 0;

void __cyg_profile_func_enter(void* func, void* caller) __attribute__((no_instrument_function));
void __cyg_profile_func_enter(void* func, void* caller) {
    if (function_count < MAX_FUNCTIONS) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts); 
        function_timings[function_count].func = func;
        function_timings[function_count].start = ts;
        function_count++;
    }
}

void __cyg_profile_func_exit(void* func, void* caller) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void* func, void* caller) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    for (int i = 0; i < function_count; i++) {
        if (function_timings[i].func == func) {
            double duration = (end.tv_sec - function_timings[i].start.tv_sec) +
                              (end.tv_nsec - function_timings[i].start.tv_nsec) / 1e9;
            printf("Function at address %p took 6f seconds\n", func, duration);

            for (int j = i; j < function_count - 1; j++) {
                function_timings[j] = function_timings[j + 1];
            }
            function_count--;
            break;
        }
    }
}

