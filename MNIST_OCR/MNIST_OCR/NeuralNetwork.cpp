#include "NeuralNetwork.h"
#include "Image.h"

void Tester::TestTrainingZero() {
	NeuralNetwork nn(28*28, 16, 16, 10);

	// Train all 0s
	int zeroTrainingCounter{};
	Eigen::VectorXd AnswerZero = Eigen::VectorXd(10).setZero();
	AnswerZero[0] = 1;

	std::filesystem::path imgZeroPath(std::string(TrainImagePath) + "0");
	for (std::filesystem::path const& entry : std::filesystem::directory_iterator(imgZeroPath)) {
		if (++zeroTrainingCounter % 1000 == 0) std::cout << "zeroTrainingCounter: " << zeroTrainingCounter << '\n';
		nn.Train(Image(entry).GetVector(), AnswerZero, 50);
	}

	nn.PrintWeights();

	std::filesystem::path imgTestZeroPath(std::string(TestImagePath) + "0/3.jpg");
	std::cout << nn.ForwardPropagation(Image(imgTestZeroPath).GetVector()) << '\n';
	

}

NeuralNetwork::NeuralNetwork(int inputSize, int HL1Size, int HL2Size, int outputSize) {

	mWeights.push_back(Eigen::MatrixXd::Zero(HL1Size, inputSize));
	mWeights.push_back(Eigen::MatrixXd::Zero(HL2Size, HL1Size));
	mWeights.push_back(Eigen::MatrixXd::Zero(outputSize, HL2Size));

	mWeights[0].setRandom();

	for (auto& weight : mWeights) {
		auto ptr = weight.data();
		for (auto& val : weight.reshaped()) val = 0.00001;
	}
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

void NeuralNetwork::Train(Eigen::VectorXd const& input, Eigen::VectorXd const& expectedResult, float learningRate) {

	// Forward propagation Start ---
	std::vector<Eigen::VectorXd> activatedLayers;

	activatedLayers.push_back(input);

	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[0] * activatedLayers[0])); // Logistic regression and fast sigmoid function
	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[1] * activatedLayers[1])); // Logistic regression and fast sigmoid function
	activatedLayers.push_back(FastSigmoidActivationVector(mWeights[2] * activatedLayers[2])); // Logistic regression and fast sigmoid function
	// Forward propagation End ---

	//for (auto ALayer : activatedLayers)
	//	std::cout << ALayer << "\n-----------\n";

	// Back propagation Start ---
	std::deque<Eigen::VectorXd> errorList;
	
	// Prepare error values
	errorList.push_front(activatedLayers.back() - expectedResult); // predicted - expected
	//std::cout << errorList.front() << "\n-----------\n";
	errorList.push_front(CostFunction(mWeights[2], activatedLayers[2], errorList.front()));
	//std::cout << errorList.front() << "\n-----------\n";
	errorList.push_front(CostFunction(mWeights[1], activatedLayers[1], errorList.front()));
	//std::cout << errorList.front() << "\n-----------\n";


	// Updating the weights (weight layer: 0 to 2, error layer: 1 to 3)
	mWeights[0] += learningRate * errorList[0] * activatedLayers[0].transpose();
	mWeights[1] += learningRate * errorList[1] * activatedLayers[1].transpose();
	mWeights[2] += learningRate * errorList[2] * activatedLayers[2].transpose();

	// Back propagation End ---
}

void NeuralNetwork::PrintWeights() {
	for (auto weight : mWeights)
		std::cout << weight << "\n-----------\n";
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
	//std::cout << returnVal << "\n-----------\n";
	Eigen::VectorXd oneMinusActivated = Eigen::VectorXd::Ones(activatedLayer.size()) - activatedLayer;
	//std::cout << oneMinusActivated << "\n-----------\n";
	returnVal = returnVal.asDiagonal()*activatedLayer;
	//std::cout << returnVal << "\n-----------\n";
	returnVal = returnVal.asDiagonal()*oneMinusActivated;
	return returnVal;
}




