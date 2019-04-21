# 排序算法实现

```cpp
void InsertSort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        int temp = nums[i];
        int j = 0;
        for (j = i - 1; j >= 0 && nums[j] > temp; j--)
            nums[j + 1] = nums[j];
        nums[j + 1] = temp;
    }
}

void BubbleSort(vector<int> &nums)
{
    bool sorted = false;
    for (int i = 0; i < nums.size() - 1 && !sorted; i++)
    {
        sorted = true;
        for (int j = 1; j < nums.size() - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                sorted = false;
                swap(nums[j], nums[j - 1]);
            }
        }
    }
}

void MergeSort(vector<int> &nums)
{
    MyMergeSort(nums, 0, nums.size() - 1);
}

void SelectionSort(vector<int> &nums)
{

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int minpos = i;

        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] < nums[minpos])
                minpos = j;
        }
        swap(nums[i], nums[minpos]);
    }
}

int partition1(vector<int> &nums, int l, int h)
{
    int i = l + 1, j = h;
    int temp = nums[l];
    while (true)
    {
        while (nums[i] <= temp && i < h)
            i++;
        while (temp <= nums[j] && j > l)
            j--;
        if (i >= j)
            break;
        swap(nums[i], nums[j]);
    }
    swap(nums[l], nums[j]);
    return j;
}
void myqsort(vector<int> &nums, int l, int h)
{
    if (l >= h)
        return;
    int j = partition1(nums, l, h);
    myqsort(nums, l, j - 1);
    myqsort(nums, j + 1, h);
}
void QuickSort(vector<int> &nums)
{
    myqsort(nums, 0, nums.size() - 1);
}

void Merge(vector<int> &nums, int l, int m, int h)
{

    vector<int> temp(nums.begin() + l, nums.begin() + m + 1);
    //	cout << temp.size() << endl;
    int i = l, j = m + 1;
    int k = l;

    while (i <= m || j <= h)
    {
        if (i > m)
        {
            nums[k] = nums[j++];
        }
        else if (j > h)
        {
            nums[k] = temp[i++ - l];
        }
        else if (temp[i - l] < nums[j])
        {
            nums[k] = temp[i++ - l];
        }
        else
            nums[k] = nums[j++];
        k++;
    }
}

void MyMergeSort(vector<int> &nums, int l, int h)
{
    if (l >= h)
        return;
    int m = (h + l) / 2;
    MyMergeSort(nums, l, m);
    MyMergeSort(nums, m + 1, h);
    Merge(nums, l, m, h);
}

void MergeSort(vector<int> &nums)
{
    MyMergeSort(nums, 0, nums.size() - 1);
}
```

# 二分查找

```cpp

//查找是否存在v,不存在返回-1
int binary_search(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] == v)
            return mid;
        else if (nums[mid] > v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

//查找是否存在v，返回第一个，不存在返回-1
int binary_search_first(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] >= v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    if (l < nums.size() && nums[l] == v)
        return l;
    return -1;
}

//查找是否存在v，返回最后一个，不存在返回-1
int binary_search_last(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] > v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    if (h >= 0 && nums[h] == v)
        return h;
    return -1;
}

//查找第一个等于或者大于v的元素

int binary_search_GE(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] >= v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

//查找第一个大于v的元素

int binary_search_G(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] > v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

//查找最后一个等于或者小于v的元素
int binary_search_last_LE(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] > v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return h;
}

//查找最后一个小于v的元素

int binary_search_GE(vector<int> &nums, int v)
{
    int l = 0, h = nums.size() - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] >= v)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return h;
}

```