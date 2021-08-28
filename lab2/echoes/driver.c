# include <stdio.h>

int main ()
{
  int num = 0;
  for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
    fflush(stdout);
    // scanf("%d", &num);
    // fprintf(stderr, "Even: sent: %d, got %d\n", i, num);
  }

  return 0;
}
