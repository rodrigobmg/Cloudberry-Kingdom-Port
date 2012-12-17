#include <global_header.h>

#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>

#include "ContentManager.h"
#include "GraphicsDevice.h"

#include <Hacks/String.h>

template<> boost::shared_ptr<SoundEffect> ContentManager::Load<SoundEffect>( const std::wstring &name )
{
	return boost::make_shared<SoundEffect>();
}

template<> boost::shared_ptr<Song> ContentManager::Load<Song>( const std::wstring &name )
{
	return boost::make_shared<Song>();
}

template<> boost::shared_ptr<Texture2D> ContentManager::Load<Texture2D>( const std::wstring &name )
{
	boost::shared_ptr<Texture2D> t2d = boost::make_shared<Texture2D>(boost::shared_ptr<GraphicsDevice>(), 1, 1);
	
#if defined(DEBUG)
	// WARNING: Fast load
	//t2d->texture_ = CONTENT->Load<Texture>( "Content/Art/default.png" );
	t2d->texture_ = CONTENT->Load<Texture>( WstringToUtf8( name ) + ".png" );
#else
	t2d->texture_ = CONTENT->Load<Texture>( WstringToUtf8( name ) + ".png" );
#endif

	return t2d;
}

template<> boost::shared_ptr<SpriteFont> ContentManager::Load<SpriteFont>( const std::wstring &name )
{
	return boost::make_shared<SpriteFont>();
}

template<> boost::shared_ptr<Effect> ContentManager::Load<Effect>( const std::wstring &name )
{
	boost::shared_ptr<Effect> effect = boost::make_shared<Effect>();
	effect->Load( WstringToUtf8( name ) );
	return effect;
}

