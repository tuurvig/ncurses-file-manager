#include <vector>
#include <list>
#include <memory>
#include <algorithm>

#include "Directory.hpp"

using namespace std;

/**
 * Navigates through directories and memorizes the path it took.
 * Only permitting to use the last added directory.
 */
class DirNavigation{
public:

    /**
     * Constructor of directory navigator.
     * @param root Pointer to start directory, which will be added
     * as a first member of list _nav.
     */
    explicit DirNavigation( Directory * root );

    /**
     * Copying constructor
     * @param x Reference to an existing DirNavigation instance.
     */
    DirNavigation( const DirNavigation &x ) = default;

    /**
     * Default destructor.
     */
    ~DirNavigation() = default;

    /**
     * Default operator=
     * @param x Reference to an existing DirNavigation instance.
     * @return itself
     */
    DirNavigation & operator=( const DirNavigation &x ) = default;

    /**
     * Takes a step deeper in directory hierarchy by pushing back another Directory pointer
     * to the _nav list. The new dir will be used for iterating through nodes.
     * @param dir directory vector iterator to directory node.
     */
    void Push( Directory * dir );

    /**
     * Moves back in directory hierarchy. Pops last item in _nav list
     * and makes the previous one the current one.
     * @return last Directory pointer in the list.
     */
    Directory * & Pop();

    /**
     * @return iterator to the first node of the last Directory pointer in the list.
     */
    inline vector< unique_ptr< HierarchyNode > >::iterator begin() const{
       return _nav.back()->begin();
    }

    /**
     * @return iterator to the end of vector of the last Directory pointer in the list.
     */
    inline vector< unique_ptr< HierarchyNode > >::iterator end() const{
       return _nav.back()->end();
    }

    /**
     * Overloaded operator-> to directly access current Directory.
     * @return pointer to a Directory
     */
    inline Directory * operator->() const{
       return _nav.back();
    }

    /**
     * Overloaded operator[] to directly access node in directory.
     * @param index Nodes index in directory.
     * @return HierarchyNode ptr to node n directory.
     */
    inline HierarchyNode * operator[]( unsigned index ) const{
       return ( begin() + index )->get();
    }

protected:
    /**
     * List with Directory pointers.
     */
    list< Directory * > _nav;
};
