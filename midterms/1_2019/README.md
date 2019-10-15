# map


## ახსნა

მნიშვნელოვანი მონაცემთა სტრუქტურის გარდა, map ასევე არის ფუნქციურ პროგრამირებაში ერთ-ერთი ყველაზე ხშირად გამოყენებადი ფუნქცია. რადგანაც ფუნქციურ ენებში სია ბაზისურ სტრუქტურად გამოიყეენბა, map-იც მასზე მუშაობს.

map არგუმენტად იღებს ფუნქციას და ამ ფუნქციას apply(როგორაა ქართულად?) სიის თითოეულ ელემენტს. მიღებულ სიაში ელემენტების მიმდევრობა შენარჩუნებულია.

მაგალითად:

```
square(x) => x * x
map(square, [1, 2, 3, 4, 5]) => [1, 4, 9, 16, 25]
```


## პირობა


### 1. იმპლემენტაცია

მოცემულია generic linked list, თქვენ უნდა დაწეროთ ფუნქცია, რომელიც მიიღებს (ასევე generic) ფუნქციის მიმმართებელს და სიის თითოეულ ელემენტზე გამოიძახებს.

function<sub>type</sub> შეგიძლიათ ყველგან ჩაანაცვლოთ სწორი პროტოტიპით, ან გამოიყენოთ typedef map.h-ის სათავეში

```C
typedef struct node {
  void* elem;
  struct node* next;
} node;
```

```C
void map(function_type apply_function, node* head);
```

```C
typedef void (*function_type)(void*);
```

```C
void map(function_type apply_function, node* head) {
// დასაწყისში შემოწმება მნიშვნელოვანია, რადგან შეიძლება პირველივე ელემენტი null იყოს
// null ტესტი არ უნდა იყოს სტუდენტების ტესტერში
  if (head == NULL) return;
  apply_function(head->elem);
  map(head->next, apply_function);
}
```

ამ ფუნქციას ალბათ for loopით დაწერენ და საქმეს გაირთულებენ


### 2. გამოყენება

დავალებლის მეორე ნაწილია კლიენტის კოდის დაწერა.

ეს ორი მაქვს დაწერილი რომ ჩემი დაწერილი კოდი დამეტესტა, არ ვიცი რა სირთულის იყოს ფუნქციები და იქნებ დამეხმაროთ.

```C
void int_apply(void* elem) {
  int* current = ((int*) elem);
  *current = *current + 2;
}
```

```C
void str_apply(void* elem) {
  char* current = ((char*) elem);
  current[0] = 'c';
}
```

```C
#include "stdio.h"

int main(int argc,char **argv) {
/*
  node int_head;
  int elem = 5;
  int_head.elem = &elem;
  int_head.next = NULL;
  int_apply(int_head.elem);
  printf("%d\n", *((int*)int_head.elem));
*/
  node str_head;
  str_head.elem = strdup("avc");
  node str2;
  str2.elem = strdup("vcd");
  str_head.next = &str2.elem;
  str2.next = NULL;
  map(str_apply, &str_head );
  printf("%s\n", (char*)str_head.elem);
  printf("%s\n", (char*)str2.elem);
  return 0;
 }

```
