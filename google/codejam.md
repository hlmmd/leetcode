# google code jam

## code jam 2018

### Practice Session 2018

#### Number Guessing

给一个范围，猜数字。二分法。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int a, b;
        cin >> a >> b;
        int num;
        cin >> num;
        while (1)
        {
            int guess = (a + b) / 2;
            string res;
            cout << guess << endl;
            cin >> res;
            if (res == "CORRECT")
            {
                break;
            }
            else if (res == "TOO_BIG")
            {
                b = guess - 1;
            }
            else
            {
                a = guess + 1;
            }
        }
    }

    return 0;
}
```

