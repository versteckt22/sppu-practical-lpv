#include <iostream>
#include <omp.h>

using namespace std;

// ---------------- DISPLAY FUNCTION ----------------

void display(int arr[], int n) {

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}

// ---------------- SEQUENTIAL BUBBLE SORT ----------------

void sequentialBubbleSort(int arr[], int n) {

    for(int i = 0; i < n - 1; i++) {

        for(int j = 0; j < n - i - 1; j++) {

            if(arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- PARALLEL BUBBLE SORT ----------------

void parallelBubbleSort(int arr[], int n) {

    for(int i = 0; i < n; i++) {

        // Odd phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2) {

            if(arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Even phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2) {

            if(arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- MERGE FUNCTION ----------------

void merge(int arr[], int low, int mid, int high) {

    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high) {

        if(arr[i] < arr[j]) {

            temp[k] = arr[i];
            i++;
        }
        else {

            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while(i <= mid) {

        temp[k] = arr[i];
        i++;
        k++;
    }

    while(j <= high) {

        temp[k] = arr[j];
        j++;
        k++;
    }

    for(i = low; i <= high; i++) {

        arr[i] = temp[i];
    }
}

// ---------------- SEQUENTIAL MERGE SORT ----------------

void sequentialMergeSort(int arr[], int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;

        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------

void parallelMergeSort(int arr[], int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

// ---------------- MAIN FUNCTION ----------------

int main() {

    int arr1[] = {9, 5, 1, 4, 3, 8, 6, 2, 7};
    int arr2[] = {9, 5, 1, 4, 3, 8, 6, 2, 7};

    int n = 9;

    double start, end;

    // Sequential Bubble Sort

    start = omp_get_wtime();

    sequentialBubbleSort(arr1, n);

    end = omp_get_wtime();

    cout << "Sequential Bubble Sort:\n";
    display(arr1, n);

    cout << "Time: " << end - start << endl << endl;

    // Parallel Bubble Sort

    int arr3[] = {9, 5, 1, 4, 3, 8, 6, 2, 7};

    start = omp_get_wtime();

    parallelBubbleSort(arr3, n);

    end = omp_get_wtime();

    cout << "Parallel Bubble Sort:\n";
    display(arr3, n);

    cout << "Time: " << end - start << endl << endl;

    // Sequential Merge Sort

    start = omp_get_wtime();

    sequentialMergeSort(arr2, 0, n - 1);

    end = omp_get_wtime();

    cout << "Sequential Merge Sort:\n";
    display(arr2, n);

    cout << "Time: " << end - start << endl << endl;

    // Parallel Merge Sort

    int arr4[] = {9, 5, 1, 4, 3, 8, 6, 2, 7};

    start = omp_get_wtime();

    parallelMergeSort(arr4, 0, n - 1);

    end = omp_get_wtime();

    cout << "Parallel Merge Sort:\n";
    display(arr4, n);

    cout << "Time: " << end - start << endl;

    return 0;
}
