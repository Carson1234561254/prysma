#include <cstdlib>

extern "C" {
    void* prysma_malloc(size_t size) {
        return std::malloc(size); 
    }
}