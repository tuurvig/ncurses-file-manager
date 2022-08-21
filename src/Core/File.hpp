#ifndef FILE_H
#define FILE_H

#include "HierarchyNode.hpp"
#include "Directory.hpp"

using namespace std;

/**
 * Class associates real file in hierarchy.
 * Inherits from HierarchyNode.
 */
class File : public HierarchyNode{
public:

    /**
     * Constructor of file.
     * @param name Name of node.
     * @param size Size of file.
     * @param parent Parent directory pointer.
     */
    File( const string & name, size_t size, Directory * parent );

    /**
     * Renames file.
     * @param name New name for the file.
     * @return Boolean to describe if rename operation was successful.
     */
    bool Rename( const string & name ) override;

    /**
     * Copies file to an another directory.
     * @param path Absolute path to where the file will be copied.
     * @return Boolean to describe if copy operation was successful.
     */
    bool Copy( const string & path ) override;

    /**
     * Erases file.
     * @return Boolean to describe if erase operation was successful.
     */
    bool Erase() override;

    /**
     * Moves file to an another directory by using copy and erase.
     * @param path Absolute path to where the file will be moved.
     * @return Boolean to describe if move operation was successful.
     */
    bool Move( const string & path ) override;

    /**
     * Shows how will be file presented in user interface.
     * @return String with ' ' prefix in front of directory name.
     */
    string Show( int width ) const override;

    /**
     * Size getter
     * @return size of file in bytes.
     */
    size_t Size() const;
private:
    /**
     * File's size.
     */
    size_t _size;
};

#endif /* FILE_H */