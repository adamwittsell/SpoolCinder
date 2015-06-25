#pragma once
#include "cinder/app/App.h"
#include "cinder/Surface.h"

#include <vector>

class VideoBuffer
{
public:
	VideoBuffer();
	void            init(int frames, int width, int height);

	void            recFrame(ci::Surface sourceImg);
	void            clearBuffer();
	void            draw(ci::Rectf square);
	ci::Surface8u   play();

	int             maxFrames;
	bool            recLoop;
	bool            rec;

	ci::Surface8u   nullFrame;

	std::vector<ci::Surface8u> videoBuffer;
	std::vector<ci::Surface8u>::iterator recIt;

	int recPos;
	int playPos;
	~VideoBuffer();
};

