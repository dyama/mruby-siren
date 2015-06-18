siren - Easy 3D operation environment
=====================================

mrbgems edition for MRuby.

**siren** is easy 3D operation environment powered by Open CASCADE Technorogy. siren is integrated to Ruby interpreter environment, so it gives high-level 3D geometrical and topological operation with easy and simple script.
For example, you can get volume of shape, intersection lines of some shapes, center of gravity and a result of boolean operation. It supports IGES, STEP file with NURBS surface and curve.

In now, siren has a 3D viewer for X window system only, but it will be included for MS Windows soon. You can use batch processing and interactive shell on Ruby environment already.

You can get more information at siren official page.

* siren official page: http://siren.xyz/

Dependencies
------------

* mruby
https://github.com/mruby/mruby

* Open CASCADE Technorogy
http://www.opencascade.org/

Required mrbgems
----------------

Nothing

Optional mrbgems
----------------

* mruby-io
https://github.com/iij/mruby-io

* mruby-pcre-regexp
https://github.com/mattn/mruby-pcre-regexp

How to build
------------
1. Install OCCT libraries and headers on your system.
2. Clone mruby environment.
3. Add build configue of mrbgems.
4. Change path to each libraries in mrbgem.rake.
5. Make mruby.

Usage
-----
* Run build/host/bin/mirb.
* Run build/host/bin/mruby with siren script.

Documentation
-------------

* Official web page: http://siren.xyz/
* Tutorial: http://siren.xyz/tutorial.html
* Wiki: https://github.com/dyama/mruby-siren/wiki.

Lincense
--------
MIT License

Author
------
* dyama <dyama@member.fsf.org>

