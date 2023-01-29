#include <stddef.h>

#define HEAP_SIZE 4096

typedef struct node_t {
    size_t empty;
    size_t size;
    struct node_t *next;
    struct node_t *prev;
} node_t;

typedef struct {
    node_t *header;
} footer_t;

static node_t *heap_head = (node_t *)0;
static size_t heap_node_overhead = sizeof(node_t) + sizeof(footer_t);

void heap_init();
void* heap_alloc(size_t size);
void heap_free(void *);
