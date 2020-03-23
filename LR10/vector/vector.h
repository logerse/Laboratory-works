#ifndef size_t
#define size_t int
#endif

typedef struct NODE_T {
  struct NODE_T *next;
  void *data;
} node_t;

typedef struct {
  size_t count;
  node_t *HEAD;
  node_t *TAIL;
} vector_t;


void v_init(vector_t *vctr);
node_t *v_next(vector_t *vctr);
void v_destruct(vector_t *vctr);
void v_add(vector_t *vctr, size_t sizeOfDataType);
