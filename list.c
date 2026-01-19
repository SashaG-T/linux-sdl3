#include "list.h"
#include <assert.h>

void List_Init(struct List* list) {
  list->head = 0;
  list->tail = 0;
}

void List_Append(struct List* list, struct LNode* node) {
  if(list->head == 0) {
    list->head = list->tail = node;
    node->prev = 0;
    node->next = 0;
  } else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    node->next = 0;
  }
}

void List_AppendList(struct List* list, struct List* other) {
  if(!other->head) {
    return;
  }
  if(list->head == 0) {
    list->head = other->head;
    list->tail = other->tail;
  } else {
    list->tail->next = other->head;
    other->head->prev = list->tail;
    list->tail = other->tail;
  }
}

void List_Remove(struct List* list, struct LNode* node) {
  if(node == list->head && list->head == list->tail) {
    list->head = 0;
    list->tail = 0;
  } else if(node == list->head) {
    list->head = node->next;
    list->head->prev = 0;
  } else if(node == list->tail) {
    list->tail = node->prev;
    list->tail->next = 0;
  } else {
    node->next->prev = node->prev;
    node->prev->next = node->next;
  }
  node->next = 0;
  node->prev = 0;
}

struct LNode* List_GetNext(struct List* list, struct LNode* currNode) {
  assert(list != 0);
  return currNode ? currNode->next : list->head;
}

#include "unittest.h"

UNITTEST_IMPL(list_init) {
  struct List list;
  List_Init(&list);
  UNITTEST_ASSERT(list.head == 0);
  UNITTEST_ASSERT(list.tail == 0);
}

UNITTEST_IMPL(list_append) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  struct LNode nodeC;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);
  List_Append(&list, &nodeC);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeA);
  UNITTEST_ASSERT(list.tail == &nodeC);

  //Check LNode Asserts
  UNITTEST_ASSERT(nodeA.prev == 0);
  UNITTEST_ASSERT(nodeA.next == &nodeB);
  UNITTEST_ASSERT(nodeB.prev == &nodeA);
  UNITTEST_ASSERT(nodeB.next == &nodeC);
  UNITTEST_ASSERT(nodeC.prev == &nodeB);
  UNITTEST_ASSERT(nodeC.next == 0);
}

UNITTEST_IMPL(list_appendlist) {
  struct List list1;
  struct LNode nodeA1;
  struct LNode nodeB1;
  struct LNode nodeC1;
  List_Init(&list1);
  List_Append(&list1, &nodeA1);
  List_Append(&list1, &nodeB1);
  List_Append(&list1, &nodeC1);

  struct List list2;
  struct LNode nodeA2;
  struct LNode nodeB2;
  struct LNode nodeC2;
  List_Init(&list2);
  List_Append(&list2, &nodeA2);
  List_Append(&list2, &nodeB2);
  List_Append(&list2, &nodeC2);

  //Action
  List_AppendList(&list1, &list2);

  //Check List Assertions
  UNITTEST_ASSERT(list1.head == &nodeA1);
  UNITTEST_ASSERT(list1.tail == &nodeC2);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA1.prev == 0);
  UNITTEST_ASSERT(nodeC1.next == &nodeA2);
  UNITTEST_ASSERT(nodeA2.prev == &nodeC1);
  UNITTEST_ASSERT(nodeC2.next == 0);
}

UNITTEST_IMPL(list_remove_middle) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  struct LNode nodeC;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);
  List_Append(&list, &nodeC);

  //Action
  List_Remove(&list, &nodeB);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeA);
  UNITTEST_ASSERT(list.tail == &nodeC);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA.prev == 0)
  UNITTEST_ASSERT(nodeA.next == &nodeC);
  UNITTEST_ASSERT(nodeC.prev == &nodeA);
  UNITTEST_ASSERT(nodeC.next == 0);

  UNITTEST_ASSERT(nodeB.prev == 0);
  UNITTEST_ASSERT(nodeB.next == 0);
}

UNITTEST_IMPL(list_remove_head) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  struct LNode nodeC;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);
  List_Append(&list, &nodeC);

  //Action
  List_Remove(&list, &nodeA);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeB);
  UNITTEST_ASSERT(list.tail == &nodeC);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeB.prev == 0)
  UNITTEST_ASSERT(nodeB.next == &nodeC);
  UNITTEST_ASSERT(nodeC.prev == &nodeB);
  UNITTEST_ASSERT(nodeC.next == 0);

  UNITTEST_ASSERT(nodeA.prev == 0);
  UNITTEST_ASSERT(nodeA.next == 0);
}

UNITTEST_IMPL(list_remove_tail) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  struct LNode nodeC;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);
  List_Append(&list, &nodeC);

  //Action
  List_Remove(&list, &nodeC);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeA);
  UNITTEST_ASSERT(list.tail == &nodeB);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA.prev == 0)
  UNITTEST_ASSERT(nodeA.next == &nodeB);
  UNITTEST_ASSERT(nodeB.prev == &nodeA);
  UNITTEST_ASSERT(nodeB.next == 0);

  UNITTEST_ASSERT(nodeC.prev == 0);
  UNITTEST_ASSERT(nodeC.next == 0);
}

UNITTEST_IMPL(list_remove_head2) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);

  //Action
  List_Remove(&list, &nodeA);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeB);
  UNITTEST_ASSERT(list.tail == &nodeB);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA.prev == 0)
  UNITTEST_ASSERT(nodeA.next == 0);
  UNITTEST_ASSERT(nodeB.prev == 0);
  UNITTEST_ASSERT(nodeB.next == 0);
}

UNITTEST_IMPL(list_remove_tail2) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);

  //Action
  List_Remove(&list, &nodeB);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == &nodeA);
  UNITTEST_ASSERT(list.tail == &nodeA);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA.prev == 0)
  UNITTEST_ASSERT(nodeA.next == 0);
  UNITTEST_ASSERT(nodeB.prev == 0);
  UNITTEST_ASSERT(nodeB.next == 0);
}

UNITTEST_IMPL(list_remove_lastnode) {
  struct List list;
  struct LNode nodeA;
  List_Init(&list);
  List_Append(&list, &nodeA);

  //Action
  List_Remove(&list, &nodeA);

  //Check List Assertions
  UNITTEST_ASSERT(list.head == 0);
  UNITTEST_ASSERT(list.tail == 0);

  //Check LNode Assertions
  UNITTEST_ASSERT(nodeA.prev == 0)
  UNITTEST_ASSERT(nodeA.next == 0);
}

UNITTEST_IMPL(list_get_next) {
  struct List list;
  struct LNode nodeA;
  struct LNode nodeB;
  struct LNode nodeC;
  List_Init(&list);
  List_Append(&list, &nodeA);
  List_Append(&list, &nodeB);
  List_Append(&list, &nodeC);

  //Action
  struct LNode* nextA = List_GetNext(&list, 0);
  struct LNode* nextB = List_GetNext(&list, nextA);
  struct LNode* nextC = List_GetNext(&list, nextB);
  struct LNode* nextD = List_GetNext(&list, nextC);

  //Check LNode Assertions
  UNITTEST_ASSERT(nextA == &nodeA);
  UNITTEST_ASSERT(nextB == &nodeB);
  UNITTEST_ASSERT(nextC == &nodeC);
  UNITTEST_ASSERT(nextD == 0);
}




