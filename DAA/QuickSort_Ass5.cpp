
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

// Random number generator
mt19937 rng(random_device{}());

// Partition function (Lomuto Scheme)
int partitionArray(vector<int>& arr, int low, int high,
                   long long& comparisons) {

    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {

        comparisons++;

        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

// Deterministic Quick Sort
void quickSortDeterministic(vector<int>& arr,
                            int low, int high,
                            long long& comparisons) {

    if(low < high) {

        // Last element is selected as pivot
        int pi = partitionArray(
            arr, low, high, comparisons
        );

        quickSortDeterministic(
            arr, low, pi - 1, comparisons
        );

        quickSortDeterministic(
            arr, pi + 1, high, comparisons
        );
    }
}

// Randomized Quick Sort
void quickSortRandomized(vector<int>& arr,
                         int low, int high,
                         long long& comparisons) {

    if(low < high) {

        // Select a random pivot
        uniform_int_distribution<int> dist(low, high);
        int randomIndex = dist(rng);

        // Move random pivot to the last position
        swap(arr[randomIndex], arr[high]);

        // Apply partition
        int pi = partitionArray(
            arr, low, high, comparisons
        );

        quickSortRandomized(
            arr, low, pi - 1, comparisons
        );

        quickSortRandomized(
            arr, pi + 1, high, comparisons
        );
    }
}

// Display array
void display(vector<int>& arr) {
    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if(n < 0) {
        cout << "Invalid array size";
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter array elements:\n";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Create separate copies
    vector<int> arr1 = arr;
    vector<int> arr2 = arr;

    long long comp1 = 0;
    long long comp2 = 0;

    // Deterministic Quick Sort
    quickSortDeterministic(
        arr1, 0, n - 1, comp1
    );

    // Randomized Quick Sort
    quickSortRandomized(
        arr2, 0, n - 1, comp2
    );

    cout << "\nDeterministic Quick Sort:\n";
    display(arr1);

    cout << "Number of Comparisons: "
         << comp1 << endl;

    cout << "\nRandomized Quick Sort:\n";
    display(arr2);

    cout << "Number of Comparisons: "
         << comp2 << endl;

    return 0;
}