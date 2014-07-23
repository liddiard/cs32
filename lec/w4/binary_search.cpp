int search(int a[], int start, int end, int x)
{
    if (start > end) return -1;
    int mid = (start + end) / 2;
    if (a[mid] == x) return true;
    else if (a[mid] < x) return search(a, mid+1, end, x);
    else return search(a, start, mid-1, x);
}
