#include "NeuralNetwork.h"
#include "Image.h"

void NNTest() {
	NeuralNetwork nn(28*28, 16, 16, 10);

	Image arrowImg("..\\..\\asset\\arrow.jpg");

	std::cout << nn.ForwardPropagation(arrowImg.GetVector()) << '\n';

}


NeuralNetwork::NeuralNetwork(int inputSize, int HL1Size, int HL2Size, int outputSize) {

	mHiddenLayerWeights.push_back(Eigen::MatrixXd::Zero(HL1Size, inputSize));
	mHiddenLayerWeights.push_back(Eigen::MatrixXd::Zero(HL2Size, HL1Size));
	mHiddenLayerWeights.push_back(Eigen::MatrixXd::Zero(outputSize, HL2Size));

}

Eigen::VectorXd NeuralNetwork::ForwardPropagation(Eigen::VectorXd const& input) {

	Eigen::VectorXd a1 = input;

	Eigen::VectorXd z2 = mHiddenLayerWeights[0] * a1; // (HL1Size,inputSize) * (inputSize,1) = (HL1Size,1)
	Eigen::VectorXd a2 = FastSigmoidActivationVector(z2);

	Eigen::VectorXd z3 = mHiddenLayerWeights[1] * a2; // (HL2Size,HL1Size) * (HL1Size,1) = (HL2Size,1)
	Eigen::VectorXd a3 = FastSigmoidActivationVector(z3);

	Eigen::VectorXd z4 = mHiddenLayerWeights[2] * a3; // (HL2Size,HL1Size) * (HL1Size,1) = (HL2Size,1)
	Eigen::VectorXd a4 = FastSigmoidActivationVector(z4);

	return a4;
}

void NeuralNetwork::BackwardPropagation() {

}


//----------------------
// Helper functions
//----------------------
Eigen::VectorXd NeuralNetwork::FastSigmoidActivationVector(Eigen::VectorXd zVal) {
	for (auto& val : zVal)
		val = val / (1 + abs(val));

	return zVal;
}





