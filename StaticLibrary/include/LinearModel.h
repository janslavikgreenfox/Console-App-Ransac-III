#pragma once

#include <vector>
#include "Column.h"
using namespace std;

namespace ConsoleAppRansacIINamespace {
namespace Core {

std::vector<size_t> getRandomIndexes(size_t numberOfSelectedPoints, size_t noOfRows);

class LinearModel {
    private:
	    double _yInterceptAlpha;
	    double _slopeBeta;
	public:
		LinearModel(const LinearModel& other) : _yInterceptAlpha(other._yInterceptAlpha), _slopeBeta(other._slopeBeta) { };
		
		LinearModel& operator=(const LinearModel& other); 
		
		LinearModel(LinearModel&& other) noexcept : _yInterceptAlpha(other._yInterceptAlpha), _slopeBeta(other._slopeBeta) { };
		
		LinearModel& operator=(LinearModel&& other) noexcept; 

		~LinearModel() = default;
	
		LinearModel(const double alpha=0, const double beta=1.0) 
		{
			_yInterceptAlpha = alpha; _slopeBeta = beta;
		};
		double getValueAt0() const { return _yInterceptAlpha; }
		double getSlope() const { return _slopeBeta; }

		void setYIntercept(const double& alpha) { _yInterceptAlpha = alpha; }
		void setSlope(const double& beta) { _slopeBeta = beta; }

		bool isEqualTo(const LinearModel& other) const;

		double getValueAt(const double& abcissa);
		vector<double> getMultipleValuesAt(const vector<double>& abcisses);

		//void fitModelByOrdinaryLeastSquares(const Column& abcissa, const Column& ordinate);


		double sumOfSquaredResiduals(const Column& abcissa, const Column& ordinate);

};

//LinearModel OriginalRANSAC(const Column& abcissa, const Column& ordinate,  const RANSACParameters& parameters);

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
