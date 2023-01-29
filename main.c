#include "time.h"
#include "heap.h"

int main(int args, char* argv[]) {
    heap_init();
    
    printf("%d, %d, %d, %d\n", sizeof(size_t), heap_node_overhead, sizeof(node_t), sizeof(footer_t));
    int repeat_time = 10000000;

    // test heap
    time_t start_time = clock();

    // for (int i = 0; i < repeat_time; i++) {
    while (1) {
        void* alloc1 = heap_alloc(4);
        // printf("%u\n", (unsigned int)alloc1);

        void* alloc2 = heap_alloc(128);
        // printf("%u\n", (unsigned int)alloc2);

        void* alloc3 = heap_alloc(4);
        // printf("%u\n", (unsigned int)alloc3);

        heap_free(alloc2);
        void* alloc4 = heap_alloc(1000);
        // printf("%u\n", (unsigned int)alloc4);

        heap_free(alloc3);
        heap_free(alloc1);
        heap_free(alloc4);
    }

    time_t end_time = clock();
    printf("heap cost(clocks): %d\n", end_time - start_time);


    // test malloc
    start_time = clock();

    // for (int i = 0; i < repeat_time; i++) {
    while (1) {
        void* alloc1 = malloc(4);
        // printf("%u\n", (unsigned int)alloc1);

        void* alloc2 = malloc(128);
        // printf("%u\n", (unsigned int)alloc2);

        void* alloc3 = malloc(4);
        // printf("%u\n", (unsigned int)alloc3);

        free(alloc2);
        void* alloc4 = malloc(1000);
        // printf("%u\n", (unsigned int)alloc4);

        free(alloc3);
        free(alloc1);
        free(alloc4);
    }

    end_time = clock();
    printf("malloc cost(clocks): %d\n", end_time - start_time);
}