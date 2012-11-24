#ifndef PIECESEEDDATA
#define PIECESEEDDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceSeedData
	{
		/// <summary>
		/// Uses the upgrade data inMyUpgrades1 to calculate the level gen data.
		/// </summary>
	public:
		void CalculateSimple();

		std::shared_ptr<Lambda_1<Level*> > PreStage1, PreStage2;

		std::shared_ptr<AutoGen_Parameters> operator []( const std::shared_ptr<AutoGen> &gen );

		/// <summary>
		/// Type of level to be made, relating to shape and direction. Different from the GameType.
		/// </summary>
		LevelGeometry GeometryType;

		/// <summary>
		/// Type of level to be made, relating to the camera zoom.
		/// </summary>
		LevelZoom ZoomType;

		float ExtraBlockLength;

		std::shared_ptr<StyleData> Style;

		std::shared_ptr<RichLevelGenData> MyGenData;
		std::shared_ptr<Upgrades> MyUpgrades1, MyUpgrades2;

		const std::shared_ptr<Upgrades> &getu() const;

		Vector2 Start, End;
		Vector2 CamZoneStartAdd, CamZoneEndAdd;

		int Paths;
		bool LockNumOfPaths;

		LadderType Ladder;
		BoxStyle ElevatorBoxStyle;

		std::shared_ptr<PieceSeedData> PieceSeed; // Used if this is a platform used for making new platforms

		bool CheckpointsAtStart, InitialCheckpointsHere;

		int MyPieceIndex;

		void Release();

		void CopyFrom( const std::shared_ptr<PieceSeedData> &piece );

		void CopyUpgrades( const std::shared_ptr<PieceSeedData> &piece );

		void CalcBounds();

		void StandardClose();

	private:
		std::shared_ptr<LevelSeedData> MyLevelSeed;
	public:
		const std::shared_ptr<Rand> &getRnd() const;

		PieceSeedData( const std::shared_ptr<LevelSeedData> &LevelSeed );

		PieceSeedData( int Index, LevelGeometry Type, const std::shared_ptr<LevelSeedData> &LevelSeed );

	private:
		void Init( LevelGeometry Type );


	public:
		void NoBlobs();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PIECESEEDDATA
