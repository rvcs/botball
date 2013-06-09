
#include <stdio.h>

int main(int argc, char * argv[])
{
  int i;
  float params[20];

  for (i = 1; i < argc; ++i)
  {
    printf("%d: %s\n", i, argv[i]);
    sscanf(argv[i], "%f", &params[i-1]);
  }

  printf("%f %f %f\n", params[0], params[1], params[2]);
}


