/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_Quantile_Class_
#define _AIMLib_Quantile_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API Quantile : public CharacteristicQuantification
	{
	public:
		Quantile(void);
		Quantile(const Quantile& quantile);
		virtual ~Quantile(void);
		Quantile& operator=(const Quantile& quantile);
		virtual Quantile* Clone() const;

		const QuantificationType GetQuantificationType() const;

		int GetBins() const;
		double GetMinValue() const;
		double GetMaxValue() const;
		int GetSelectedBin() const;

		void SetBins(int newVal);
		void SetMinValue(double minValue);
		void SetMaxValue(double maxValue);
		void SetSelectedBin(int selectedBin);

	protected:
		int _bins;
		double _minValue;
		double _maxValue;
		int _selectedBin;
	};
}
#endif // _AIMLib_Quantile_Class_
