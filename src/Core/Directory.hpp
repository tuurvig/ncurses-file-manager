#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>

#include "HierarchyNode.hpp"
#include "File.hpp"
#include "SymLink.hpp"

using namespace std;

/**
 * Class associates real directory in hierarchy.
 * Inherits from HierarchyNode.
 */
class Directory : public HierarchyNode{
public:

    /**
     * Default constructor that initializes root directory.
     */
    Directory();

    /**
     * Constructor of Directory class. Contents are empty. Needs to be initialized by LoadContents().
     * @param name Absolute path to a directory. Member of parent class.
     */
    Directory( const string & name, const string & path, Directory * parent );

    /**
     * Creates new directory
     * @param name New directory name.
     * @return Boolean to describe if creating operation was successful.
     */
    bool CreateDir( const string & name );
    
    /**
     * Creates new file
     * @param name New file name.
     * @return Boolean to describe if creating operation was successful.
     */
    bool CreateFile( const string & name );
    
    /**
     * Creates new symbolic link
     * @param name New link name.
     * @param path Path to a node where it's linked.
     * @return Boolean to describe if creating operation was successful.
     */
    bool CreateLink( const string & name, const string & path );
    
    /**
     * Renames directory
     * @param name New name for a directory.
     * @return Boolean to describe if rename operation was successful.
     */
    bool Rename( const string & name ) override;

    /**
     * Copies directory.
     * @param path Absolute path to where copy of this directory will be created.
     * @return Boolean to describe if copy operation was successful.
     */
    bool Copy( const string & path ) override;

    /**
     * Erases directory.
     * @return Boolean to describe if erase operation was successful.
     */
    bool Erase() override;

    /**
     * Moves directory by copying and erasing directory.
     * @param path Absolute path to where the directory will be moved.
     * @return Boolean to describe if move operation was successful.
     */
    bool Move( const string & path ) override;

    /**
     * @return String to be compared.
     */
    inline string Compare() const override{
        return ' ' + _name;
    }
    /**
     * Shows how directory name will be presented in user interface.
     * Cuts the original length to fit it into width.
     * @param width Max width to where string must fit.
     * @return String with '/' prefix in front of directory name.
     */
    string Show( int width ) const override;

    /**
     * Shows how directory path will be presented in user interface.
     * Cuts the original length to fit it into width.
     * @param width Max width to where string must fit.
     * @return Absolute path to directory.
     */
    string ShowPath( int width ) const;

    /**
     * Removes node from _contents.
     * @param index Nodes index.
     */
    void RemoveNode( unsigned index );
    
    /**
     * @return iterator to the beginning of the directory contents.
     */
    inline vector< unique_ptr< HierarchyNode > >::iterator const begin(){
       return _contents.begin();
    }

    /**
     * @return iterator to the end of the directory contents.
     */
    inline vector< unique_ptr< HierarchyNode > >::iterator const end(){
       return _contents.end();
    }

    /**
     * Loads the directory contents.
     */
    bool LoadContents();

    /**
     * Asks if object is Directory.
     * @return True
     */
    inline bool IsDIR() const override{
       return true;
    }
    
    /**
     * Toggles Directory functionality of showing hidden folders.
     */
    inline void ToggleHidden(){
       _showHidden = !_showHidden;
    }

    /**
     * @return Number of nodes in directory.
     */
    inline size_t NodeCount() const{
       return _contents.size();
    }

    /**
     * Get path of a directory.
     * @return string reference to a path.
     */
    const string & Path() const;
private:
    /**
     * Directory absolute path.
     */
    string _path;

    /**
     * Determines if it will show hidden folders.
     */
    bool _showHidden;

    /**
     * Vector of nodes.
     */
    vector< unique_ptr< HierarchyNode > > _contents;

    /**
     * Appends node into its rightful place in _contents, by using lower_bound and compare function.
     * @param buffer info about node.
     * @param name nodes name.
     * @param path nodes path.
     */
    void Append( const struct stat & buffer, const string & name, const string & path );

    /**
     * Method that compares names of nodes.
     * @param lhs unique_ptr of HierarchyNode
     * @param rhs unique_ptr of HierarchyNode
     * @return boolean if string of lhs is less than rhs
     */
    struct __compareNames{
        bool operator()( const unique_ptr< HierarchyNode > &lhs, const unique_ptr< HierarchyNode > &rhs );
    } CompareNames;
};

#endif /* DIRECTORY_H */
