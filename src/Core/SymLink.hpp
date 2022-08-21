#ifndef SYMLINK_H
#define SYMLINK_H

#include "HierarchyNode.hpp"
#include "Directory.hpp"

using namespace std;

/**
 * Class associates real symbolic link in hierarchy.
 * Inherits from HierarchyNode.
 */
class SymLink : public HierarchyNode{
public:

    /**
     * Constructor of symbolic link
     * @param name Name of node.
     * @param link Absolute path to linked node.
     * @param parent Pointer to a parent directory.
     */
    SymLink( const string & name, const string & path, Directory * parent );

    /**
     * Renames symbolic link.
     * @param name New name for node to be replaced.
     * @return Boolean to describe if rename operation was successful.
     */
    bool Rename( const string & name ) override;

    /**
     * Copies symbolic link to an another directory.
     * @param path Absolute path to where symbolic link will be copied.
     * @return Boolean to describe if copy operation was successful.
     */
    bool Copy( const string & path ) override;

    /**
     * Erases symbolic link.
     * @return Boolean to describe if erase operation was successful.
     */
    bool Erase() override;

    /**
     * Moves symbolic link to an another directory by using copy and erase.
     * @param path Absolute path to where symbolic link will be moved.
     * @return Boolean to describe if move operation was successful.
     */
    bool Move( const string & path ) override;

    /**
     * Shows how will be symbolic link presented in user interface.
     * @return String with '@' prefix in front of directory name.
     */
    string Show( int width ) const override;

    /**
     * Link getter.
     * @return Reference to an absolute path to link.
     */
    const string & GetLink() const;
private:
    /**
     * String that holds absolute path to a file.
     */
    string _link;
};

#endif /* SYMLINK_H */