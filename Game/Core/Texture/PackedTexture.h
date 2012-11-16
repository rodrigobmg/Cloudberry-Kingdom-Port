﻿#ifndef PACKEDTEXTURE
#define PACKEDTEXTURE

#include <string>
#include <vector>

namespace CloudberryKingdom
{
	class EzTexture;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	class PackedTexture
	{
	public:
		class SubTexture
		{
		public:
			std::wstring name;
			Vector2 BL, TR;
		};

	public:
		std::shared_ptr<EzTexture> MyTexture;

		/// <summary>
		/// The subtextures held inside this PackedTexture.
		/// </summary>
		std::vector<SubTexture> SubTextures;

		PackedTexture( const std::wstring &name );

		void Add( const std::wstring &name, float x1, float y1, float x2, float y2 );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PACKEDTEXTURE