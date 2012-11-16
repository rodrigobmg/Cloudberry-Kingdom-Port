﻿#ifndef SPRITEANIM
#define SPRITEANIM

#include <unordered_map>
#include <cmath>

namespace CloudberryKingdom
{
	class SpriteAnim;
}

namespace CloudberryKingdom
{
	class Lambda_2;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class Texture2D;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	/// <summary>
	/// Should be replaced. Right now this is used for drawing the players in the replays, but replays should instead be reusing the same draw code for the player as the normal draw code.
	/// </summary>
	class SpriteAnimGroup
	{
	public:
		std::unordered_map<int, SpriteAnim*> SpriteAnims;

		void Release();

		SpriteAnimGroup();

		void Init( const std::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding, const std::shared_ptr<CloudberryKingdom::Lambda_2<std::unordered_map<int, SpriteAnim*>, Vector2> > &SpriteFunc );

		std::shared_ptr<Texture2D> Get( int anim, float t, Vector2 &padding );
	};

	class SpriteAnim
	{
	public:
		float dt;
		std::vector<Texture2D*> Frames;
		Vector2 Padding;

		void Release();
	};
}


#endif	//#ifndef SPRITEANIM