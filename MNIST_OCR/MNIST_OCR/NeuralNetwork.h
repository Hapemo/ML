#pragma once
#include "pch.h"
/* Info
* if s = number of hidden layers, number of layer weights is s+1
* Size of hidden layer = Current layer neuron size (j) * Prev layer neuron size (n)


*/

#define TrainImagePath "../../asset/MNIST - JPG - training/"
#define TestImagePath "../../asset/MNIST - JPG - testing/"


class Tester {
public:
	static void TestTrainingZero();


private:

};

// 2 hidden layers only
class NeuralNetwork {
public:

	// input size
	NeuralNetwork(int inputSize, int HL1Size, int HL2Size, int outputSize);

	// Forward propagation takes in input to first layer and returns the result of final layer using
	Eigen::VectorXd ForwardPropagation(Eigen::VectorXd const& input);

	void Train(Eigen::VectorXd const& input, Eigen::VectorXd const& expectedResult, float learningRate);

	//void BackwardPropagation(Eigen::VectorXd const& predicted, Eigen::VectorXd const& actual);

	void PrintWeights();

private:

	// Actual sigmoid function is computationally slow, so a good enough approximation will be used instead
	Eigen::VectorXd FastSigmoidActivationVector(Eigen::VectorXd zVal);

	Eigen::VectorXd CostFunction(Eigen::MatrixXd const& weights, Eigen::VectorXd const& activatedLayer, Eigen::VectorXd const& prevError);

	std::vector<Eigen::MatrixXd> mWeights;
};


















