#ifndef _SONG_H_
#define _SONG_H_

struct Song
{

	struct
	{
		double TotalSeconds;
	} Duration;

	Song()
	{
		Duration.TotalSeconds = 0;
	}

};

#endif
