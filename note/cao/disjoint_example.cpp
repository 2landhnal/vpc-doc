// C++ program to find minimum changes 
// required to make two arrays identical
#include <bits/stdc++.h>
using namespace std;

#define N 100010

/*  'id': stores parent of a node.
    'sz': stores size of a DSU tree. */
int id[N], sz[N];

// Function to assign root
int Root(int idx)
{
    int i = idx;
    while (i != id[i])
        id[i] = id[id[i]], i = id[i];

    return i;
}

// Function to find Union
void Union(int a, int b)
{
    int i = Root(a), j = Root(b);

    if (i != j) {
        if (sz[i] >= sz[j]) {
            id[j] = i, sz[i] += sz[j];
            sz[j] = 0;
        }
        else {
            id[i] = j, sz[j] += sz[i];
            sz[i] = 0;
        }
    }
}

// function to find minimum changes required
// to make both array equal.
int minChange(int n, int a[], int b[])
{

    // Sets as single elements
    for (int i = 0; i < N; i++)
        id[i] = i, sz[i] = 1;

    // Combine items if they belong to different
    // sets.
    for (int i = 0; i < n; ++i)

        // Combine items if they belong to different
    // sets.// true if both elements have different root
        if (Root(a[i]) != Root(b[i]))
            Union(a[i], b[i]); // make root equal

    // Find sum sizes of all sets formed.
    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (id[i] == i)
            ans += (sz[i] - 1);

    return ans;
}

// Driver program
int main()
{

    int a[] = { 2, 1, 1, 3, 5 }, b[] = { 1, 2, 2, 4, 5 };
    int n = sizeof(a) / sizeof(a[0]);
    cout << minChange(n, a, b);
    return 0;
}