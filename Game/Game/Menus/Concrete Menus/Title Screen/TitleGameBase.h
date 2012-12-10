﻿#ifndef TITLEGAMEBASE
#define TITLEGAMEBASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class TitleFactory : public GameFactory
	{
	public:
		virtual std::shared_ptr<GameData> Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	class TitleGameData : public GameData
	{

	public:
		static void InitializeStatics();

	public:
		static std::shared_ptr<GameFactory> Factory;

		virtual void Release();

		TitleGameData();

		virtual void SetToReturnTo( int code );

		virtual void ReturnTo( int code );

	protected:
		std::shared_ptr<CameraZone> CamZone;
		virtual std::shared_ptr<Level> MakeLevel();

	public:
		virtual void Init();

		virtual void AdditionalReset();

		bool PanCamera;
	protected:
		float PanAcc;
		float PanMaxSpeed;
		float PanMaxDist;
		float PanMinDist;

	public:
		virtual void PhsxStep();

		virtual void PostDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TITLEGAMEBASE
