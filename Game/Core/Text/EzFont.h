﻿#ifndef EZFONT
#define EZFONT

#include <global_header.h>

#include "Hacks/XNA/SpriteFont.h"

namespace CloudberryKingdom
{
	struct EzFont
	{
	
		std::shared_ptr<SpriteFont> Font, OutlineFont;
		float CharacterSpacing;
		int LineSpacing;

		EzFont( const std::wstring &FontName );

		EzFont( const std::wstring &FontName, float CharacterSpacing, int LineSpacing );

		EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );

		EzFont( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, float LineSpacingMod );

		void FixFont();

	
		void Initialize( const std::wstring &FontName, const std::wstring &OutlineFontName, float CharacterSpacing, int LineSpacing );
	};
}


#endif	//#ifndef EZFONT
