#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WINDOW_SIZE 15
#define THRESHOLD 0.5

double differentiate(double *input, int i) {
    return input[i] - input[i - 1];
}

double movingAverage(double *input, int i) {
    double sum = 0.0;
    for (int j = i - WINDOW_SIZE / 2; j <= i + WINDOW_SIZE / 2; j++) {
        sum += input[j];
    }
    return sum / WINDOW_SIZE;
}

double squaring(double input) {
    return input * input;
}

double integration(double *input, int i) {
    double sum = 0.0;
    for (int j = i - WINDOW_SIZE / 2; j <= i + WINDOW_SIZE / 2; j++) {
        sum += input[j];
    }
    return sum;
}

int detectQRS(double *input, int length, double fs, int *qrsPeaks) {
    double diff[length];
    double squared[length];
    double integrated[length];
    double averaged[length];
    for (int i = 1; i < length; i++) {
        diff[i] = differentiate(input, i);
    }
    for (int i = WINDOW_SIZE / 2; i < length - WINDOW_SIZE / 2; i++) {
        squared[i] = squaring(diff[i]);
    }
    for (int i = WINDOW_SIZE / 2; i < length - WINDOW_SIZE / 2; i++) {
        integrated[i] = integration(squared, i) * fs;
    }
    for (int i = WINDOW_SIZE / 2; i < length - WINDOW_SIZE / 2; i++) {
        averaged[i] = movingAverage(integrated, i);
    }
    double threshold = THRESHOLD * max(averaged, length);
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (averaged[i] > threshold) {
            qrsPeaks[count++] = i;
        }
    }
    return count;
}

int main() {
    double input[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int length = sizeof(input) / sizeof(input[0]);
    double fs = 1200.0;
    int qrsPeaks[length];
    int count = detectQRS(input, length, fs, qrsPeaks);
    printf("QRS peaks: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", qrsPeaks[i]);
    }
    printf("\n");
    return 0;
}

/* This implementation includes the following functions:

differentiate: computes the first-order derivative of the input signal.
movingAverage: computes the moving average of the input signal using a specified window size.
squaring: squares the input signal element-wise.
integration: computes the integral of the input signal using a specified window size.
detectQRS: implements the Pan-Tompkins algorithm for QRS detection on a filtered data stream sampled at fs Hz.
To use this implementation, replace the input array with your filtered data stream and set fs to the sampling 
frequency of your data. 
The output of detectQRS is an array of indices corresponding to the detected QRS peaks in the input signal. */