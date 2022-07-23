#include "queue.h"
#include "stdlib.h"
#include "string.h"

int enqueue(struct studentqueue *q, const char *name)
{
  struct studentqueue* new_queue = malloc(sizeof(struct studentqueue));
  if (new_queue == NULL)
    return 0;

  new_queue->name = malloc(strlen(name)+1);
  strcpy(new_queue->name, name);
  new_queue->next=NULL;

  if(q->next==NULL && q->name==NULL) {
    q->next = new_queue;
    return 1;
  }

  struct studentqueue *tail = q;
  while (tail->next != NULL) {
    tail = tail->next;
  }
  tail->next = new_queue;

  return 1;
}

int dequeue(struct studentqueue *q, char *buffer, unsigned int size)
{
  if (q == NULL)
    return 0;

  // Nothign to deuque
  if (q->name == NULL && q->next == NULL)
    return 0;

  struct studentqueue *head = q->next;

  if (strlen(head->name) > size)
    return 0;

  q->next = head->next;

  strcpy(buffer, head->name);
  free(head->name);
  free(head);
  return 1;
}
