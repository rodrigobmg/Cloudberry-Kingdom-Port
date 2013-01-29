#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

#include <boost/shared_ptr.hpp>

// Forward declarations.
class Texture2D;
class Video;
struct VideoPlayerInternal;

struct VideoPlayer
{

	VideoPlayerInternal *internal_;

public:

	bool IsLooped;

	VideoPlayer();
	~VideoPlayer();

	void Play( const boost::shared_ptr< Video > &video );

	boost::shared_ptr< Texture2D > GetTexture();

};

#endif
