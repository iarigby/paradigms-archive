typedef struct Transaction{
	char * from;
	char to[8];
	int amount;
} Transaction;

int hash(void *item);

int Transfer(struct Transaction trans, int * accounts)
{
	int index = hash(trans.from);
	if (accounts[index] > trans.amount){
		accounts[index] = accounts[index]-trans.amount;
		accounts[trans.to[0]] = accounts[(int)trans.to]+trans.amount;
		return index;
	}
	return -1;
}
