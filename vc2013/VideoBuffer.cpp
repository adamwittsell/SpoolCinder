#include "VideoBuffer.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/app/RendererGl.h"

#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

VideoBuffer::VideoBuffer()
{
	recLoop = false;
	rec = false;

	recPos = 0;
	playPos = 0;
}

void VideoBuffer::init(int frames,int width, int height)
{

	maxFrames = frames;

	for (int i = 0; i < maxFrames; i++) {
		videoBuffer.push_back(Surface8u(width, height, false));
	}

	nullFrame = Surface8u(width, height, false);

	recIt = videoBuffer.begin();

}


void VideoBuffer::recFrame(Surface8u sourceImg)
{

	if (rec) {

		if (recIt != videoBuffer.end()) {
			*recIt = sourceImg.clone();
			recIt++;
		}

		if (recIt == videoBuffer.end()) {

			if (recLoop) {
				recIt = videoBuffer.begin();
			}
			else {
				recIt = videoBuffer.begin();
				rec = false;
			}
		}

	}
	else {
		recIt = videoBuffer.begin();
	}

}

void VideoBuffer::clearBuffer()
{
	videoBuffer.clear();
}


Surface8u VideoBuffer::play()
{
	if (playPos <= videoBuffer.size() - 1) {
		return videoBuffer.at(playPos);
		playPos++;
	}
	else {
		playPos = 0;
		return videoBuffer.at(playPos);
	}
}



VideoBuffer::~VideoBuffer()
{
}
