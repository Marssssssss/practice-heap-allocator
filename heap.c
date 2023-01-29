#include "heap.h"
#include <stdlib.h>

void add_node_footer(node_t *node) {
    ((footer_t *) ((char*) node + sizeof(node_t) + node->size - sizeof(footer_t)))->header = node;
}

void heap_init() {
    heap_head = (node_t *) malloc(HEAP_SIZE);
    memset(heap_head, 0, HEAP_SIZE);
    heap_head->empty = 1;
    heap_head->size = HEAP_SIZE;
    heap_head->next = NULL;
    heap_head->prev = NULL;
}

void *heap_alloc(size_t size) {
    node_t *next = heap_head;
    while ((!next->empty || next->size - heap_node_overhead < size)) {
        next = next->next;
        if ((char*)next - HEAP_SIZE >= heap_head)
            return NULL;
    }

    if (!next) return NULL; // think about expand

    node_t *split = (char*)next + heap_node_overhead + size;
    split->empty = 1;
    split->prev = next;
    split->next = NULL;
    split->size = next->size - heap_node_overhead - size;
    add_node_footer(split);
    
    next->empty = 0;
    next->size = heap_node_overhead + size;
    next->next = split;
    next->prev = ((next != heap_head) ? ((footer_t *)((char *) next - sizeof(footer_t)))->header : NULL);
    add_node_footer(next);

    return (void *)((char*)next + sizeof(node_t));
}

void heap_free(void *ptr) {
    node_t *next = heap_head;
    while (!next->empty && (char*)next + sizeof(node_t) != ptr) {
        next = next->next;
        if ((char*)next - HEAP_SIZE >= heap_head)
            return;
    }

    next->empty = 1;
}