
void ssort(void *base, int size, int elemSize, int (*cmpFunc)(void *, void *)) {
    int i,j;
    int n = size; 
    for (j = 0; j < n-1; j++)
    {
        int iMin = j;
        for (i = j+1; i < n; i++)
            if (cmpFunc(base[i], base[iMin]) < 0)
                iMin = i;

        if (iMin != j) 
            swap(base[j], base[iMin]);
    }
}

int main() {


}