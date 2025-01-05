#pragma once

#include <vector>
#include "Column.h"
using namespace std;

namespace ConsoleAppRansacIINamespace {
namespace Core {

/**
* @brief The function to get random selection of indexes.
* @param numberOfSelectedPoints The number of indexes to be selected.
* @param noOfRows The total number of indexes.
* @return A vector of indexes.
*/
std::vector<size_t> getRandomIndexes(size_t numberOfSelectedPoints, size_t noOfRows);


/**
* @class LinearModel
* @brief A class that represents a linear model between two variables.
* 
* @details The class represents a linear model between two variables, X and Y, where Y = _slopeBeta * X + _yInterceptAlpha.
*/
class LinearModel {
    private:
		/**
		* @brief The y-intercept value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		*/
	    double _yInterceptAlpha;

		/**
		* @brief The slope (gradient) value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		*/
	    double _slopeBeta;

	public:
		/**
		* @brief Copy constructor.
		*/
		LinearModel(const LinearModel& other) : _yInterceptAlpha(other._yInterceptAlpha), _slopeBeta(other._slopeBeta) { };
		
		/**
		* @brief Move constructor.
		*/
		LinearModel(LinearModel&& other) noexcept : _yInterceptAlpha(other._yInterceptAlpha), _slopeBeta(other._slopeBeta) { };
		
		/**
		* @brief Copy assignment operator.
		*/
		LinearModel& operator=(const LinearModel& other); 
		
		/**
		* @brief Move assignment operator.
		*/
		LinearModel& operator=(LinearModel&& other) noexcept; 

		/**
		* @brief Destructor.
		*/
		~LinearModel() = default;
	
		/**
		* @brief Parametric constructor.
		* @param alpha The y-intercept value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		* @param beta The slope (gradient) value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		*/
		LinearModel(const double alpha=0, const double beta=1.0) 
		{
			_yInterceptAlpha = alpha; _slopeBeta = beta;
		};

		/**
		* @brief Get the y-intercept value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		* @return The y-intercept value of the linear model.
		*/
		double getValueAt0() const { return _yInterceptAlpha; }

		/**
		* @brief Get the slope (gradient) value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		* @return The slope (gradient) value of the linear model.
		*/
		double getSlope() const { return _slopeBeta; }

		/**
		* @brief Set the y-intercept value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		* @param alpha The y-intercept value of the linear model.
		*/
		void setYIntercept(const double& alpha) { _yInterceptAlpha = alpha; }

		/**
		* @brief Set the slope (gradient) value of the linear model Y = _slopeBeta * X + _yInterceptAlpha.
		* @param beta The slope (gradient) value of the linear model.
		*/
		void setSlope(const double& beta) { _slopeBeta = beta; }

		/**
		* @brief Check if the current linear model is equal to another linear model.
		* @param other The other linear model to compare with.
		*/
		bool isEqualTo(const LinearModel& other) const;

		/**
		* @brief Get the value of the linear model at a given abcissa.
		* @param abcissa The abcissa value.
		*/
		double getValueAt(const double& abcissa);

		/**
		* @brief Get the values of the linear model at multiple abcisses.
		* @param abcisses The vector of abcisses.
		*/
		vector<double> getMultipleValuesAt(const vector<double>& abcisses);

		/**
		* @brief Get the sum of squared residuals for the set of data points against the linear model.
		* @param abcissa The abcissa values.
		* @param ordinate The ordinate values.
		*/
		double sumOfSquaredResiduals(const Column& abcissa, const Column& ordinate);
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
