/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Data/StyleData.h"
#include "Utils/Utils.h"

namespace hg
{
	StyleData::StyleData(string mId, float mHueMin, float mHueMax, bool mHuePingPong, float mHueIncrement, bool mHuePulse, bool mMainDynamic,
						float mMainDynamicDarkness, Color mMainStatic, bool mADynamic, float mADynamicDarkness, Color mAStatic,
						bool mBDynamic, bool mBDynamicOffset, float mBDynamicDarkness, Color mBStatic) :
		id{mId}, hueMin{mHueMin}, hueMax{mHueMax}, huePingPong{mHuePingPong}, hueIncrement{mHueIncrement}, huePulse{mHuePulse}, mainDynamic{mMainDynamic},
		mainDynamicDarkness{mMainDynamicDarkness}, mainStatic{mMainStatic}, aDynamic{mADynamic}, aDynamicDarkness{mADynamicDarkness},
		aStatic{mAStatic}, bDynamic{mBDynamic}, bDynamicOffset{mBDynamicOffset}, bDynamicDarkness{mBDynamicDarkness}, bStatic{mBStatic}
	{
		currentHue = hueMin;
		currentSwapTime = 0;
		currentMain = mainStatic;
		currentA = aStatic;
		currentB = bStatic;
	}

	void StyleData::update(float mFrameTime)
	{
		if(mainDynamic) currentMain = getColorFromHue(currentHue / 360.0f);
		else currentMain = mainStatic;

		currentSwapTime += 1.f * mFrameTime;
		if(currentSwapTime > 100) currentSwapTime = 0;

		currentHue += hueIncrement * mFrameTime;
				
		if(currentHue < hueMin)
		{
			if(huePingPong)
			{
				currentHue = hueMin;
				hueIncrement *= -1;
			}
			else currentHue = hueMax;
		}
		if(currentHue > hueMax)
		{
			if(huePingPong)
			{
				currentHue = hueMax;
				hueIncrement *= -1;
			}
			else currentHue = hueMin;
		}

		if(aDynamic) currentA = getColorDarkened(currentMain, aDynamicDarkness);
		else currentA = aStatic;

		if(bDynamic)
		{
			if(!bDynamicOffset) currentB = getColorDarkened(currentMain, bDynamicDarkness);
			else currentB = Color(bStatic.r + currentMain.r / 5, bStatic.g + currentMain.g / 5, bStatic.b + currentMain.b / 5, bStatic.a);
		}
		else currentB = bStatic;

		if(huePulse)
		{
			pulseFactor += pulseFactorIncrement * mFrameTime;

			if(pulseFactor < pulseFactorMin)
			{
				pulseFactorIncrement *= -1;
				pulseFactor = pulseFactorMin;
			}
			if(pulseFactor > pulseFactorMax)
			{
				pulseFactorIncrement *= -1;
				pulseFactor = pulseFactorMax;
			}

			if(!aDynamic) currentA = getColorDarkened(aStatic, pulseFactor);
			if(!bDynamic) currentB = getColorDarkened(bStatic, pulseFactor);
		}

		if(currentSwapTime > 50) std::swap(currentA, currentB);
	}

	string StyleData::getId() 					{ return id; }
	float StyleData::getHueMin() 				{ return hueMin; }
	float StyleData::getHueMax()				{ return hueMax; }
	bool StyleData::getHuePingPong()			{ return huePingPong; }
	float StyleData::getHueIncrement()			{ return hueIncrement; }
	bool StyleData::getHuePulse()				{ return huePulse; }
	bool StyleData::getMainDynamic()			{ return mainDynamic; }
	float StyleData::getMainDynamicDarkness()	{ return mainDynamicDarkness; }
	Color StyleData::getMainStatic()			{ return mainStatic; }
	bool StyleData::getADynamic()				{ return aDynamic; }
	float StyleData::getADynamicDarkness()		{ return aDynamicDarkness; }
	Color StyleData::getAStatic()				{ return aStatic; }
	bool StyleData::getBDynamic()				{ return bDynamic; }
	bool StyleData::getBDynamicOffset() 		{ return bDynamicOffset; }
	float StyleData::getBDynamicDarkness()		{ return bDynamicDarkness; }
	Color StyleData::getBStatic()				{ return bStatic; }

	float StyleData::getCurrentHue() 			{ return currentHue; }
	float StyleData::getCurrentSwapTime() 		{ return currentSwapTime; }
	Color StyleData::getCurrentMain() 			{ return currentMain; }
	Color StyleData::getCurrentA()				{ return currentA; }
	Color StyleData::getCurrentB()				{ return currentB; }
}
