siren - Lightweight 3D operation environment
=====================================

![siren logo](http://siren.xyz/res/siren_logo.png)

**siren** is lightweight 3D operation environment powered by Open CASCADE Technorogy. siren is integrated to MRuby; lightweight Ruby interpreter environment, so it gives high-level 3D geometrical and topological operation with easy and simple scripting.
For example, you can get volume of shape, intersection lines of some shapes, center of gravity and a result of boolean operation. It supports IGES, STEP file with NURBS surface and curve.

You can get more information at siren official page.

* siren official page: http://siren.xyz/

Example
-------

    # Make two boxes
    box1 = Prim.box [10, 10, 10]
    box2 = Prim.box [10, 10, 10]

    # Move box2
    box2.translate! [5, 5, 5]

    # Fuse two boxes
    box3 = box1.fuse box2

    # Print volume of box
    p box3.volume # => 1875

    box3.explore(ShapeType::FACE) do |face|
      # Print area of face
      p face.area
    end

You can find more examples code on Github page.

https://github.com/dyama/mruby-siren/wiki/Sample

Dependencies
------------

* mruby (Lightweight Ruby interpreter engine)
  * Official page: http://www.mruby.org/
  * Source code: https://github.com/mruby/mruby
  * License: https://github.com/mruby/mruby/blob/master/MITL

* Open CASCADE Technorogy 6.9.0 (for UNIX)
  * Official page: http://www.opencascade.org/
  * Source code: http://www.opencascade.com/content/latest-release
  * License: http://www.opencascade.com/content/licensing

* Open CASCADE Community Edition 0.17 (for MINGW32)
  * Source code: https://github.com/tpaviot/oce
  * License: https://github.com/tpaviot/oce/blob/master/LICENSE_LGPL_21.txt

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

Show `LICENSE` file.

Author
------
* dyama <dyama@member.fsf.org>

