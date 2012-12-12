/**
 * @file
 *
 * Cross platform file.
 */
#ifndef _FILE_H_
#define _FILE_H_

#include <string>

/**
 * File IO interface.
 */
class File
{

public:

	virtual ~File() { }

	/// Read data from file.
	/**
	 * @param buffer Output buffer.
	 * @param length Number of bytes to read.
	 * @return Number of bytes that were read.
	 */
	virtual size_t Read( char *buffer, size_t length ) = 0;

	/// Peek a character.
	virtual int Peek() = 0;

	/// Is the file open?
	virtual bool IsOpen() = 0;

	/// Have we reached the end of file?
	virtual bool IsEOF() = 0;

	/// Read a file into a string.
	/**
	 * @param path Path to file.
	 * @param[out] str Output string.
	 * @return True on success and false on failure.
	 */
	static bool ReadAsString( const std::string &path, std::string &str );

};

#endif
