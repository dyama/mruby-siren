siren - Lightweight 3D operation environment
=====================================

**siren** is lightweight 3D operation environment powered by Open CASCADE Technorogy. siren is integrated to MRuby; lightweight Ruby interpreter environment, so it gives high-level 3D geometrical and topological operation with easy and simple scripting.
For example, you can get volume of shape, intersection lines of some shapes, center of gravity and a result of boolean operation. It supports IGES, STEP file with NURBS surface and curve.

You can get more information at siren official page.

* siren official page: http://siren.xyz/

Dependencies
------------

* mruby
https://github.com/mruby/mruby

* Open CASCADE Technorogy 6.9.0 (for UNIX environment)
http://www.opencascade.org/

* Open CASCADE Community Edition 0.17 (for MINGW32 environment)
https://github.com/tpaviot/oce

How to build
------------
1. Install OCCT libraries and headers on your system.
2. Clone mruby source code from github.
3. Add `conf.gem :github => "dyama/mruby-siren"` line to mrbgems/default.gembox.
4. Make mruby.

If your OCCT installed path is not `/opt/occ<version no>`, you should change mrbgem.rake file in build/mrbgems/mruby-siren.
Default install path is;

  * /opt/occ690 ... for UNIX
  * E:/occ/OCE-0.170Mingw32 .. for MINGW32

Usage
-----
* Run build/host/bin/mirb.
* Run build/host/bin/mruby with siren script.

Documentation
-------------

* Official web page: http://siren.xyz/
* Tutorial: http://siren.xyz/tutorial.html
* Wiki: https://github.com/dyama/mruby-siren/wiki.
  * Reference Manual: https://github.com/dyama/mruby-siren/wiki/Reference-manual
  * Examples: https://github.com/dyama/mruby-siren/wiki/Sample

Lincense
--------
MIT License

Author
------
* dyama <dyama@member.fsf.org>

