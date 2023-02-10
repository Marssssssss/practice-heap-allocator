#include "time.h"
#include "heap.h"

#define break_if_null(x) if(!x) break

void test_heap_alloc() {
    heap_clear();
    int count = 1;
    while (1) {
        void* alloc1 = heap_alloc(4);
        break_if_null(alloc1);
        count++;

        void* alloc2 = heap_alloc(4);
        break_if_null(alloc2);

        void* alloc3 = heap_alloc(4);
        break_if_null(alloc3);
        count++;

        void* alloc4 = heap_alloc(4);
        break_if_null(alloc4);

        void* alloc6 = heap_alloc(4);
        break_if_null(alloc6);
        count++;

        heap_free(alloc2);
        heap_free(alloc4);

        void* alloc7 = heap_alloc(8);
        break_if_null(alloc7);
        count++;

        // heap_free(alloc1);
        // heap_free(alloc3);
        // heap_free(alloc6);
        // heap_free(alloc7);

        // print_all_nodes();
        // heap_merge_fragment();
        // print_all_nodes();
    }
    printf("test_heap_alloc: %u\n", count);

}

void test_heap_alloc_with_fragment_merge() {
    heap_clear();
    int count = 1;
    while (1) {
        void* alloc1 = heap_alloc(4);
        break_if_null(alloc1);
        count++;

        void* alloc2 = heap_alloc(4);
        break_if_null(alloc2);

        void* alloc3 = heap_alloc(4);
        break_if_null(alloc3);
        count++;

        void* alloc4 = heap_alloc(4);
        break_if_null(alloc4);

        void* alloc6 = heap_alloc(4);
        break_if_null(alloc6);
        count++;

        heap_free(alloc2);
        heap_free(alloc4);

        void* alloc7 = heap_alloc(8);
        break_if_null(alloc7);
        count++;

        // heap_free(alloc1);
        // heap_free(alloc3);
        // heap_free(alloc6);
        // heap_free(alloc7);

        // print_all_nodes();
        heap_merge_fragment();
        // print_all_nodes();
    }
    printf("test_heap_alloc_with_fragment_merge: %u\n", count);

}


void test_malloc() {
    int count = 1;
    size_t s = 0;
    while (1) {
        void* alloc1 = malloc(4);
        s += 4 + heap_node_overhead;
        if (!alloc1 || s >= HEAP_SIZE) break;
        count++;

        void* alloc2 = malloc(4);
        s += 4 + heap_node_overhead;
        if (!alloc2 || s >= HEAP_SIZE) break;

        void* alloc3 = malloc(4);
        s += 4 + heap_node_overhead;
        if (!alloc3 || s >= HEAP_SIZE) break;
        count++;

        void* alloc4 = malloc(4);
        s += 4 + heap_node_overhead;
        if (!alloc4 || s >= HEAP_SIZE) break;

        void* alloc6 = malloc(4);
        s += 4 + heap_node_overhead;
        if (!alloc6 || s >= HEAP_SIZE) break;
        count++;

        heap_free(alloc2);
        heap_free(alloc4);

        void* alloc7 = malloc(8);
        s += 8 + heap_node_overhead;
        if (!alloc7 || s >= HEAP_SIZE) break;
        count++;

        // heap_free(alloc1);
        // heap_free(alloc3);
        // heap_free(alloc6);
        // heap_free(alloc7);
    }
    printf("test_malloc: %u\n", count);
}


int main(int args, char* argv[]) {
    heap_init();
    
    printf("%d, %d, %d, %d\n", sizeof(size_t), heap_node_overhead, sizeof(node_t), sizeof(footer_t));
    test_heap_alloc();
    test_heap_alloc_with_fragment_merge();
    test_malloc();
}