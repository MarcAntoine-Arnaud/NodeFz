#ifndef UV_LOGICAL_CALLBACK_NODE_H_
#define UV_LOGICAL_CALLBACK_NODE_H_

#include "unified-callback-enums.h"
#include "list.h"

enum callback_type;
struct callback_info;
struct lcbn_s;
typedef struct lcbn_s lcbn_t;

/* Nodes that comprise a logical callback tree. */
struct lcbn_s
{
  /* Set at registration time. */
  void *context;
  void *cb;
  enum callback_type cb_type; 

  int tree_number; /* Index in the sequence of trees */
  int tree_level;  /* Level in the tree */
  int level_entry; /* What number lcbn in this level of the tree? */

  int global_id; /* The order in which it was executed relative to all other LCBNs */

  struct callback_info *info; /* Set at invoke_callback time. */

  lcbn_t *registrar;   /* Which LCBN registered me? For response CBs. */

  lcbn_t *tree_parent; /* Parent in the tree. which tree am I in? For action CBs. */
  struct list children;

  struct timespec start;
  struct timespec end;

  int active;   /* Is this LCBN currently executing? */
  int finished; /* Has this LCBN finished executing? */
  
  struct list_elem global_order_elem; /* For inclusion in the global callback order list. */
  struct list_elem child_elem; /* For inclusion in logical parent's list of children. */
  struct list_elem root_elem; /* For root nodes: inclusion in the list of logical root nodes. */
};

lcbn_t * lcbn_create (void *context, void *cb, enum callback_type cb_type);
lcbn_t * lcbn_add_child (lcbn_t *parent, lcbn_t *child);
void lcbn_destroy (lcbn_t *lcbn);

void lcbn_mark_begin (lcbn_t *lcbn);
void lcbn_mark_end (lcbn_t *lcbn);

#endif /* UV_LOGICAL_CALLBACK_NODE_H_ */