##
# mruby-siren rake file
#

MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'

  # define path
  occlibpath = '/opt/occ680/lib'
  occincpath = '/opt/occ680/inc'
  sirenincpath = File.expand_path(File.dirname(__FILE__)) + '/inc'

  if ENV['OS'] == 'Windows_NT'
    occlibpath = 'E:/occ//680/opencascade-6.8.0/win32/vc9/lib'
    occincpath = 'E:/occ/680/opencascade-6.8.0/inc'
  end

  # OCCT dependencies
  # Check http://dev.opencascade.org/doc/refman/html/index.html
  thirdPartyLibs = []
  if cxx.command == 'cl.exe'

  else
    thirdPartyLibs = [ 'tbb', 'gl2ps', 'freetype', 'freeimage', 'OpenCL' ]
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
     [ 'TKService', 'TKV3d', 'TKOpenGl', 'TKMeshVS',
       'TKNIS', 'TKVoxel' ]
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
    spec.cxx.flags << "/I#{sirenincpath}"
    spec.cxx.flags << "/DWNT"
  else
    spec.cxx.flags << "-L" << occlibpath << " -I" << occincpath << " -I" << sirenincpath <<
      "-Wno-unused-function -Wno-unused-variable"
  end

  #allLibs.each do |libname|
  #  spec.cxx.flags << " -l" << libname
  #end

end

