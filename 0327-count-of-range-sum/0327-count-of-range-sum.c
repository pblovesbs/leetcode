int countWithMergeSort(long long* sums, int left, int right, int lower, int upper, long long* temp) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    int count = countWithMergeSort(sums, left, mid, lower, upper, temp) + 
                countWithMergeSort(sums, mid + 1, right, lower, upper, temp);
    
    int j = mid + 1;
    int k = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && sums[j] - sums[i] < lower) j++;
        while (k <= right && sums[k] - sums[i] <= upper) k++;
        count += k - j;
    }
    
    int p = left;
    int q = mid + 1;
    int r = left;
    
    while (p <= mid && q <= right) {
        if (sums[p] <= sums[q]) {
            temp[r++] = sums[p++];
        } else {
            temp[r++] = sums[q++];
        }
    }
    
    while (p <= mid) temp[r++] = sums[p++];
    while (q <= right) temp[r++] = sums[q++];
    
    for (int i = left; i <= right; i++) {
        sums[i] = temp[i];
    }
    
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long long* sums = (long long*)malloc((numsSize + 1) * sizeof(long long));
    long long* temp = (long long*)malloc((numsSize + 1) * sizeof(long long));
    
    sums[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        sums[i + 1] = sums[i] + nums[i];
    }
    
    int result = countWithMergeSort(sums, 0, numsSize, lower, upper, temp);
    
    free(sums);
    free(temp);
    
    return result;
}