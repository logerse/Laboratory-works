#include <stdlib.h>
#include "vector.h"

void v_init(vector_t *vctr)
{
  vctr->HEAD = NULL;
  vctr->TAIL = NULL;
  vctr->count = 0;
};

void v_destruct(vector_t *vctr)
{
  if( vctr->HEAD != NULL ) {
    void *tmp;
    node_t *cur = vctr->HEAD;
    while( cur->next != NULL ) {
      tmp = (void *) cur->next;
      free(cur->data);
      free(cur);
      cur = (node_t *) tmp;
    };
    free(cur);
  };
};

void v_add(vector_t *vctr, size_t sizeOfDataType)
{
  node_t *new_node = (node_t *) malloc(sizeof(node_t));

  new_node->next = NULL;
  new_node->data = malloc(sizeOfDataType);

  if( vctr->TAIL != NULL )
    vctr->TAIL->next = new_node;
  else
    vctr->HEAD = new_node;

  vctr->TAIL = new_node;
  vctr->count++;
};

node_t *v_next(vector_t *vctr)
{
  static node_t *prev = NULL;

  if( prev == NULL ) {
    if( vctr->HEAD == NULL ) return NULL;
    prev = vctr->HEAD;

  } else {
    prev = prev->next;
  };

  return prev;
};
