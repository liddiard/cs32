bool isSorted(int a[], int n)
{
    bool sorted; // assuming it's sorted
    do {
        sorted = true;
        for (int i = 0; i < n-1; i++)
        {
            if (a[i] > a[i+1])
            {
                sorted = false;
                swap(a[i], a[i+1]);
            }
        }
    } while (!sorted);
}
