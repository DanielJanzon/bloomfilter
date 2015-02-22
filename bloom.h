#ifndef BLOOM_H

#include <stdbool.h>

struct bloom_filter;

struct bloom_filter *bloom_filter_init(int n, int k);

void bloom_filter_add(struct bloom_filter *filter, const char *string);

bool bloom_filter_query(struct bloom_filter *filter, const char *string);

void bloom_filter_print(struct bloom_filter *filter);

#endif
