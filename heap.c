#include "heap.h"
#include <stdlib.h>

static inline void add_node_footer(node_t *node) {
    ((footer_t *) ((char*) node + node->size - sizeof(footer_t)))->header = node;
}


static inline node_t* get_prev(node_t *node) {
    footer_t *prev_footer = ((footer_t *)((char *) node - sizeof(footer_t)));
    return (prev_footer < heap_head) ?  NULL : prev_footer->header;
}


static inline node_t* get_next(node_t *node) {
    node_t *next = (node_t *)((char*)node + node->size);
    return ((char*)next - HEAP_SIZE >= heap_head) ? NULL : next;
}


void heap_init() {
    heap_head = (node_t *) malloc(HEAP_SIZE);
    memset(heap_head, 0, HEAP_SIZE);
    heap_head->empty = 1;
    heap_head->size = HEAP_SIZE;
}


void heap_clear() {
    heap_head->empty = 1;
    heap_head->size = HEAP_SIZE;
}


void *heap_alloc(size_t size) {
    node_t *next = heap_head;
    while ((!next->empty || next->size - heap_node_overhead < size + heap_node_overhead)) {
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
        add_node_footer(after);
    }

    // merge before block if empty
    if (before && before->empty) {
        before->size += next->size;
        add_node_footer(before);
        next = before;
    }
}


void heap_merge_fragment() {
    // merge memory fragment
    node_t *empty_block = NULL;
    node_t *next = heap_head;

    while(next) {
        if (next->empty) {
            if (!empty_block) {
                empty_block = next;
            }
            else {
                // merge empty block
                empty_block->size += next->size;
                add_node_footer(empty_block);
            }
            next = get_next(next);
            continue;
        }

        if (!empty_block) {
            next = get_next(next);
            continue;
        }

        // swap next block and empty_block
        char *next_ptr = next;
        char *empty_block_ptr = empty_block;
        char *end_ptr = (char*)get_next(next);
        size_t empty_size = empty_block->size;


        while (next_ptr != (char*)end_ptr) {
            *empty_block_ptr = *next_ptr;
            next_ptr++;
            empty_block_ptr++;
        }

        empty_block = (node_t *)empty_block_ptr;
        empty_block->empty = 1;
        empty_block->size = empty_size;
        add_node_footer(empty_block);

        next = end_ptr;
    }
}


// DEBUG
void print_all_nodes() {
    node_t *next = heap_head;
    while (next) {
        printf("node: %u, empty: %d, size: %u\n", (unsigned int) next, next->empty, (unsigned int)next->size);
        next = get_next(next);
    }
    printf("\n");
}
