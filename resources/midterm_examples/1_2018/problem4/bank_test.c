#include "bank.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool test1()
{
	char *accounts[4];
	accounts[0] = strdup("John doe");
	accounts[1] = strdup("Bob Black");
	accounts[2] = strdup("Brian Adams");
	accounts[3] = strdup("John doe");

	int amounts[4] = {100, 200, 100, 50};
	transactType types[4] = {deposit, deposit, deposit, deposit};

	char *buff = (char*) malloc(100);

	char * curr = buff;

	for (int i = 0; i < 4; i++)
	{
		strcpy(curr, accounts[i]);
		curr += strlen(accounts[i]) + 1;				

		*(transactType*)curr = types[i];
		curr += sizeof(transactType);

		int dist = curr - buff;

		dist %= 4;

		int increase = (4 - dist) % 4;

		curr += increase;

		*(int*) curr = amounts[i];

		curr += sizeof(int);	
	}

	for (int i = 0; i < 4; i++) free(accounts[i]);

	char *johaccount = strdup("John doe");
	char *brianaccount = strdup("Brian Adams");
	char *bobaccount = strdup("Bob Black");
	
	int johnbalance = get_balance(buff, 4, johaccount);	
	int bobbalance = get_balance(buff, 4, bobaccount);	
	int brianbalance = get_balance(buff, 4, brianaccount);	

	free(buff);
	free(johaccount);
	free(brianaccount);
	free(bobaccount);

	return (bobbalance == 200) && (brianbalance == 100) && (johnbalance == 150);
}

bool test2()
{

	char *accounts[2];
	accounts[0] = strdup("John doe");
	accounts[1] = strdup("John doe");

	int amounts[2] = {100, 100};
	transactType types[2] = {deposit, withdraw};

	char *buff = (char*) malloc(100);

	char * curr = buff;

	for (int i = 0; i < 2; i++)
	{
		strcpy(curr, accounts[i]);
		curr += strlen(accounts[i]) + 1;				

		*(transactType*)curr = types[i];
		curr += sizeof(transactType);

		int dist = curr - buff;

		dist %= 4;

		int increase = (4 - dist) % 4;

		curr += increase;

		*(int*) curr = amounts[i];

		curr += sizeof(int);	
	}

	for (int i = 0; i < 2; i++) free(accounts[i]);

	char *account = strdup("John doe");
	int balance = get_balance(buff, 2, account);	
	free(buff);
	free(account);

	return balance == 0;
}

bool test3()
{

	char *accounts[6];
	accounts[0] = strdup("John doe");
	accounts[1] = strdup("John doe");
	accounts[2] = strdup("John doe");
	accounts[3] = strdup("John doe");
	accounts[4] = strdup("John doe");
	accounts[5] = strdup("John doe");

	int amounts[6] = {100, 200, 100, 50, 150, 10};
	transactType types[6] = {deposit, deposit, withdraw, withdraw, deposit, withdraw};

	char *buff = (char*) malloc(150);

	char * curr = buff;

	for (int i = 0; i < 6; i++)
	{
		strcpy(curr, accounts[i]);
		curr += strlen(accounts[i]) + 1;				

		*(transactType*)curr = types[i];
		curr += sizeof(transactType);

		int dist = curr - buff;

		dist %= 4;

		int increase = (4 - dist) % 4;

		curr += increase;

		*(int*) curr = amounts[i];

		curr += sizeof(int);	
	}

	for (int i = 0; i < 6; i++) free(accounts[i]);

	char *account = strdup("John doe");
	int balance = get_balance(buff, 6, account);	
	free(buff);
	free(account);

	return balance == 290;
}
bool test4()
{

	char *accounts[5];
	accounts[0] = strdup("John doe");
	accounts[1] = strdup("Bob Black");
	accounts[2] = strdup("John doe");
	accounts[3] = strdup("Bob Black");
	accounts[4] = strdup("John doe");

	int amounts[5] = {100, 200, 100, 50, 50};
	transactType types[5] = {deposit, deposit, deposit, withdraw, withdraw};

	char *buff = (char*) malloc(100);

	char * curr = buff;

	for (int i = 0; i < 5; i++)
	{
		strcpy(curr, accounts[i]);
		curr += strlen(accounts[i]) + 1;				

		*(transactType*)curr = types[i];
		curr += sizeof(transactType);

		int dist = curr - buff;

		dist %= 4;

		int increase = (4 - dist) % 4;

		curr += increase;

		*(int*) curr = amounts[i];

		curr += sizeof(int);	
	}

	for (int i = 0; i < 5; i++) free(accounts[i]);

	char *johnaccount = strdup("John doe");
	char *bobaccount = strdup("Bob Black");
	int johnbalance = get_balance(buff, 5, johnaccount);	
	int bobbalance = get_balance(buff, 5, bobaccount);	

	free(buff);
	free(johnaccount);
	free(bobaccount);

	return (bobbalance == 150) && (johnbalance == 150);
}

int main()
{

	printf("test1 : %s\n", test1() ? "passed" : "failed" );
	printf("test2 : %s\n", test2() ? "passed" : "failed" );
	printf("test3 : %s\n", test3() ? "passed" : "failed" );
	printf("test4 : %s\n", test4() ? "passed" : "failed" );

	return 0;
}
