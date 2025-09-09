# LCM
The Least Common Multiple (LCM) of two numbers is the smallest positive number that is evenly divisible by both of them. For example, the LCM of 4 and 6 is 12, as 12 is the smallest number that is divisible by both 4 and 6.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int lcm(int a, int b) {
    
    // larger value
    int g = max(a, b);
    
    // Smaller value
    int s = min(a, b);
    
    for (int i = g; i <= a * b; i += g) {
        if (i % s == 0)
            return i;
    }
}

int main() {
    int a = 10, b = 5;
    cout << lcm(a, b);
    return 0;
}
```