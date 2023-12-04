#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> differentiate(const vector<double>& input) {
    vector<double> output(input.size(), 0.0);
    for (int i = 1; i < input.size(); i++) {
        output[i] = input[i] - input[i - 1];
    }
    return output;
}

vector<double> movingAverage(const vector<double>& input, int windowSize) {
    vector<double> output(input.size(), 0.0);
    for (int i = windowSize / 2; i < input.size() - windowSize / 2; i++) {
        double sum = 0.0;
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; j++) {
            sum += input[j];
        }
        output[i] = sum / windowSize;
    }
    return output;
}

vector<double> squaring(const vector<double>& input) {
    vector<double> output(input.size(), 0.0);
    for (int i = 0; i < input.size(); i++) {
        output[i] = input[i] * input[i];
    }
    return output;
}

vector<double> integration(const vector<double>& input, int windowSize) {
    vector<double> output(input.size(), 0.0);
    for (int i = windowSize / 2; i < input.size() - windowSize / 2; i++) {
        double sum = 0.0;
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; j++) {
            sum += input[j];
        }
        output[i] = sum;
    }
    return output;
}

vector<int> detectQRS(const vector<double>& input, double fs) {
    vector<double> diff = differentiate(input);
    vector<double> squared = squaring(diff);
    vector<double> integrated = integration(squared, static_cast<int>(0.12 * fs));
    vector<double> averaged = movingAverage(integrated, static_cast<int>(0.6 * fs));
    double threshold = 0.5 * (*max_element(averaged.begin(), averaged.end()));
    vector<int> qrsPeaks;
    for (int i = 0; i < averaged.size(); i++) {
        if (averaged[i] > threshold) {
            qrsPeaks.push_back(i);
        }
    }
    return qrsPeaks;
}

int main() {
    vector<double> input = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double fs = 1200.0;
    vector<int> qrsPeaks = detectQRS(input, fs);
    cout << "QRS peaks: ";
    for (int i = 0; i < qrsPeaks.size(); i++) {
        cout << qrsPeaks[i] << " ";
    }
    cout << endl;
    return 0;
}