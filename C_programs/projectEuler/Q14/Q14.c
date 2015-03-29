#include <stdio.h>
#include <stdlib.h>

#ifndef MAXNUM
  #define MAXNUM 20
#endif

struct ans {
  long long int num;
  long long int chainNum;
};

int main (int argc, char **agrv) {
  long long int i, num, j, chain;
  struct ans ans;
  ans.num = 0;
  ans.chainNum = 0;
  
  for (num = MAXNUM; num > 0; num--) {
    chain = num;
    for (i = 1; chain != 1; i++) {
      if (chain % 2 == 0) {
	chain = chain / 2;
      }
      else {
	chain = chain * 3 + 1;
      }
    }
    //printf("i: %lld\n", i);
    if (i > ans.chainNum) {
      ans.num = num;
      ans.chainNum = i;
    }
  }

  printf("ans: %lld, length: %lld", ans.num, ans.chainNum);
  
  return 0;
}
