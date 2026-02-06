#include <cstdio>

extern "C" {
    void printInt(int x) {
        printf("%d\n", x);
    }

    void printFloat(float x) {
        printf("%f\n", x);
    }
}