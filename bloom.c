#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bloom.h"

typedef uint64_t word;
typedef word *bitfield;

void setbit(bitfield field, int n, bool value)
{
  word *w = &field[n / 64];
  word mask = 1LLU << (n % 64);
  if(value)
    *w |= mask;
  else
    *w &= ~mask;
}

bool getbit(bitfield field, int n)
{
  word w = field[n / 64];
  word mask = 1LLU << (n % 64);
  if(mask & w)
    return true;
  else
    return false;
}

uint64_t str_hash(const char *string, char seed) {
  uint64_t h = 1125899906842597L; // prime
  h = 31*h + seed*h;
  const char *sp = string;
  while (*sp)
    h = 31*h + *sp++;
  return h;
}

struct bloom_filter {
  int n; /* Number of bits in the field */
  unsigned char k; /* Number of hash functions */
  word field[];
};

struct bloom_filter *bloom_filter_init(int n, int k)
{
  if(n < 64)
  {
    return 0;
  }
  int struct_size = sizeof(struct bloom_filter) + n / (8*sizeof(word)) + 1;
  struct bloom_filter *filter = (struct bloom_filter*)calloc(1, struct_size);
  filter->n = n;
  filter->k = k;
  return filter;
}

void bloom_filter_add(struct bloom_filter *filter, const char *string)
{
  int i;

  for(i=0; i<filter->k; i++)
  {
    setbit(filter->field, str_hash(string, i) % filter->n, true);
  }
}

bool bloom_filter_query(struct bloom_filter *filter, const char *string)
{
  int i;

  for(i=0; i<filter->k; i++)
  {
    if(!getbit(filter->field, str_hash(string, i) % filter->n))
      return false;
  }
  return true;
}

void bloom_filter_print(struct bloom_filter *filter)
{
  int i, num_words = filter->n / (8*sizeof(word));
  for(i=0; i<num_words; i++)
  {
    printf("%.16llx ", filter->field[i]);
  }
  puts("\n");
}
