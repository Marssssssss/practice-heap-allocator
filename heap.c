#include "heap.h"
#include <stdlib.h>

void add_node_footer(node_t *node) {
    ((footer_t *) ((char*) node + node->size - sizeof(footer_t)))->header = node;
}

node_t* get_prev(node_t *node) {
    footer_t *prev_footer = ((footer_t *)((char *) node - sizeof(footer_t)));
    return (prev_footer < heap_head) ?  NULL : prev_footer->header;
}

node_t* get_next(node_t *node) {
    node_t *next = (node_t *)((char*)node + node->size);
    return ((char*)next - HEAP_SIZE >= heap_head) ? NULL : next;
}

void heap_init() {
    heap_head = (node_t *) malloc(HEAP_SIZE);
    memset(heap_head, 0, HEAP_SIZE);
    heap_head->empty = 1;
    heap_head->size = HEAP_SIZE;
}

void *heap_alloc(size_t size) {
    node_t *next = heap_head;
    while ((!next->empty || next->size - heap_node_overhead < size + sizeof(node_t))) {
        next = get_next(next);
        if (!next) return NULL; // think about expand
    }


    node_t *split = (char*)next + heap_node_overhead + size;
    split->empty = 1;
    split->size = next->size - heap_node_overhead - size;
    add_node_footer(split);

    next->empty = 0;
    next->size = heap_node_overhead + size;
    add_node_footer(next);

    return (void *)((char*)next + sizeof(node_t));
}

void heap_free(void *ptr) {
    node_t *next = heap_head;
    while ((char*)next + sizeof(node_t) != ptr) {
        next = get_next(next);
        if (!next) return;
    }

    next->empty = 1;
    node_t *before = get_prev(next);
    node_t *after = get_next(next);

    // merge after block if empty
    if (after && after->empty) {
        next->size += after->size;
        add_node_footer(before);
    }

    // merge before block if empty
    if (before && before->empty) {
        before->size += next->size;
        add_node_footer(before);
        next = before;
    }
} 