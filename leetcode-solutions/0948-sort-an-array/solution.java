class Solution {
    public int[] sortArray(int[] nums) {
        mergeSort(nums, 0, nums.length - 1);
        return nums;
    }

    private void mergeSort(int[] arr, int st, int end) {
        if (st < end) {
            int mid = st + (end - st) / 2;
            mergeSort(arr, st, mid);
            mergeSort(arr, mid + 1, end);
            merge(arr, st, mid, end);
        }
    }

    private void merge(int[] arr, int st, int mid, int end) {
        int i = st, j = mid + 1;
        int size = end - st + 1;
        int[] temp = new int[size];
        int k = 0;

        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= end) temp[k++] = arr[j++];

        for (k = 0; k < size; k++) arr[st + k] = temp[k];
    }
}

