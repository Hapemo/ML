#include "pch.h"
#include "JazzImage.h"

int main() {

	std::filesystem::path img1("..\\..\\asset\\arrow.jpg");

	JazzImage loadedImg(img1);

#if 1 // Eigen lib testing

	std::cout << loadedImg.GetVector();

	//using Eigen::MatrixXd;
	//using Eigen::VectorXd;

	//MatrixXd m = MatrixXd::Random(3, 3);
	//MatrixXd mConst = MatrixXd::Constant(3, 3, 1.2);
	//m = (m + mConst) * 50;
	//std::cout << "m =" << std::endl << m << std::endl;
	//VectorXd v(3);
	//v << 1, 1, 0;
	//std::cout << "v =" << std::endl << v << std::endl;
	//std::cout << "m * v =" << std::endl << m * v << std::endl;
	//std::cout << "mConst =" << std::endl << mConst<< std::endl;

#endif

	return 1;
}




























