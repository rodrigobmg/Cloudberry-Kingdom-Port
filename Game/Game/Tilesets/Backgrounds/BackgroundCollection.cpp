#include <small_header.h>
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"

#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Collision Detection/FloatRectangle.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Tools.h"


#include "Hacks/Queue.h"

#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"

namespace CloudberryKingdom
{

	BackgroundCollection::BackgroundCollection( const boost::shared_ptr<Level> &level )
	{
		MyLevel = level;

		//Lists = std::vector<boost::shared_ptr<BackgroundFloaterList> >();
	}

	void BackgroundCollection::Release()
	{
		MyLevel.reset();

		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Release();
	}

	void BackgroundCollection::Reset()
	{
		if ( Lists.empty() )
			return;

		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Reset();
	}

	void BackgroundCollection::SetLevel( const boost::shared_ptr<Level> &level )
	{
		MyLevel = level;

		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetLevel( level );
	}

	void BackgroundCollection::SetBackground( const boost::shared_ptr<Background> &b )
	{
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetBackground( b );
	}

	void BackgroundCollection::Move( Vector2 shift )
	{
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Move( shift );
	}

	void BackgroundCollection::Clear()
	{
		Clear( boost::make_shared<FloatRectangle>( Vector2(), Vector2( 100000000 ) ) );
	}

	void BackgroundCollection::Clear( const boost::shared_ptr<FloatRectangle> &Area )
	{
		for ( size_t i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Clear( Area );
	}

	void BackgroundCollection::Absorb( const boost::shared_ptr<BackgroundCollection> &collection )
	{
		for ( size_t i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Absorb( collection->Lists[ i ] );
	}

	void BackgroundCollection::DrawLayer( int Layer )
	{
		if ( Layer < static_cast<int>( Lists.size() ) )
			Lists[ Layer ]->Draw();
	}

	void BackgroundCollection::FinishDraw()
	{
		Tools::QDrawer->Flush();

		boost::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();
		//Vector4 cameraPos = new Vector4(Cam.Data.Position.X, Cam.Data.Position.Y, Cam.Zoom.X, Cam.Zoom.Y);
		//Tools::EffectWad.SetCameraPosition(cameraPos);
	}

	void BackgroundCollection::Draw()
	{
		Draw( 1, false );
	}

	void BackgroundCollection::Draw( float CamMod, bool Foreground )
	{
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			if ( ( *list )->Foreground == Foreground )
				( *list )->Draw( CamMod );

		FinishDraw();
	}

	void BackgroundCollection::PhsxStep()
	{
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->PhsxStep();
	}

}
