
{
  int i;
  float f;
  f = 3.14159
    i = f;
}

{
  int i;
  if (i >= 0)
    i *= 2;
  i = 10;
}

{
  char ch;
  int i;
  for (i = 0; i < 10; i++)
    ch = 'a';
  i = 25;
}
{
  char ch;
  int i;
  i = 0;
  while (i < 10) {
    ch = 'a';
    i++;
  }
  i = 25;
}


struct binky {
  int a;
  char b, c, d, e;
  short f;
};

{
  struct binky x;
  x.e = 'A';
  x.f = x.a;
}
{
  int arr[20];
  arr[25] = 7;
}
{
  int i;
  struct binky arr[50];
  a[i].f = i;
}

{
  int *ptr;
  *ptr = 120;
}
{
  int *s; i;
  s = &i;
  s++;
}
