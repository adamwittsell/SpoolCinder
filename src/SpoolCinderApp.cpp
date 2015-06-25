#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Capture.h"
#include "cinder/Log.h"
#include "VideoBuffer.h"

#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;


class SpoolCinderApp : public App {
  public:
	void prepareSettings(Settings *settings);
	void setup() override;
	void keyDown(KeyEvent event);
	void keyUp(KeyEvent event);
	void update() override;
	void draw() override;

	const int BUFFERSIZE = 200;
	const int WIDTH = 1024;
	const int HEIGHT = 576;

	CaptureRef			mCaptureFront;
	gl::TextureRef		mTextureFront;
	gl::TextureRef		mTextureFrontBuffer;
	CaptureRef			mCaptureBack;
	gl::TextureRef		mTextureBack;

	VideoBuffer			mVBuffer1;

};

void SpoolCinderApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(1920, 1080);
}

void SpoolCinderApp::setup()
{
	mVBuffer1.init(BUFFERSIZE, WIDTH, HEIGHT);

	try {
		mCaptureFront = Capture::create(1024, 576, Capture::getDevices()[1]);
		mCaptureFront->start();
	}
	catch (ci::Exception &exc) {
		CI_LOG_EXCEPTION("Failed to init capture ", exc);
	}

	try {
		mCaptureBack = Capture::create(1024, 576, Capture::getDevices()[0]);
		mCaptureBack->start();
	}
	catch (ci::Exception &exc) {
		CI_LOG_EXCEPTION("Failed to init capture ", exc);
	}
}

void SpoolCinderApp::keyDown(KeyEvent event) {

	switch (event.getChar()) {
	case 'r':
		mVBuffer1.rec = true;
		break;
	}

}

void SpoolCinderApp::keyUp(KeyEvent event) {

	switch (event.getChar()) {
	case 'r':
		mVBuffer1.rec = false;
		break;
	}

}
void SpoolCinderApp::update()
{
	if (mCaptureFront && mCaptureFront->checkNewFrame()) {
		if (!mTextureFront) {
			// Capture images come back as top-down, and it's more efficient to keep them that way
			mTextureFront = gl::Texture::create(*mCaptureFront->getSurface(), gl::Texture::Format().loadTopDown());
		}
		else {
			mTextureFront->update(*mCaptureFront->getSurface());
		}

		if (mVBuffer1.rec) {
			mVBuffer1.recFrame(*mCaptureFront->getSurface());
		}
	}

	if (mCaptureBack && mCaptureBack->checkNewFrame()) {
		if (!mTextureBack) {
			// Capture images come back as top-down, and it's more efficient to keep them that way
			mTextureBack = gl::Texture::create(*mCaptureBack->getSurface(), gl::Texture::Format().loadTopDown());
		}
		else {
			mTextureBack->update(*mCaptureBack->getSurface());
		}
	}

	mVBuffer1.update();
}

void SpoolCinderApp::draw()
{
	gl::clear();

	if (mTextureFront) {
		gl::ScopedModelMatrix modelScope;
		gl::draw(mTextureFront, vec2(0,0));
	}
	gl::draw(gl::Texture::create(mVBuffer1.play()), vec2(0,600));
}

void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(1920, 1280);
}

CINDER_APP(SpoolCinderApp, RendererGl, prepareSettings);
