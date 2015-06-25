#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"

#include <vector>

class VideoBuffer
{
public:
	VideoBuffer();
	void            init(int frames, int width, int height);

	void            recFrame(ci::Surface sourceImg);
	void            clearBuffer();
	void            update();
	ci::Surface8u    play();

	std::string		info;

	int             maxFrames;
	bool            recLoop;
	bool            rec;
	bool			recStarted;

	int				recStartedFrame;
	int				recEndedFrame;

	ci::Surface8u   nullFrame;

	std::vector<ci::Surface8u> videoBuffer;
	std::vector<ci::Surface8u>::iterator recIt;

	int recPos;
	int playPos;
};

