# Superbly inefficient inverse matrix api
The algorithm sucks, it is O(n^4). So don't expect much. Altough for regular circuits and meshes it is more than enough.

To use the program,
1. Compile the project with `make` (or just follow the recipe mentioned in the `Makefile`)
2. Change the content of `input.txt` according to your need (As it stands for now, any dimension should be okay), *the entries are parsed in float*
3. Mention where you want your output. (A new file will be created if the path is empty)
4. run the output with the address of the text file. (eg. `main input.txt output.txt`)

*This project uses [the vector implementation of stb](http://nothings.org/stb_ds/)*
