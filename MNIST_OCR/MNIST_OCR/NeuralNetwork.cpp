#include "NeuralNetwork.h"
#include "Image.h"

void NNTest() {
	NeuralNetwork nn(28*28, 16, 16, 10);

	Image arrowImg("..\\..\\asset\\arrow.jpg");

	std::cout << nn.ForwardPropagation(arrowImg.GetVector()) << '\n';

	nn.Train(arrowImg.GetVector(), Eigen::VectorXd(10).setZero());

}


NeuralNetwork::NeuralNetwork(int inputSize, int HL1Size, int HL2Size, int outputSize) {

	mWeights.push_back(Eigen::MatrixXd::Zero(HL1Size, inputSize));
	mWeights.push_back(Eigen::MatrixXd::Zero(HL2Size, HL1Size));
	mWeights.push_back(Eigen::MatrixXd::Zero(outputSize, HL2Size));

}

Eigen::VectorXd NeuralNetwork::ForwardPropagation(Eigen::VectorXd const& input) {

	Eigen::VectorXd a1 = input;

	Eigen::VectorXd z2 = mWeights[0] * a1; // (HL1Size,inputSize) * (inputSize,1) = (HL1Size,1)
	Eigen::VectorXd a2 = FastSigmoidActivationVector(z2);

	Eigen::VectorXd z3 = mWeights[1] * a2; // (HL2Size,HL1Size) * (HL1Size,1) = (HL2Size,1)
	Eigen::VectorXd a3 = FastSigmoidActivationVector(z3);

	Eigen::VectorXd z4 = mWeights[2] * a3; // (HL2Size,HL1Size) * (HL1Size,1) = (HL2Size,1)
	Eigen::VectorXd a4 = FastSigmoidActivationVector(z4);

	return a4;
}

void NeuralNetwork::Train(Eigen::VectorXd const& input, Eigen::VectorXd const& expectedResult) {

	// Forward propagation Start ---
	std::vector<Eigen::VectorXd> activatedLayers;

	activatedLayers.push_back(input);

	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[0] * activatedLayers[0])); // Logistic regression and fast sigmoid function
	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[1] * activatedLayers[1])); // Logistic regression and fast sigmoid function
	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[2] * activatedLayers[2])); // Logistic regression and fast sigmoid function
	// Forward propagation End ---

	// Back propagation Start ---
	std::deque<Eigen::VectorXd> errorList;
	
	// Prepare error values
	errorList.push_front(activatedLayers.back() - expectedResult); // predicted - expected
	errorList.push_front(CostFunction(mWeights[2], activatedLayers[2], errorList.front()));
	errorList.push_front(CostFunction(mWeights[1], activatedLayers[1], errorList.front()));

	// Updating the weights (weight layer: 0 to 2, error layer: 1 to 3)
	mWeights[0] += errorList[0] * activatedLayers[0].transpose();
	mWeights[1] += errorList[1] * activatedLayers[1].transpose();
	mWeights[2] += errorList[2] * activatedLayers[2].transpose();

	// Back propagation End ---

	for (auto weight : mWeights)
		std::cout << weight << "-----------\n";

}


//void NeuralNetwork::BackwardPropagation(Eigen::VectorXd const& predicted, Eigen::VectorXd const& actual) {
//	Eigen::VectorXd finalLayerError = predicted - actual;
//
//
//}


//----------------------
// Helper functions
//----------------------
Eigen::VectorXd NeuralNetwork::FastSigmoidActivationVector(Eigen::VectorXd zVal) {
	for (auto& val : zVal)
		val = val / (1 + abs(val));

	return zVal;
}

Eigen::VectorXd NeuralNetwork::CostFunction(Eigen::MatrixXd const& weights, Eigen::VectorXd const& activatedLayer, Eigen::VectorXd const& prevError) {
	Eigen::VectorXd returnVal = weights.transpose()*prevError;
	Eigen::VectorXd oneMinusActivated = Eigen::VectorXd::Ones(activatedLayer.size()) - activatedLayer;
	returnVal = returnVal.asDiagonal()*activatedLayer;
	returnVal = returnVal.asDiagonal()*oneMinusActivated;
	return returnVal;
}




