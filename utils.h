#pragma once
#include "linuxlist.h"

int list_head_length(struct list_head *head);
struct list_head *list_head_at(struct list_head *head, int index);

