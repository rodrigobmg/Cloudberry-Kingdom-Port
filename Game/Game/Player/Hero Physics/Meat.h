﻿#ifndef MEAT
#define MEAT

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxMeat : public BobPhsxNormal
	{

	public:
		static void InitializeStatics();

	public:
		virtual void Release();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static std::shared_ptr<BobPhsxMeat> instance;
	public:
		const static std::shared_ptr<BobPhsxMeat> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxMeat> &bob );

		// Instancable class
		BobPhsxMeat();

		virtual void Init( const std::shared_ptr<Bob> &bob );

	private:
		bool LastJumpWasSticky;
	public:
		int StepsSinceSide, StepsOnSide;
		int StickyDuration;
	private:
		ColType StickySide;
		std::shared_ptr<BlockBase> LastStickyBlock;
		bool IsStuck;
	public:
		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

	private:
		bool CanWallJump;
	public:
		int WallJumpCount;
	private:
		int StickyGracePeriod;
	public:
		float Max_yVel_ForWallJump;

	private:
		int SideJumpLength;
		float SideJumpStr;

	public:
		virtual void Jump();

	private:
		float SideToDir( ColType side );

		float getStickyDir();

	public:
		virtual void PhsxStep();

		virtual void DoXAccel();

		virtual float GetXAccel();

	protected:
		virtual void DoJump();

	public:
		virtual bool ShouldStartJumpAnim();

	protected:
		virtual void SetTarget( const std::shared_ptr<RichLevelGenData> &GenData );

	private:
		Vector2 PrefferedDir;
		void NewTarget();

	public:
		bool WantToLandOnTop;
	private:
		Vector2 Target;
		Vector2 AlwaysForward;
		int StraightUpDuration;
		float yVelCutoff;
	public:
		virtual void GenerateInput( int CurPhsxStep );

		virtual bool IsTopCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual bool IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MEAT
