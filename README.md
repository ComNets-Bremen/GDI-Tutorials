[See it in action][www_rendered]

GDI Tutorials
=============

This repository contains slides for tutorials
that go along with an Introduction to coputer
science course for electrical engineering students.

The course spans two semesters,
the main topics of the two semesters are:

- Semester 1: Using the Arduino soft- and hardware
- Semester 2: Programming in Python and connecting it
  to the Arduino platform

The Slides are written in Markdown and the
sourcecode is located in the `/src` folder.

Generating the presentations
============================

To generate the presenation .html
files change into the target directory

    $ cd target/

and run make.

    $ make

Assuming you have the access rights to the server configured
in the Makefile you can now run

    $ make available

to upload the slides to a server.

Dependencies
============

To generate the slides you will need
[landslide][www_landslide] installed.

To install landslide on a debian based
distribution enter

    $ sudo apt install python-landslide

on the commandline.

Licenses
========

The slide-sourcecodes, code examples and all other
assets are licensed under the GNU Free Documentation License
([FDL][www_gnu_fdl]) without invariant sections or cover text.

The theme files under `/theme/boring` may also be used
under the Creative Commons Zero ([CC0][www_cc_zero]) license
for easier integration into other projects.

[www_rendered]: https://tut.zerforscht.de/gdi/
[www_landslide]: https://github.com/adamzap/landslide
[www_gnu_fdl]: http://www.gnu.org/licenses/fdl.html
[www_cc_zero]: https://creativecommons.org/publicdomain/zero/1.0/
