#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global dataset
vector<int> dataset;

// Display menu
void displayMenu() {
    cout << "\n========== Sorting Squad Menu ==========\n";
    cout << "1. Generate random dataset\n";
    cout << "2. Generate already sorted dataset\n";
    cout << "3. Generate reverse sorted dataset\n";
    cout << "4. Run QuickSort\n";
    cout << "5. Run MergeSort\n";
    cout << "6. Compare algorithm performance\n";
    cout << "7. Verify current dataset is sorted\n";
    cout << "8. Show dataset size\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

// Random dataset
vector<int> generateRandomData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 1000000;
    }
    return data;
}

// Already sorted dataset
vector<int> generateSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = i;
    }
    return data;
}

// Reverse sorted dataset
vector<int> generateReverseSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = size - i;
    }
    return data;
}

// Check if array is sorted
bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// QuickSort partition
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Merge helper
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        rightArray[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// MergeSort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Run QuickSort and time it
void runQuickSort() {
    if (dataset.empty()) {
        cout << "No dataset found. Please generate a dataset first.\n";
        return;
    }

    vector<int> temp = dataset;

    auto start = chrono::high_resolution_clock::now();
    quickSort(temp, 0, temp.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\nQuickSort completed.\n";
    cout << "Time taken: " << duration.count() << " ms\n";
    cout << "Sorted correctly? " << (isSorted(temp) ? "Yes" : "No") << "\n";
}

// Run MergeSort and time it
void runMergeSort() {
    if (dataset.empty()) {
        cout << "No dataset found. Please generate a dataset first.\n";
        return;
    }

    vector<int> temp = dataset;

    auto start = chrono::high_resolution_clock::now();
    mergeSort(temp, 0, temp.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\nMergeSort completed.\n";
    cout << "Time taken: " << duration.count() << " ms\n";
    cout << "Sorted correctly? " << (isSorted(temp) ? "Yes" : "No") << "\n";
}

// Compare both algorithms
void compareAlgorithms() {
    if (dataset.empty()) {
        cout << "No dataset found. Please generate a dataset first.\n";
        return;
    }

    vector<int> quickData = dataset;
    vector<int> mergeData = dataset;

    auto quickStart = chrono::high_resolution_clock::now();
    quickSort(quickData, 0, quickData.size() - 1);
    auto quickEnd = chrono::high_resolution_clock::now();

    auto mergeStart = chrono::high_resolution_clock::now();
    mergeSort(mergeData, 0, mergeData.size() - 1);
    auto mergeEnd = chrono::high_resolution_clock::now();

    auto quickTime = chrono::duration_cast<chrono::milliseconds>(quickEnd - quickStart);
    auto mergeTime = chrono::duration_cast<chrono::milliseconds>(mergeEnd - mergeStart);

    cout << "\n========== Performance Comparison ==========\n";
    cout << "QuickSort Time: " << quickTime.count() << " ms\n";
    cout << "MergeSort Time: " << mergeTime.count() << " ms\n";
    cout << "QuickSort sorted correctly? " << (isSorted(quickData) ? "Yes" : "No") << "\n";
    cout << "MergeSort sorted correctly? " << (isSorted(mergeData) ? "Yes" : "No") << "\n";

    if (quickTime.count() < mergeTime.count()) {
        cout << "Result: QuickSort was faster on this dataset.\n";
    } else if (mergeTime.count() < quickTime.count()) {
        cout << "Result: MergeSort was faster on this dataset.\n";
    } else {
        cout << "Result: Both algorithms performed equally on this dataset.\n";
    }
}

// Main
int main() {
    srand(time(0));

    int choice;
    int size;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter dataset size (at least 100000 recommended): ";
                cin >> size;
                dataset = generateRandomData(size);
                cout << "Random dataset generated successfully.\n";
                break;

            case 2:
                cout << "Enter dataset size (at least 100000 recommended): ";
                cin >> size;
                dataset = generateSortedData(size);
                cout << "Already sorted dataset generated successfully.\n";
                break;

            case 3:
                cout << "Enter dataset size (at least 100000 recommended): ";
                cin >> size;
                dataset = generateReverseSortedData(size);
                cout << "Reverse sorted dataset generated successfully.\n";
                break;

            case 4:
                runQuickSort();
                break;

            case 5:
                runMergeSort();
                break;

            case 6:
                compareAlgorithms();
                break;

            case 7:
                if (dataset.empty()) {
                    cout << "No dataset found. Please generate a dataset first.\n";
                } else {
                    cout << "Current dataset sorted? " << (isSorted(dataset) ? "Yes" : "No") << "\n";
                }
                break;

            case 8:
                cout << "Current dataset size: " << dataset.size() << "\n";
                break;

            case 9:
                cout << "Exiting program. Goodbye.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}