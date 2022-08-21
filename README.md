# simple ncurses filemanager

File/directory management program.
The program can create, delete, copy, move and rename directories, files and symbolic links.

The user interface is implemented using ncurses.

The program works only with POSIX libraries unistd.h, dirent.h, sys/stat.h, sys/types.h and STL libraries.

## Compilation:

In the project directory:

- `make compile` - builds filemanager from source
- `make doc` - makes a doxygen documentation from source according to the Doxyfile
- `make clean` - removes build and object files
- `make all` - makes both filemanager build and documentation
- `make run` - runs the build app

## Example

using POSIX libraries to retrieve the contents of the root directory.

```cpp
DIR *dir;
struct dirent *sd; // node in the directory
struct stat buf; // more detailed information about the file

dir = opendir( "/" ); 

while( ( sd = readdir( dir ) ) ){
   stat( sd->d_name, &buf );
   // do something
}
closedir( dir );
```

And this is how the contents of the other directories are loaded, to which the program navigates.

## Functionality description

Information obtained from directories/folders/links is added to the appropriate classes. A list of directories that the program has already navigated through is formed.

When navigating to the /.. directory, pressing `ENTER` will navigate the program higher up in the folder hierarchy. Otherwise, when it's on any other directory, it dives deeper, and when it's on a node other than the directory, it does nothing. 

The implemented user interface is divided into left and right panels, with the left panel being the controller that navigates through the folders. The program always starts in the root directory.
The right panel is a menubar that holds the available operations.

Use the `TAB` to switch between the left and right panels.

The currently selected menu option, when `ENTER` is pressed, performs a create, delete, rename, move, or copy operation over the appropriate node where the left panel is currently pointing.

When performing operations, dialog boxes may pop up that either want to share some information, ask a question, or expect some user input. This is either in the form of a new filename or the absolute path of the node being moved.
