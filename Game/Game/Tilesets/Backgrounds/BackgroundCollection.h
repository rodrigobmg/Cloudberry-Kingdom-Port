﻿#ifndef BACKGROUNDCOLLECTION
#define BACKGROUNDCOLLECTION

#include <global_header.h>

namespace CloudberryKingdom
{
	class BackgroundCollection
	{
	public:
		std::shared_ptr<Level> MyLevel;

		std::vector<BackgroundFloaterList*> Lists;

		BackgroundCollection( const std::shared_ptr<Level> &level );

		void Release();

		/// <summary>
		/// Reset the lists to their start position.
		/// </summary>
		void Reset();

		void SetLevel( const std::shared_ptr<Level> &level );

		void SetBackground( const std::shared_ptr<Background> &b );

		void Move( Vector2 shift );

		void Clear();
		void Clear( const std::shared_ptr<FloatRectangle> &Area );

		void Absorb( const std::shared_ptr<BackgroundCollection> &collection );

		void DrawLayer( int Layer );

		void FinishDraw();

		void Draw();
		void Draw( float CamMod, bool Foreground );

		void PhsxStep();
	};
}


#endif	//#ifndef BACKGROUNDCOLLECTION
