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
	info = "idle";

	recStartedFrame = 0;
	recEndedFrame = 0;

	recStarted = false;

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

void VideoBuffer::update()
{
	if (rec && !recStarted) {
		recStartedFrame = recIt - videoBuffer.begin();
		recStarted = true;
	}
	
	if (recStarted && !rec) {
		recEndedFrame = recIt - videoBuffer.begin();
		recStarted = false;
	}
}


void VideoBuffer::recFrame(Surface8u sourceImg)
{

	if (recIt != videoBuffer.end()) {
		*recIt = sourceImg.clone();
		recEndedFrame = recIt - videoBuffer.begin();

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

void VideoBuffer::clearBuffer()
{
	videoBuffer.clear();
}


Surface8u VideoBuffer::play()
{
	playPos++;


	if (playPos >= recEndedFrame ) {
		playPos = recStartedFrame;
	}
	return videoBuffer.at(playPos);
}
