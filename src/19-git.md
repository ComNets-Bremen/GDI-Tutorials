<!--

                  Copyright (C)  2017  Leonard Göhrs.
   Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
     or any later version published by the Free Software Foundation;
  with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
      A copy of the license is included in the file "LICENSE-FDL.txt".

-->

Git version control
===================

Git is a tool to manage sourcecode

_Never lose your coding progress again_

---

An empty folder
===============

Windows
-------

Go to your programs overview and start
Git Bash

Everywhere else
---------------

Open a terminal window

---

![Empty working directory](images/19_gitint_empty_wd.svg)

`cd` into the directory where you save your
python projects

Type `mkdir test` to create a new empty folder
called `test`

Type `cd test` to go to the new folder

---

![Non-empty working directory](images/19_gitint_nonempty_wd.svg)

Open your text editor and create the files `README.md` and `test.py`
with some dummy content like `hello world` or `test`

Save the files to the folder you created on the previous slide

Type `ls` in the terminal to verify that you saved the files
correctly

---

![Non-empty working directory](images/19_gitint_nonempty_wd.svg)

The folder in which you saved the files is called the

_working directory_

we now want to manage this directory using git

---

![empty git repository](images/19_gitint_empty_git.svg)

To make the current directory a git
repository type `git init` on the terminal

`git init` creates a hidden `.git` folder
in the working directory to store all its data

Type `ls -a` to see the hidden `.git` directory

Type `ls .git` to see the content of the `.git`
directory

---

![empty git repository](images/19_gitint_empty_git.svg)

We want git to keep track of our `README.md` and
`test.py` files

Git does not perform any automatic synchronizations
in the background like e.g. Dropbox does

Instead we have to manually inform git about
changes we made to the files in the working
directory

---

<pre style="font-size:0.5em">
$ git status
On branch master

Initial commit

Untracked files:
  (use "git add &lt;file&gt;..." to include in what will be committed)

  README.md
  test.py

nothing added to commit but untracked files present (use "git add" to track)
</pre>

Use the `git status` command to find the files
in the working directory that git does not yet track

---

![files in staging](images/19_gitint_staging.svg)

On the previous slide git told us to use `git add`
to start tracking `README.md` and `test.py`

Type `git add README.md test.py` on the terminal

`git add` creates copies of the files and saves
them under the `.git` directory

It also calculates hash values that uniquely
identify the contents of the files

---

Commits
=======

<pre style="font-size:0.5em">
$ git status
On branch master

Initial commit

Changes to be committed:
  (use "git rm --cached &lt;file&gt;..." to unstage)

	new file:   README.md
	new file:   test.py
</pre>

If we now rerun `git status` it will tell us,
that `README.md` and `test.py` are "to be committed"

---

Commits
=======

A commit in git is a snapshot of the whole project
at a given time

As long as you do not actively break your git repository
you can always go back to _every previous commit_ in
your git history

E.g. when you accidentially delete one of your source-files
you will only lose the work you did since the last commit

Or when your project stops working you can always go back to
a previous version that is known to work and find the
breaking change

---

Commits
=======

In order to create a new commit you:

- `git add` every file that you want to be part of the commit
- use `git status` to check if you included all your changes
- Type `git commit -m "Your description here"`

You should replace "Your description here" by a description of
the changes you did since the last commit

---

![first commit](images/19_gitint_commit_1.svg)

In the example we are now about to commit the
changes to `README.md` and `test.py`

Type `git commit -m "My 1st commit"` as this is
our first commit in this repository

You can now use `git log` to see the history
of this repository

---

Commit #2
=========

For the next commit we want `test.py` to
output `"Hello World!"` when it is executed

Replace the text you put into `text.py`
with the following program:

    !Python
    print('Hello World!')

Create a commit that includes the new `test.py`

Make sure to give it a good description of the changes

---

![second commit](images/19_gitint_commit_2.svg)

The second commit stores:

- A reference to the previous commit
- A description "Better test.py"
- References to the old `README.md` and the new `test.py`

Use `git log` to look at the history of the project

---

Syncing
=======

Although not losing any local work is already a great feature
git can do even more

One of the other mayor features is being able to
synchronize repositories with a server

This allows you to simultaneously collaborate on
software over the internet

---

Syncing
=======

![Gitlab Dashboard](images/19_gitlab_dashboard.png)

Sign into/create an account on a codesharing site that
supports git like Gitlab, Bitbucket or Github

---

Syncing
=======

![Gitlab ssh key](images/19_gitlab_key.png)

In order to use a git-based codesharing site
you have to generate a ssh public key once
and configure the site to associate it with
your account

[Click here][www_ssh_tut] for a tutorial on
how to generate a public key

---

Syncing
=======

![Gitlab new project](images/19_gitlab_new_project.png)

After configuring your public key you
can create a new project …

---

Syncing
=======

![Gitlab ssh address](images/19_gitlab_ssh.png)

… copy the address of the new project …

---

Syncing
=======

![empty server](images/19_gitint_empty_server.svg)

… and add it to your git repository as a remote
using the command:

`git remote add origin [address of the project]`

---

Syncing
=======

![Synchronized server](images/19_gitint_synced_server.svg)

Once again git does not perform any automatic
synchronizations.

In order to publish your changes to the server
you have to use the `git push` command

To setup this remote as a default type
`git push --set-upstream origin master`
to push your changes to the server

---

Collaborating
=============

![Add a developer](images/19_gitlab_add_dev.png)

In order to collaborate on a project you have
to add another user as a developer to the
project

Add a partner to your project

---

![Cloning a project](images/19_gitint_clone.svg)

To get a copy of an already existing repository
you can use the `git clone` command

Ask your partner for the address she/he
used in the `git remote add [address]` command

Type `cd ..` to go one directory up

Type `git clone [address] partner` to get a copy of
your partners code into a new `partner` folder

---

![Synchronized server](images/19_gitint_synced_server.svg)

Whenever you start working on your project you should
run the command `git pull`

It asks the server for the newest changes your
project-partners might have pushed to the common
repository

When you are done with a feature you should
`git add`, `git commit` and `git push` your
changes to the server

---

Outlook
=======

Git has a lot more feature than we covered here

We have not covered:

- What to do if you and your partner made
  changes to the code at the same time
- How to retrieve old commits
- What branches are
- Merging, rebasing, stashing

But as long as you stick to the commands that were
demonstrated in this turorial you will not lose
progress because of accidentially overwritten/deleted
files

[www_ssh_tut]: https://gitlab.com/help/ssh/README
