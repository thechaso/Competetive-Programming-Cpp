#include <bits/stdc++.h>
using namespace std;
#define ll long long

class PriorityQueue
{
public:
    vector<int> data;

    void upHeapify(int i)
    {
        if (i == 0) return;
        int parentInd = (i - 1) / 2;
        if (data[i] < data[parentInd]) {
            swap(data[i], data[parentInd]);
            upHeapify(parentInd);
        }
    }

    void downHeapify(int i)
    {
        int minInd = i;
        int leftInd = 2 * i + 1, rightInd = 2 * i + 2;
        if (leftInd < data.size() && data[leftInd] < data[minInd]) {
            minInd = leftInd;
        }
        if (rightInd < data.size() && data[rightInd] < data[minInd]) {
            minInd = rightInd;
        }
        if (minInd != i) {
            swap(data[minInd], data[i]);
            downHeapify(minInd);
        }
    }

    void add(int n)
    {
        data.push_back(n);
        upHeapify(data.size() - 1);

    }

    int remove()
    {
        if (data.size() == 0) {
            cout << "Underflow" << endl;
            return -1;
        }
        swap(data[0], data[data.size() - 1]);
        int res = data[data.size() - 1];
        data.erase(data.begin() + data.size() - 1);
        downHeapify(0);
        return res;
    }

    int peek()
    {
        if (data.size() == 0) {
            cout << "Underflow" << endl;
            return -1;
        }
        return data[0];
    }

    int size()
    {
        return data.size();
    }
};

int main()
{
    bool run = true;
    PriorityQueue pq;
    while (run) {
        string op;
        cin >> op;
        if (op == "add") {
            int num;
            cin >> num;
            pq.add(num);
        }
        else if (op == "remove") {
            int res = pq.remove();
            if (res != -1) cout << res << endl;
        }
        else if (op == "peek") {
            int res = pq.peek();
            if (res != -1) cout << res << endl;
        }
        else if (op == "size") {
            cout << pq.size() << endl;
        }
        else if (op == "quit") {
            run = false;
        }
    }
}

