#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    deposit, withdraw
} transactType;

/* Calculates the balance of the user. */
int get_balance(void *transactions, int n, char* account);