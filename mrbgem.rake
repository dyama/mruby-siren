##
# mruby-siren rake file
#

MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'

  # define path
  use_oce = true
  occlibpath = '/opt/occ671/lib'
  occincpath = '/opt/occ671/inc'
  occlibpath2 = ''
  if use_oce
    occlibpath = '/opt/oce/lib'
    occincpath = '/opt/oce/include/oce'
  end

  if ENV['OS'] == 'Windows_NT'
    occlibpath = 'E:/occ//671/opencascade-6.7.1/win32/vc9/lib'
    occincpath = 'E:/occ/671/opencascade-6.7.1/inc'
  end

  # OCCT dependencies
  # Check http://dev.opencascade.org/doc/refman/html/index.html
  thirdPartyLibs = []
  if cxx.command == 'cl.exe'

  else
    thirdPartyLibs = [ 'tbb' ]
  end
  foundationClasses =
    [ 'TKernel', 'TKMath' ]
  modelingData =
    [ 'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep' ]
  modelingAlgorithms =
    [ 'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
      'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
      'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset' ]
  visualization =
    [ 'TKService', 'TKV3d' ]
  applicationFramework = []
  dataExchange = [ 'TKXSBase', 'TKSTL', 'TKIGES' ]

  # thirdPartyLibs =
  #   [ 'tbb' ]
  # foundationClasses =
  #   [ 'TKernel', 'TKMath' ]
  # modelingData =
  #   [ 'TKG2d', 'TKG3d', 'TKGeomBase', 'TKBRep' ]
  # modelingAlgorithms =
  #   [ 'TKGeomAlgo', 'TKTopAlgo', 'TKBO', 'TKPrim',
  #     'TKShHealing', 'TKHLR', 'TKMesh', 'TKBool',
  #     'TKXMesh', 'TKFeat', 'TKFillet', 'TKOffset' ]
  # visualization =
  #   [ 'TKService', 'TKV3d', 'TKOpenGl', 'TKMeshVS',
  #     'TKNIS', 'TKVoxel' ]
  # applicationFramework =
  #   [ 'PTKernel', 'TKCDF', 'TKPShape', 'FWOSPlugin', 'TKLCAF',
  #     'TKShapeSchema', 'TKPLCAF', 'TKCAF', 'TKBinL', 'TKTObj',
  #     'TKXmlL', 'TKStdLSchema', 'TKPCAF', 'TKBin', 'TKBinTObj',
  #     'TKXml', 'TKXmlTObj', 'TKStdSchema' ]
  # dataExchange =
  #   [ 'TKXSBase', 'TKSTL', 'TKVRML', 'TKSTEPBase', 'TKXCAF', 'TKIGES',
  #     'TKSTEP209', 'TKSTEPAttr', 'TKXCAFSchema', 'TKXmlXCAF', 'TKBinXCAF',
  #     'TKXDEIGES', 'TKSTEP', 'TKXDESTEP' ]

  allLibs = []
  allLibs <<
    thirdPartyLibs << foundationClasses << modelingData << modelingAlgorithms <<
    visualization << applicationFramework << dataExchange

  # Linker option
  spec.linker.library_paths << [ occlibpath ]

  spec.linker.libraries << allLibs

  # Compiler option
  if spec.cxx.command == 'cl.exe'
    spec.cxx.flags << "/I#{occincpath}"
    spec.cxx.flags << "/DWNT"
  else
    spec.cxx.flags << "-L" << occlibpath << " -I" << occincpath <<
      "-Wno-unused-function -Wno-unused-variable"
  end

  #allLibs.each do |libname|
  #  spec.cxx.flags << " -l" << libname
  #end

end

