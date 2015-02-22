#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "bloom.h"

/*
   Test adding n elements and verify presence of them.
*/
void test_presence(int n)
{

}

int main(int argc, char *argv[])
{
  if(argc != 2 && argc != 3)
  {
    fprintf(stderr,
            "usage: %s <width of bit field> [num of hash functions (default=4)]\n",
            argv[0]);
    exit(EX_USAGE);
  }
  int field_width = atoi(argv[1]);
  if(field_width < 64)
  {
    fprintf(stderr, "error: field width must be at least 64 bits\n");
    exit(EX_DATAERR);
  }
  int num_hashes = 4;
  if(argc == 3)
  {
    num_hashes = atoi(argv[2]);
  }

  struct bloom_filter *filter = bloom_filter_init(field_width, num_hashes);

  printf("Usage:\n\n");
  printf("\ta <string>\t\t- Add string to filter\n");
  printf("\te <string>\t\t- Check if string exists in filter\n");
  printf("\ts\t\t\t- Show bloom filter\n");
  printf("\tq\t\t\t- Quit\n\n");

  while(true)
  {
    char buf[128];
    printf("--> ");
    fgets(buf, sizeof buf, stdin);
    int len = strlen(buf);
    if(buf[len-1] == '\n')
      buf[len-1] = '\0';
    switch(buf[0]) {
    case 'a':
      bloom_filter_add(filter, buf+2);
      printf("added '%s'\n", buf+2);
      break;
    case 'e':
      if(bloom_filter_query(filter, buf+2))
        printf("'%s' in set\n", buf+2);
      else
        printf("'%s' not in set\n", buf+2);
      break;
    case 's':
      bloom_filter_print(filter);
      break;
    case 'q':
      exit(EX_OK);
    default:
      printf("unknown command\n");
    }
  }
}
