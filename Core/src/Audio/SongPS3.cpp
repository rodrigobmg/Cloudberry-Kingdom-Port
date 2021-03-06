#include <Audio/Song.h>

#include <Audio/PS3/mscommon.h>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "SongInternalPS3.h"

float GetMP3Length( const std::string &path )
{
	long size;

	int handle = OpenFile( path.c_str(), &size );

	if( handle < 0 )
	{
		LOG_WRITE( "Couldn't get length: %s\n", path.c_str() );
		return 0.f;
	}

	LOG_WRITE( "Buffer %d bytes\n", size );
	long buffer = reinterpret_cast< long >( memalign( 128, size ) );
	long data = buffer;

	LoadFile( handle, data, size, 0, 0 );

	unsigned int tSize = 0;
	float time = 0.f;
	unsigned int offset = 0;

	while( true )
	{
		CellMSMP3FrameHeader hdr;

		int ret = cellMSMP3GetFrameInfo( reinterpret_cast< void * >( data ), &hdr );
		if( ret == -1 )
		{
			LOG_WRITE( "Invalid MP3 header\n" );
			time = 0.f;
			break;
		}

		tSize += hdr.PacketSize;
		if( hdr.ID3 == 0 && hdr.Tag == 0 )
			time += hdr.PacketTime;
		data += hdr.PacketSize;
		offset += hdr.PacketSize;
		
		if( tSize == size )
		{
			LOG_WRITE( "MP3 loaded\n" );
			LOG_WRITE( "Playback time at %d Hz: %f s\n", hdr.Frequency, time );
			break;
		}
		else if( tSize > size )
		{
			LOG_WRITE( "Passed the end of file!\n ");
			time = 0.f;
			break;
		}
	}

	free( reinterpret_cast< void * >( buffer ) );
	cellFsClose( handle );

	return time;
}

Song::Song() :
	internal_( new SongInternal )
{
	Duration.TotalSeconds = 0.f;
}

Song::~Song() 
{
	delete internal_;
}

extern std::string PS3_PATH_PREFIX;

void Song::Load( const std::string &path )
{
	internal_->Path = PS3_PATH_PREFIX + "ContentPS3/" + path;
	Duration.TotalSeconds = GetMP3Length( internal_->Path );
}
