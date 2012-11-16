#ifndef LEVELCONNECTOR
#define LEVELCONNECTOR

#include <string>

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Door;
}


namespace CloudberryKingdom
{
	/// <summary>
	/// A singleton class to store data about LevelConnectors.
	/// </summary>
	class LevelConnector
	{
		/// <summary> The object core string code for an end of level object level connector. </summary>
	public:
		static std::wstring EndOfLevelCode;

		/// <summary> The object core string code for a start of level object level connector. </summary>
		static std::wstring StartOfLevelCode;
	};

	/// <summary>
	/// Implemented by IObjects that connect levels together.
	/// </summary>
	class ILevelConnector
	{
	public:
		virtual const std::shared_ptr<LevelSeedData> &getNextLevelSeedData() const = 0;
		virtual void setNextLevelSeedData( const std::shared_ptr<LevelSeedData> &value ) = 0;
		virtual const std::shared_ptr<Lambda_1<Door*> > &getOnOpen() const = 0;
		virtual void setOnOpen( const std::shared_ptr<Lambda_1<Door*> > &value ) = 0;
		virtual const std::shared_ptr<Lambda_1<Door*> > &getOnEnter() const = 0;
		virtual void setOnEnter( const std::shared_ptr<Lambda_1<Door*> > &value ) = 0;
	};
}


#endif	//#ifndef LEVELCONNECTOR