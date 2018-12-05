# Graph

##  743. Network Delay Time



## Medium

##  207. Course Schedule

拓扑排序。安排课程顺序

首先，统计各个节点的入度，入度为0的点是不需要前提课程，可以直接学习的。

然后将题目给的数据转换成邻接表

使用队列，将入度为0的点入队，在循环中，每次讲队头出队，根据邻接表将相应的结点入度减1，如果入度变为0，就进队继续循环，知道队列为空，即没有入度为0的点。此时判断总结点数和遍历过的结点个数，如果相等说明能够学习所有课程。

```cpp
class Solution
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        if (numCourses == 0)
            return false;
        queue<int> q;
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for (int i = 0; i < prerequisites.size(); i++)
        {
            indegree[prerequisites[i].second]++;
            adj[prerequisites[i].first].push_back(prerequisites[i].second);
        }

        for (int i = 0; i < indegree.size(); i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }
        int count = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            ++count;

            for (int i = 0; i < adj[v].size(); i++)
            {
                if (!(--indegree[adj[v][i]]))
                    q.push(adj[v][i]);
            }
        }

        return count == numCourses;
    }
};
```

