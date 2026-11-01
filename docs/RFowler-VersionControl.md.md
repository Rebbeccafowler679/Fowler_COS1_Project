
# Project and Portfolio I: Computer Science

- [**Becca Fowler**]
- [**November 1, 2026**]

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.


**1. Using Terminal, there are essential commands to know.**

- [`clear`]: Clear the screen
- [`pwd`]: Print the working directory (shows the full path of the folder you're currently in)
- [`ls`]: List files and folders in the current directory
- [`ls -a`]: List files and folders, including invisible (hidden) files
- [`ls -lah`]: List all files and folders in long format, with file sizes in human readable form (KB, MB)
- [`cd [foldername]`]: Change directory into a specific folder
- [`cd /`]: Change directory, go to the root directory
- [`cd ~`]: Change directory and go to the user home directory
- [`cd ..`]: Change directory, go up one folder level
- [`cd ../..`]: Change directory, go up two folder levels
- [`cd ~/Desktop`]: Change directory to my desktop

**2. Using Terminal...**

**Folder Drop:** I typed [`cd`] followed by a space, dragged a folder from my file explorer into the terminal window, and pressed return. The terminal automatically pasted the folder's full path after [`cd`], and the command changed my working directory into that folder. It's a fast shortcut - instead of typing out a long path by hand and risking typos, the OS fills in the exact path for you. I can see myself using this a lot when jumping into my project repo, since it's nested a few folders deep.

## Topic: Version Control & Git

**1. There are three types of version control.**

1. **Local version control** — changes are tracked in a database on a single computer (for example, RCS keeps a record of file diffs locally). Simple, but everything lives in one place, so if that machine dies, the history dies with it.
2. **Centralized version control (CVCS)** — a single central server holds the entire version history, and everyone checks files in and out of that server (examples: Subversion, Perforce). Collaboration is easier, but the server is a single point of failure — if it goes down, nobody can save their work, and if it's lost without a backup, so is the history.
3. **Distributed version control (DVCS)** — every developer has a complete copy of the repository, including its full history, on their own machine (examples: Git, Mercurial). There is no single point of failure, you can commit and browse history offline, and if the server dies, any clone can restore it. This is what Git is, and it's why cloning a repo gives you everything, not just the latest files.