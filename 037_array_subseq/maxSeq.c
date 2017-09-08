
size_t  maxSeq(int * array, size_t n)
{
    size_t max=1, tmp_max=1;
    for (int i=1; i<n; i++)
    {
        if (array[i] > array[i-1])
            tmp_max++;
        else
        {
            if (max < tmp_max)
                max = tmp_max;
            tmp_max=1;
        }
    }
    return max;
}
