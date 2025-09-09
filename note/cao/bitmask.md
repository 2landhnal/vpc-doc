# Note
Dấu hiệu: 
Cách giải: DP, DFS, BFS...

1. [Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square)
2. [Can I Win](https://leetcode.com/problems/can-i-win)

```cpp
class Solution {
public:
    Map<Integer, Boolean> map;
    int state;
    int n;
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        this.map = new HashMap();
        this.n = maxChoosableInteger;
        this.state = 0;
        int sum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        if(sum < desiredTotal) return false;
        if(desiredTotal <= 0) return true;
        return helper(desiredTotal);
    }
    bool solve(int desiredTotal){
        if(desiredTotal<=0) return false;
        if(map.containsKey(state)) return map.get(state);
        for(int i=0; i<n; i++){
            if(state&(1<<i)!=0) continue;
            state = state|(1<<i);
            if(!solve(desiredTotal-i)){
                map.put(state, true);
                state = state&(0<<i);
                return true;
            }
            state = state&(0<<i);
        }
        map.put(state, false);
        return false;
    }
};
```