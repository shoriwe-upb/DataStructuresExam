//
// Created by universidad on 2/23/2021.
//

#ifndef COLLECTIONS_LIST_NODE_H
#define COLLECTIONS_LIST_NODE_H

#include <stdio.h>
#include "../primitives.h"

typedef struct ListNode {
    char copied;
    void *value;
    size_t value_size;
    struct ListNode *next;
    struct ListNode *before;
} ListNode;

typedef bool (*is_equal_condition)(struct ListNode *node);

#endif //COLLECTIONS_LIST_NODE_H
