# summry

## substring & sliding windows problems template

```cpp
int findSubstring(string s){
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here */ }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here */ }

            while(/* counter condition */){ 
                 
                 /* update d here if finding minimum*/

                //increase begin to make it invalid/valid again
                
                if(map[s[begin++]]++ ?){ /*modify counter here*/ }
            }  

            /* update d here if finding maximum*/
        }
        return d;
  }
```

## priority_queue 定义

定义一个递增的优先队列

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

## Binary Search

## size()

因为size()返回值是unsigned。所以在执行-1操作后，该循环会一直执行。需要先判断size大小再写成这样。

```cpp
for(int i= 0;i<nums.size()-1;i++)
```