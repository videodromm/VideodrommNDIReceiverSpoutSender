
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/GeomIo.h"
#include "cinder/CameraUi.h"
#include "cinder/Camera.h"

#include "CiSpoutOut.h"
#include "CinderNDIReceiver.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VideodrommNDIReceiverSpoutSenderApp : public App {
public:
	VideodrommNDIReceiverSpoutSenderApp();
	void update() override;
	void draw() override;

	SpoutOut mSpoutOut;
private:
	CinderNDIReceiver mReceiver;
};

VideodrommNDIReceiverSpoutSenderApp::VideodrommNDIReceiverSpoutSenderApp()
	: mReceiver{}
	, mSpoutOut("NDIReceiver", app::getWindowSize())
{
	
}

void VideodrommNDIReceiverSpoutSenderApp::update()
{
	mReceiver.update();
	getWindow()->setTitle("Videodromm NDI-Receiver Spout-Sender - " + std::to_string((int)getAverageFps()) + " FPS");

}

void VideodrommNDIReceiverSpoutSenderApp::draw()
{
	gl::clear(Color(0, 0, 0));
	auto meta = mReceiver.getMetadata();
	auto tex = mReceiver.getVideoTexture();
	if (tex.first) {
		Rectf centeredRect = Rectf(tex.first->getBounds()).getCenteredFit(getWindowBounds(), true);
		gl::draw(tex.first, centeredRect);
	}
	CI_LOG_I(" Frame: " << tex.second << ", metadata: " << meta.first << " : " << meta.second);


	mSpoutOut.sendViewport();
}

void prepareSettings(VideodrommNDIReceiverSpoutSenderApp::Settings* settings)
{
	settings->setWindowSize(640, 480);
}

CINDER_APP(VideodrommNDIReceiverSpoutSenderApp, RendererGl, prepareSettings)

