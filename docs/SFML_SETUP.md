0. Place SFML into the `libraries` directory.
1. set up code::blocks to remember the dir so you dont need to change all project files if you decide on putting SFML somewhere else
- open c::b
- go to "settings" menu -> "global variables"
- click the lower "new" button
- type in "sfml" (without "")
- click the base field
- type in "C:\SFML"  (without "") or whatever directory you put it
- click close

2. set up your project search directories
- have the project open
- rightclick the project name
- click "Build options"
- click your project name in the treeview at left to select options for all builds in the project
- click "Search directories" tab
- click "Compiler" subtab if not already choosen
- click "add" button
- type in "$(#sfml.include)" (without "")
- click "ok"
- click "Linker" subtab
- click "add" button
- type in "$(#sfml.lib)" (without "")
- click "ok"
3. set up the names of the actual library files
- you still need to be in the "Build options" dialog
- click the "Linker settings" tab
- click on "Release" in the treeview at the left
- click "add" button, type in "sfml-network" (without ""), click ok
- repeat last step several times and add "sfml-audio", "sfml-graphics", "sfml-window", "sfml-system", "opengl32" (without "") in the same order as written here
- click on "Debug" in the treeview at the left
- use the "add" button like above to fill in "sfml-network-d","sfml-audio-d", "sfml-graphics-d", "sfml-window-d", "sfml-system-d", "opengl32" (without "")
- click "OK" to close the "Build options" dialog
4. save your updated project
- click "File" menu
- click "Save project"
5. done 8)
- if it is still not working check that you actually put the SFML-version compatible to the version of MinGW you are currently using in the directory you set up and

