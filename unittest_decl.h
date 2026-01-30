#define UNITTEST_RUN_ORDER \
\
  UNITTEST_RUN(list_init); \
  UNITTEST_RUN(list_append); \
  UNITTEST_RUN(list_appendlist); \
  UNITTEST_RUN(list_remove_middle); \
  UNITTEST_RUN(list_remove_head); \
  UNITTEST_RUN(list_remove_tail); \
  UNITTEST_RUN(list_remove_head2); \
  UNITTEST_RUN(list_remove_tail2); \
  UNITTEST_RUN(list_remove_lastnode); \
  UNITTEST_RUN(list_get_next); \
\
  UNITTEST_RUN(array_create); \
  UNITTEST_RUN(array_expand); \
  UNITTEST_RUN(array_push); \
  UNITTEST_RUN(array_shrink); \
  UNITTEST_RUN(array_pop); \
  UNITTEST_RUN(array_remove); \
  UNITTEST_RUN(array_insert); \
  UNITTEST_RUN(array_destroy);

UNITTEST_DECL(list_init);
UNITTEST_DECL(list_append);
UNITTEST_DECL(list_appendlist);
UNITTEST_DECL(list_remove_middle);
UNITTEST_DECL(list_remove_head);
UNITTEST_DECL(list_remove_tail);
UNITTEST_DECL(list_remove_head2);
UNITTEST_DECL(list_remove_tail2);
UNITTEST_DECL(list_remove_lastnode);
UNITTEST_DECL(list_get_next);

UNITTEST_DECL(array_create);
UNITTEST_DECL(array_expand);
UNITTEST_DECL(array_push);
UNITTEST_DECL(array_shrink);
UNITTEST_DECL(array_pop);
UNITTEST_DECL(array_remove);
UNITTEST_DECL(array_insert);
UNITTEST_DECL(array_destroy);

