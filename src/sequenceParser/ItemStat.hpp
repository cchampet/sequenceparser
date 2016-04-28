#ifndef _SEQUENCE_PARSER_ITEMSTAT_HPP_
#define _SEQUENCE_PARSER_ITEMSTAT_HPP_

#include "common.hpp"
#include "Item.hpp"
#include "system.hpp"

#ifdef __UNIX__
    #include <sys/types.h>
#endif


namespace sequenceParser {

class ItemStat
{
public:
	ItemStat( const Item& item, const bool approximative=true );
	ItemStat( const EType& type, const boost::filesystem::path& path, const bool approximative=true );

	std::string getUserName() const;
	std::string getGroupName() const;

private:
	void statFolder( const boost::filesystem::path& path );
	void statFile( const boost::filesystem::path& path );
	void statSequence( const Item& item, const bool approximative );
	void statLink( const boost::filesystem::path& path );
	void setDefaultValues();
#ifdef __UNIX__
	void setPermissions( const mode_t& protection );
#endif

public:
	// See the following doc to get file status on UNIX system
	// See http://linux.die.net/man/2/stat
	long long deviceId; /// ID of device containing file
	unsigned int inodeId; /// inode number
	double nbHardLinks; /// number of hard links
	long long fullNbHardLinks; /// total number of hard links in a sequence (otherwise, same value as nbHardLinks)
	long long userId; /// user ID of owner
	long long groupId; /// group ID of owner

	long long size; /// total size, in bytes
	long long minSize; /// size of the smallest file in the sequence (otherwise, same value as size)
	long long maxSize; /// size of the biggest file in the sequence (otherwise, same value as size)
	long long realSize; /// size (takes hardlinks into account)
	long long sizeOnDisk; /// size on hard-drive (takes hardlinks into account)

	long long accessTime; /// time of last access
	long long modificationTime; /// time of last modification
	/**
	 * @brief Time of last status change
	 * @note In case of rsync command with preserve times, 
	 * the modification time is the same as remote file and the lastChangeTime is the local time 
	 */
	long long lastChangeTime;

	// permissions
	bool ownerCanRead;
	bool ownerCanWrite;
	bool ownerCanExecute;
	bool groupCanRead;
	bool groupCanWrite;
	bool groupCanExecute;
	bool otherCanRead;
	bool otherCanWrite;
	bool otherCanExecute;
};

}

#endif
