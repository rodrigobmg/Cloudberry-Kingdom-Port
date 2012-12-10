#ifndef SCOREDATABASE
#define SCOREDATABASE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ScoreDatabase : public SaveLoad
	{

	
		static void InitializeStatics();

	
		static std::shared_ptr<ScoreDatabase> Instance;

	
		static int MostRecentScoreDate;
		static int CurrentDate();

		static int Capacity;

	
		static std::map<int, std::vector<std::shared_ptr<ScoreEntry> > > Games;

	
		static void Initialize();

		#pragma region SaveLoad
	
		virtual void Serialize( const std::shared_ptr<BinaryWriter> &writer );
		virtual void FailLoad();
		virtual void Deserialize( std::vector<unsigned char> Data );
		#pragma endregion

	
		static void EnsureList( int Game );

		static std::shared_ptr<ScoreList> GetList( int Game );

		/// <summary>
		/// Whether the given score qualifies for the high score list
		/// </summary>
		static bool Qualifies( int Game, int Score );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
	
		static std::shared_ptr<ScoreEntry> Max( std::vector<std::shared_ptr<ScoreEntry> > &Scores );

	
		static std::shared_ptr<ScoreEntry> Max( int GameId );

		/// <summary>
		/// Return the score with the smallest value.
		/// </summary>
		static std::shared_ptr<ScoreEntry> Min( std::vector<std::shared_ptr<ScoreEntry> > &Scores );

		static std::shared_ptr<ScoreEntry> Min( int GameId );

		static void Add( const std::shared_ptr<ScoreEntry> &score );

		/// <summary>
		/// Remove excess entries, if the list is over capacity.
		/// </summary>
	
		static void TrimExcess( std::vector<std::shared_ptr<ScoreEntry> > &Scores );

		static int ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 );

		static bool ScoreCompareStrictWeak( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 );

		/// <summary>
		/// Sort the list by value.
		/// </summary>
		static void Sort( std::vector<std::shared_ptr<ScoreEntry> > &Scores );
	};
}


#endif	//#ifndef SCOREDATABASE
