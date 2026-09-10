#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;


struct Bid {
    string bidderId;
    double amount;       // bid price
    long long timestamp; // Unix ms
    int auctionId;
};

// ---------- Utilities ----------
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount
        << " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}





// ---------- TODO: Implement these ----------
void insertionSort(vector<Bid>& v)       // Task A
{
    int n = v.size();

    for (int i = 1; i < n; i++) {
        Bid key = v[i];
        int j = i - 1;
        while (j >= 0 && (v[j].amount > key.amount || (v[j].amount == key.amount && v[j].timestamp > key.timestamp))) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = key;
    }

}
void selectionSort(vector<Bid>& v)        // Task B
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j].amount > v[maxIndex].amount || (v[j].amount == v[maxIndex].amount && v[j].timestamp < v[maxIndex].timestamp)) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(v[i], v[maxIndex]);
        }
    }
}
int interchangeSort(vector<Bid>& v)   // Task C
{
	int swapCount = 0;
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[j].amount < v[i].amount || (v[j].amount == v[i].amount && v[j].timestamp < v[i].timestamp)) {
                swap(v[i], v[j]);
                swapCount++;
            }
        }
    }

    return swapCount;
}
bool bubbleSortEarlyStop(vector<Bid>& v)   // Task D — returns true if stable (no swaps on a full pass)
{
    int n = v.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].amount > v[j + 1].amount || (v[j].amount == v[j + 1].amount && v[j].timestamp > v[j + 1].timestamp)) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            return true;
        }
    }
    return false;
}
bool isLess(const Bid& a, const Bid& b) {
    if (a.amount != b.amount) return a.amount < b.amount;
    return a.timestamp < b.timestamp;
}


int partition(vector<Bid>& v, int lo, int hi) {

    int mid = (lo + hi) / 2;

    if (isLess(v[mid], v[lo])) {
        swap(v[mid], v[lo]);
    }

    if (isLess(v[hi], v[lo])) {
        swap(v[hi], v[lo]);
    }

    if (isLess(v[hi], v[mid])) {
        swap(v[hi], v[mid]);
    }

    swap(v[mid], v[hi]);


    Bid pivot = v[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (v[j].amount < pivot.amount || (v[j].amount == pivot.amount && v[j].timestamp < pivot.timestamp)) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[hi]);
    return i + 1;

}
void quickSort(vector<Bid>& v, int lo, int hi) // Task E 
{
    if (lo < hi) {
        int pivot = partition(v, lo, hi);
        quickSort(v, lo, pivot - 1);
        quickSort(v, pivot + 1, hi);
    }
}

// ---------- Driver ----------
int main(int argc, char* argv[]) {
    // See per-task instructions.
    ofstream file("test_data/large.txt");

    mt19937 gen(12345);
    uniform_real_distribution<double> amount(1, 10000);
    uniform_int_distribution<long long> timestampDist(1000000, 9999999);

    for (int i = 1; i <= 100000; i++)
        file << "bid" << i << " " << amount(gen) << " "
        << timestampDist(gen) << " 1\n";

    file.close();


 
    vector<Bid> bids;

    if (!loadBids("test_data/large.txt", bids)) {
        cout << "Failed to load file.\n";
        return 1;
    }

    cout << "Number of bids: " << bids.size() << "\n";



    auto start = high_resolution_clock::now();

    quickSort(bids, 0, bids.size() - 1);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Quick Sort time: " << duration.count() << " ms\n";


  
    bool sorted = true;

    for (size_t i = 1; i < bids.size(); i++) {
        if (isLess(bids[i], bids[i - 1])) {
            sorted = false;
            break;
        }
    }

    cout << "Sorted: " << (sorted ? "YES" : "NO") << "\n";

    return 0;
}