MRuby::Gem::Specification.new('mruby-siren') do |spec|

  # General spec
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'

  # define path
  use_oce = true
  occlibpath = '/opt/occ671/lib'
  occincpath = '/opt/occ671/inc'
  if use_oce
    occlibpath = '/opt/oce/lib'
    occincpath = '/opt/oce/include/oce'
  end

  # Linker option
  spec.linker.libraries << [
    'tbb',
    'TKernel',
    'TKMath',
    'TKBRep',
    'TKTopAlgo',
    'TKGeomAlgo',
    'TKGeomBase',
    'TKG3d',
    'TKG2d'
  ]
  spec.linker.library_paths << [ occlibpath ]

  # Compiler option
  spec.cxx.flags << "\
    -L" << occlibpath << " -I" << occincpath << " \
    -Wno-unused-function -Wno-unused-variable \
    -ltbb \
    -lTKernel \
    -lTKMath \
    -lTKBRep \
    -lTKGeomAlgo \
    -lTKTopAlgo \
    -lTKGeomBase \
    -lTKG3d \
    -lTKG2d"
    # -lFWOSPlugin \
    # -lPTKernel \
    # -lTKAdvTools \
    # -lTKBO \
    # -lTKBRep \
    # -lTKBin \
    # -lTKBinL \
    # -lTKBinTObj \
    # -lTKBinXCAF \
    # -lTKBool \
    # -lTKCAF \
    # -lTKCDF \
    # -lTKFeat \
    # -lTKFillet \
    # -lTKG2d \
    # -lTKG3d \
    # -lTKGeomAlgo \
    # -lTKGeomBase \
    # -lTKHLR \
    # -lTKIGES \
    # -lTKLCAF \
    # -lTKMath \
    # -lTKMesh \
    # -lTKOffset \
    # -lTKPCAF \
    # -lTKPLCAF \
    # -lTKPShape \
    # -lTKPrim \
    # -lTKSTEP \
    # -lTKSTEP209 \
    # -lTKSTEPAttr \
    # -lTKSTEPBase \
    # -lTKSTL \
    # -lTKService \
    # -lTKShHealing \
    # -lTKShapeSchema \
    # -lTKStdLSchema \
    # -lTKStdSchema \
    # -lTKTObj \
    # -lTKTopAlgo \
    # -lTKV3d \
    # -lFWOSPlugin \
    # -lPTKernel \
    # -lTKAdvTools \
    # -lTKBO \
    # -lTKBRep \
    # -lTKBin \
    # -lTKBinL \
    # -lTKBinTObj \
    # -lTKBinXCAF \
    # -lTKBool \
    # -lTKCAF \
    # -lTKCDF \
    # -lTKFeat \
    # -lTKFillet \
    # -lTKG2d \
    # -lTKG3d \
    # -lTKGeomAlgo \
    # -lTKGeomBase \
    # -lTKHLR \
    # -lTKIGES \
    # -lTKLCAF \
    # -lTKMath \
    # -lTKMesh \
    # -lTKOffset \
    # -lTKPCAF \
    # -lTKPLCAF \
    # -lTKPShape \
    # -lTKPrim \
    # -lTKSTEP \
    # -lTKSTEP209 \
    # -lTKSTEPAttr \
    # -lTKSTEPBase \
    # -lTKSTL \
    # -lTKService \
    # -lTKShHealing \
    # -lTKShapeSchema \
    # -lTKStdLSchema \
    # -lTKStdSchema \
    # -lTKTObj \
    # -lTKTopAlgo \
    # -lTKV3d \
    # -lTKVRML \
    # -lTKXCAF \
    # -lTKXCAFSchema \
    # -lTKXDEIGES \
    # -lTKXDESTEP \
    # -lTKXMesh \
    # -lTKXSBase \
    # -lTKXml \
    # -lTKXmlL \
    # -lTKXmlTObj \
    # -lTKXmlXCAF \
    # -lTKernel"
end

