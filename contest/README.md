# leetcode contest

## Weekly Contest 186

2020.4.26 

### [1422. Maximum Score After Splitting a String](https://leetcode.com/problems/maximum-score-after-splitting-a-string/)

把01字符串拆成左右两个字串，让左串的0和右串的1数量和最大

```cpp
class Solution
{
public:
    int maxScore(string s)
    {
        int zeros = 0, ones = 0;
        int maxret = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '1')
                ones++;
        }

        for (int i = 0; i < s.size() - 1; i++)
        {
            s[i] == '0' ? zeros++ : ones--;
            maxret = max(maxret, zeros + ones);
        }

        return maxret;
    }
};
```

### [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)

题目等同于求最小连续定长子序列的和

```cpp
class Solution
{
public:
    int maxScore(vector<int> &cardPoints, int k)
    {

        int sum = 0;
        for (int i = 0; i < cardPoints.size(); i++)
            sum += cardPoints[i];

        int sublen = cardPoints.size() - k;

        int tempsum = 0;
        for (int i = 0; i < sublen; i++)
            tempsum += cardPoints[i];

        int minsubsum = tempsum;
        for (int i = sublen; i < cardPoints.size(); i++)
        {
            tempsum += cardPoints[i];
            tempsum -= cardPoints[i - sublen];
            minsubsum = min(minsubsum, tempsum);
        }
        return sum - minsubsum;
    }
};
```

### [1424. Diagonal Traverse II](https://leetcode.com/problems/diagonal-traverse-ii/)

遍历矩阵 暴力会超时，学了一手map。因为每一斜行的i+j都是一样的

```cpp
class Solution
{
public:
    vector<int> findDiagonalOrder(vector<vector<int>> &nums)
    {

        map<int, vector<int>> mymap;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < nums[i].size(); j++)
            {
                mymap[i + j].push_back(nums[i][j]);
            }
        }

        vector<int> ret;
        for (auto &it : mymap)
        {
            auto vec = it.second;
            for (int i = vec.size() - 1; i >= 0; i--)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
};
```

### [1425. Constrained Subset Sum](https://leetcode.com/problems/constrained-subset-sum/)

题都没看 //fix me