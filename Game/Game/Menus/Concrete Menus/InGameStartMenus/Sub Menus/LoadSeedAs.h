#ifndef LOADSEEDAS
#define LOADSEEDAS

#include "../Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Core/Lambdas/Lambda_1.h"
#include <string>
#include <tchar.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class GUI_TextBox;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

namespace CloudberryKingdom
{
	class LoadSeedAs : public VerifyBaseMenu
	{
	private:
		class LoadSeedAsOnEnterLambda : public Lambda
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;
		public:
			LoadSeedAsOnEnterLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	private:
		class LoadSeedAsBackLambda : public Lambda
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;
		public:
			LoadSeedAsBackLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	private:
		class LoadProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;

		public:
			LoadProxy1( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	public:
		LoadSeedAs( int Control, const std::shared_ptr<PlayerData> &Player );

	private:
		std::shared_ptr<PlayerData> Player;
		std::shared_ptr<GUI_TextBox> TextBox;
		std::shared_ptr<EzText> HeaderText;
	public:
		virtual void Init();

		virtual void Release();

	private:
		void SetPosition();

	public:
		virtual void OnAdd();

	private:
		void Load( const std::shared_ptr<MenuItem> &_item );
	};
}


#endif	//#ifndef LOADSEEDAS