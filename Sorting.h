#include <bits/stdc++.h>
using namespace std;

//This algorithm runs in O(n^2 time)
vector<int> bubbleSort(vector<int> arr) {
    int len = arr.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <  len; j++) {
            if (j + 1 < len) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    return arr;
}

//This algorithm runs in O(n^2) time
vector<int> insertionSort(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        int cur = arr[i];
        int j = i - 1;
        while ((j >= 0) && (arr[j] > cur)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
    }
    return arr;
}

//This algorithm runs in O(n^2) time
vector<int> selectionSort(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
    return arr;
}

//This algorithm runs in O(n * log(n)) time
vector<int> countingSort(vector<int> v) {
    int mx = *std::max_element(v.begin(), v.end());
    vector<int> counts(mx);
    for (int i : v) ++counts[i];
    for (int i = 1; i <= mx; i++) {
        counts[i] += counts[i - 1];
    }
    vector<int> ans(v.size());
    for (int i : v) {
        int ind = counts[i];
        ans[ind - 1] = i;
        --counts[i];
    }
    return ans;
}

//This algorithm runs in O(n * log(n)) time
vector<int> heapSort(vector<int> arr)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i : arr) pq.push(i);
    vector<int> res;
    while (!pq.empty()) {
        res.push_back(pq.top());
        pq.pop();
    }
    return res;
}

//This algorithm runs in O(n * log(n)) time
vector<int> HighToLowHeapSort(vector<int> arr)
{
    priority_queue<int> pq;
    for (int i : arr) pq.push(i);
    vector<int> res;
    while (!pq.empty()) {
        res.push_back(pq.top());
        pq.pop();
    }
    return res;
}

