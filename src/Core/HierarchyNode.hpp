#ifndef HIERARCHY_NODE_H
#define HIERARCHY_NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

class Directory;
/**
 * Abstract class to File, Directory and Symlink.
 */
class HierarchyNode{
public:

    /**
     * Created node.
     * @param name Name of a node.
     * @param parent Pointer to a parent directory.
     */
    explicit HierarchyNode( const string & name, Directory * parent );

    /**
     * Default destructor of node.
     */
    virtual ~HierarchyNode() = default;

    /**
     * Renames this node.
     * @param name Renames old name with new one.
     * @return Boolean to describe if rename operation was successful.
     */
    virtual bool Rename( const string & name ) = 0;

    /**
     * Copies node.
     * @param path Path to where node will be copied.
     * @return Boolean to describe if copy operation was successful.
     */
    virtual bool Copy( const string & path ) = 0;

    /**
     * Erases node.
     * @return Boolean to describe if erase operation was successful.
     */
    virtual bool Erase() = 0;

    /**
     * Moves node.
     * @param path Path to where node will be moved.
     * @return Boolean to describe if move operation was successful.
     */
    virtual bool Move( const string & path ) = 0;

    /**
     * Getter to a nodes name.
     * @return Name of a node.
     */
    virtual inline const string & GetName() const{
       return _name;
    }

    /**
     * @return Name to compare.
     */
    virtual inline string Compare() const{
        return _name;
    }
    /**
     * Virtual function that tells us if node is a directory.
     * @return False by default. Overridden in class Directory so it can return true.
     */
    virtual inline bool IsDIR() const{
       return false;
    }

    /**
     * Virtual method that shows how nodes will be visually distinguishable in user interface.
     * @return String with updated node name.
     */
    virtual string Show( int width ) const = 0;
protected:
    /**
     * Method uses <cstdlib> function realpath() that returns canonical path without using /. or /..
     * Allocates buffer by size PATH_MAX.
     * @param path Original path that is about to be converted.
     * @return String with desired absolute path, but if realpath() fails then the return string will be empty.
     */
    string GetAbsolutePath( const string & path ) const;

    /**
     * Nodes name.
     */
    string _name;

    /**
     * Constant pointer to parent directory.
     */
    const Directory * _parent;
};

#endif /* HIERARCHY_NODE_H */
