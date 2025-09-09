# Note
Dấu hiệu: Liệt kê, đếm, kết hợp các thành phần
Cách giải: DFS, Backtracking...

1. [1201. Ugly Number III](https://leetcode.com/problems/ugly-number-iii/submissions/1755318947/?envType=problem-list-v2&envId=combinatorics)
2. [62. Unique Paths](https://leetcode.com/problems/unique-paths/description/?envType=problem-list-v2&envId=combinatorics)
3. [Count Sorted Vowel Strings](https://leetcode.com/problems/count-sorted-vowel-strings/submissions/1755335321/?envType=problem-list-v2&envId=combinatorics)
4. [Number of Sets of K Non-Overlapping Line Segments](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/?envType=problem-list-v2&envId=combinatorics)

```java
class Solution {
    Integer[][][] dp;
    int mod = 1000000000 + 7;
    int n;
    public int solve(int i, int k, int isStart){
        if(dp[i][k][isStart] != null) return dp[i][k][isStart];
        if(k==0) return 1;
        if(i==n) return 0;
        int res = solve(i+1, k, isStart); // skip ith point
        if(isStart == 1){
            res += solve(i+1, k, 0);
        } else {
            res += solve(i, k-1, 1);
        }
        res %= mod;
        dp[i][k][isStart] = res;
        return res;
    }
    public int numberOfSets(int n, int k) {
        this.n = n;
        this.dp = new Integer[n+1][k+1][2];
        return solve(0, k, 1);
    }
}
```