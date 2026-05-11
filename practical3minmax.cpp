#include <iostream>
#include <omp.h>

using namespace std;

int main() {

    int arr[5] = {10, 20, 5, 40, 15};

    int sum = 0;
    int min = arr[0];
    int max = arr[0];

    // Parallel Sum Reduction
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < 5; i++) {

        sum = sum + arr[i];
    }

    // Parallel Minimum Reduction
    #pragma omp parallel for reduction(min:min)
    for(int i = 0; i < 5; i++) {

        if(arr[i] < min)
            min = arr[i];
    }

    // Parallel Maximum Reduction
    #pragma omp parallel for reduction(max:max)
    for(int i = 0; i < 5; i++) {

        if(arr[i] > max)
            max = arr[i];
    }

    // Average
    float avg = (float)sum / 5;

    // Output
    cout << "Sum = " << sum << endl;
    cout << "Minimum = " << min << endl;
    cout << "Maximum = " << max << endl;
    cout << "Average = " << avg << endl;

    return 0;
}
