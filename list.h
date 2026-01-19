#ifndef LLIST_H_
#define LLIST_H_

struct LNode {
  struct LNode* prev;
  struct LNode* next;
};

struct List {
  struct LNode* head;
  struct LNode* tail;
};

void List_Init(struct List* list);
void List_Append(struct List* list, struct LNode* node);
void List_AppendList(struct List* list, struct List* other);
void List_Remove(struct List* list, struct LNode* node);
struct LNode* List_GetNext(struct List* list, struct LNode* currNode);

#endif
