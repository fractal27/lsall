# lsall

Lsall is a project that focuses on the tree-like visualization of a folder, with various arguments.

---
## Installation

### Linux

For Linux the installation is simple

1. Download the project via git

```bash
git clone https://github.com/GDominici07/lsall.git
```

2. Run the shell program `./install`

and just run in bash the simple command while in the cloned project
```bash
sudo ./install
```

If you are intruigued at how the installation process works, it uses a combination of CMake and some `sudo cp` commands to add the executable files to the directory `/usr/local/bin/` and the manual(man1) page to the directory `/usr/share/man/man1`.

*NOTE*: Windows and MacOS installation is not yet implemented.

---
## Usage

### Synopsis

the comand is used as follows:
```bash
lsall [-pfFesdi] [-p PATH] [-f CHARACTER] [-F CHARACTER] [-d DEPTH]
lsa   [-pfFesdi] [-p PATH] [-f CHARACTER] [-F CHARACTER] [-d DEPTH]
```

### Arguments

**-p** To enter only one path, the argument in -p. (default is \'./\')

**-f** Character in the first row of every line. (default is \'\|\')

**-F** Filler between the first character and the filename representing the
current depth of the file.(if not inserted is \"\~\")

**-e** Doesn\'t show the unicode characters(emoji) used to represent files,
directories\...

**-s**Shows the size of each file.

**-d DEPTH** Depth of the recursive search (If depth is negative or null, it will be
counted as infinity.)

**-i** Read file path from standard input ( The prompt is not set by default. )

**NOTE**: TOOK FROM [lsall man page](src/lsall.1)

## Examples

If you want to use to display a the tree of your project without all the directories and you are
using a terminal without UNICODE emoji support, you can use the -e to not show emojis.

And use the flag `-d` to set the depth to the level you prefer, for example:

```bash
$ lsa -e -d 1
|[.]
|~(d) src
|~~~(r) main.cpp
|~~~(r) lsall.1
|~~~(r) lsa.cpp
|~(d) include
|~~~(r) lsall.h
|~(r) README.md
|~(r) CMakeLists.txt
|~(d) .git
|~~~(r) index
|~~~(r) HEAD
|~~~(d) branches
|~~~(r) config
|~~~(r) description
|~~~(r) FETCH_HEAD
|~~~(d) hooks
|~~~(r) COMMIT_EDITMSG
|~~~(d) objects
|~~~(d) info
|~~~(d) refs
|~~~(d) logs
|~(r) install
|~(d) build
|~(d) CMakeFile
```

