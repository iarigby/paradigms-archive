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
JMP
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

/**
    examples on pointers missing, see handout 13
 */

static int Add(int one, int two)
{
int temp, sum;
sum = one + two;
return sum;
}
/**
 SP = SP - 8
 R1 = M[SP + 12]
 R2 = M[SP + 16]
 R3 = R1 + R2
 M[SP] = R3
 RV = M[SP]
 SP = SP + 8
 RET
 */
static void Caller(void)
{
int num = 10;
num = Add(num, 45);
num = 100;
}

/**
  SP = SP - 4
  M[SP] = 10
  R2 = M[SP]
  SP = SP - 8
  M[SP + 4] = 45
  M[SP] = R2 
  CALL <Add>
  SP = SP + 8
  M[SP] = RV
  M[SP] = 100
  SP = SP + 4
  RET
  */
struct fraction {
int numerator;
int denominator;
};
static void Binky(struct fraction param)
{
struct fraction local;
local.denominator = 1;
param.denominator = 2;
}

static void Caller(void)
{
struct fraction actual;
Binky(actual);
}

static void Apple(void)
{
int i;
short scores[4];
scores[i] = 10;
}
