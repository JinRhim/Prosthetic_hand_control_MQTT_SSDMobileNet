#include "logistic_regression_classifier.h"
#include <Arduino.h> 
// Constructor (if needed)
LogisticRegressionClassifier::LogisticRegressionClassifier() {
  // Initialize any variables or resources here
}

// Prediction function implementation
int LogisticRegressionClassifier::predict(int x1, int x2) {
  // Use the provided weights and bias for prediction
  // Replace weights and bias with actual values from your model
  double weights[3][2] = {{-0.03380946, 0.03126931},
                          {-1.13246563, 1.130974},
                          {1.16627509, -1.16224331}};
  double bias[3] = {77.84127544, -33.53217802, -44.30909742};

  // Calculate the logits
  double logits[3];
  logits[0] = weights[0][0] * x1 + weights[0][1] * x2 + bias[0];
  logits[1] = weights[1][0] * x1 + weights[1][1] * x2 + bias[1];
  logits[2] = weights[2][0] * x1 + weights[2][1] * x2 + bias[2];

  // Calculate the softmax probabilities
  double softmax_probs[3];
  double sum_exp_logits = exp(logits[0]) + exp(logits[1]) + exp(logits[2]);
  softmax_probs[0] = exp(logits[0]) / sum_exp_logits;
  softmax_probs[1] = exp(logits[1]) / sum_exp_logits;
  softmax_probs[2] = exp(logits[2]) / sum_exp_logits;

  // Make a prediction based on the class with the highest probability
  int predicted_class = 0;
  for (int i = 1; i < 3; i++) {
    if (softmax_probs[i] > softmax_probs[predicted_class]) {
      predicted_class = i;
    }
  }

  return predicted_class;
}
