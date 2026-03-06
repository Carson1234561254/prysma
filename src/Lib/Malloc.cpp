#include <cstdlib>

extern "C" {
    void* prysma_malloc(size_t size) {
        return std::malloc(size); 
    }

    void prysma_free(void* ptr) {
        if (ptr != nullptr) { 
            std::free(ptr);
        }
    }
}
