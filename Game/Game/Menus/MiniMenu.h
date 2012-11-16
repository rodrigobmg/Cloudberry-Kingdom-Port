﻿#ifndef MINIMENU
#define MINIMENU

#include "Menu.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MiniMenu : public Menu
	{
	public:
		int ItemsToShow;
	private:
		int TopItem;
		const int &getBottomItem() const;
		void setBottomItem( const int &value );

	public:
		MiniMenu();

		virtual void SelectItem( int Index );

		virtual void PhsxStep();

		Vector2 Shift;
		virtual void DrawText( int Layer );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MINIMENU