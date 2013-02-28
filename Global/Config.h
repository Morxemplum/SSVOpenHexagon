// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <fstream>
#include <json/json.h>
#include <json/reader.h>
#include <SSVStart.h>

namespace hg
{
	void loadConfig(std::vector<std::string> mOverridesIds);
	void saveConfig();

	void recalculateSizes();
	void setFullscreen(ssvs::GameWindow& mWindow, bool mFullscreen);

	void setPulse(bool mPulse);

	float getSizeX();
	float getSizeY();
	float getSpawnDistance();
	float getZoomFactor();
	int getPixelMultiplier();
	float getPlayerSpeed();
	float getPlayerFocusSpeed();
	float getPlayerSize();
	bool getNoRotation();
	bool getNoBackground();
	bool getBlackAndWhite();
	bool getNoSound();
	bool getNoMusic();
	int getSoundVolume();
	int getMusicVolume();
	bool getStaticFrameTime();
	float getStaticFrameTimeValue();
	bool getLimitFps();
	bool getVsync();
	bool getAutoZoomFactor();
	bool getFullscreen();
	float getVersion();
	bool getWindowedAutoResolution();
	bool getFullscreenAutoResolution();
	unsigned int getFullscreenWidth();
	unsigned int getFullscreenHeight();
	unsigned int getWindowedWidth();
	unsigned int getWindowedHeight();
	unsigned int getWidth();
	unsigned int getHeight();
	bool getShowMessages();
	bool getChangeStyles();
	bool getChangeMusic();
	bool getDebug();
	bool getPulse();
	bool getBeatPulse();
	bool getInvincible();
	bool get3D(); // TODO!!
}

#endif /* CONFIG_H_ */
