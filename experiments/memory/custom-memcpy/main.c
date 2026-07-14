#include <stdio.h> // for printf (C compiler)
#include <stdlib.h> // for malloc and free (C compiler)
#include <string.h> // for standard memcpy and memset (C compiler)
#include <time.h> // for clock_gettime
#include "custom_string.h" 

// A 100 MB buffer for testing
#define BUFFER_SIZE (100 * 1024 * 1024)

int main() {
    // allocate memory for source and destination buffers
    uint8_t* src = (uint8_t*)malloc(BUFFER_SIZE);
    uint8_t* dest = (uint8_t*)malloc(BUFFER_SIZE);
    uint8_t* dest_custom = (uint8_t*)malloc(BUFFER_SIZE);

    if (!src || !dest || !dest_custom) {
        printf("Memory allocation failed\n.");
        return EXIT_FAILURE;
    }

    // Initialize the source buffer with some data
    for (size_t i=0; i < BUFFER_SIZE; i++) {
        src[i] = (uint8_t)(i % 256); // fill with repeating pattern
    }

    // Measure time taken by standard memcpy
    clock_t start = clock();
    memcpy(dest, src, BUFFER_SIZE);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Standard memcpy took %f seconds to copy %d bytes.\n", time_taken, BUFFER_SIZE);

    // Measure time taken by custom memcpy
    start = clock();
    custom_memcpy(dest_custom, src, BUFFER_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Custom memcpy took %f seconds to copy %d bytes.\n", time_taken, BUFFER_SIZE);

    // Verify that both destination buffers are identical
    if (memcmp(dest, dest_custom, BUFFER_SIZE) == 0) {
        printf("Verification successful: Both destination buffers are identical.\n");
    } else {
        printf("Verification failed: Destination buffers differ.\n");
    }
    
    // free allocated memory
    free(src);
    free(dest);
    free(dest_custom);

    return 0;
}
