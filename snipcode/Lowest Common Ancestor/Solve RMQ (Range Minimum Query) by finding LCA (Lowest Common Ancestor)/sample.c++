vector<int> parent(n, -1); // lưu chỉ số cha của mỗi node
stack<int> s;              // stack lưu các node đang trên most-right path

for (int i = 0; i < n; i++) {
    int last = -1;          // node cuối cùng bị pop ra, sẽ trở thành left child của A[i]

    // Pop các node mà giá trị >= A[i] (vì A[i] sẽ "lấn át" chúng)
    while (!s.empty() && A[s.top()] >= A[i]) {
        last = s.top();      // lưu node bị pop cuối cùng
        s.pop();             // loại node khỏi most right path
    }

    // Nếu stack còn node, node trên cùng bây giờ là cha của A[i]
    if (!s.empty())
        parent[i] = s.top();

    // Nếu có node bị pop (last >= 0), nó trở thành left child của A[i]
    if (last >= 0)
        parent[last] = i;

    s.push(i);              // thêm A[i] vào stack, làm node cuối cùng trên most-right path
}
