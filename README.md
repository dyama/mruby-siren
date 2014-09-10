siren - Easy 3D geometry and topology engine
============================================

mrbgems edition for MRuby.

**siren** is easy 3D operation engine powered by Open CASCADE technorogy. siren is integrated to Ruby interpreter environment, so it gives high-level 3D geometrical and topological operation with easy and simple script.
For example, you can get volume of shape, intersection lines of some shapes, center of gravity and a result of boolean operation. It supports IGES, STEP file with NURBS surface and curve.

In now, siren has no 3D viewer but it will be included soon. You can use batch processing and interactive shell on Ruby environment already.

Base project
------------

* siren
https://github.com/dyama/siren

Dependencies
------------

* mruby
https://github.com/mruby/mruby

* Open CASCADE Community Edition
https://github.com/tpaviot/oce

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
1. Install OCE libraries and headers on your system.
2. Clone mruby environment.
3. Add build configue of mrbgems.
4. Change path to each libraries in mrbgem.rake.
5. Make mruby.

Usage
-----
* Run build/host/bin/mirb.
* Run build/host/bin/mruby with siren script.

Reference manual
----------------

See documentation in doc directory or https://github.com/dyama/mruby-siren/wiki.

Lincense
--------
MIT License

Author
------
* dyama <dyama@member.fsf.org>

