#ifndef WRITEREADTOOLS
#define WRITEREADTOOLS

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Animation/AnimationData_Vector.h"
//#include "Core/Graphics/VertexFormat.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Tools/Tools.h"


#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{
	struct WriteReadTools
	{
	
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static Vector2 ReadVector2(this BinaryReader reader)
		static Vector2 ReadVector2( const boost::shared_ptr<BinaryReader> &reader );

		/// <summary>
		/// Writes the index, ensuring non-negativity.
		/// </summary>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void WriteSafeIndex(this BinaryWriter writer, int index)
		static void WriteSafeIndex( const boost::shared_ptr<BinaryWriter> &writer, int index );

//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void Write(this BinaryWriter writer, Vector2 v)
		static void Write( const boost::shared_ptr<BinaryWriter> &writer, Vector2 v );

		static void WriteOneAnim( const boost::shared_ptr<BinaryWriter> &writer, OneAnim anim );

		static void ReadOneAnim( const boost::shared_ptr<BinaryReader> &reader, OneAnim &anim );

		static void WriteOneAnim( const boost::shared_ptr<BinaryWriter> &writer, OneAnim_Texture anim );

		static void ReadOneAnim( const boost::shared_ptr<BinaryReader> &reader, OneAnim_Texture &anim );


		static void WriteVector2( const boost::shared_ptr<BinaryWriter> &writer, Vector2 vec );

		static void ReadVector3( const boost::shared_ptr<BinaryReader> &reader, Vector3 &vec );

		static void WriteVector3( const boost::shared_ptr<BinaryWriter> &writer, Vector3 vec );

		static void ReadVector2( const boost::shared_ptr<BinaryReader> &reader, Vector2 &vec );

		static void WriteColor( const boost::shared_ptr<BinaryWriter> &writer, Color clr );

		static void ReadColor( const boost::shared_ptr<BinaryReader> &reader, Color &clr );

		static void WriteVertex( const boost::shared_ptr<BinaryWriter> &writer, MyOwnVertexFormat ver );

		static void ReadVertex( const boost::shared_ptr<BinaryReader> &reader, MyOwnVertexFormat &ver );

		static void WritePhsxData( const boost::shared_ptr<BinaryWriter> &writer, PhsxData data );

		static void ReadPhsxData( const boost::shared_ptr<BinaryReader> &reader, PhsxData &data );
	};
}


#endif	//#ifndef WRITEREADTOOLS
