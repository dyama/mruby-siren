MRuby::Gem::Specification.new('mruby-siren') do |spec|
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Easy 3D Geometry and Topology engine.'
    #-L/opt/occ671/lib -I/opt/occ671/inc \
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
  spec.linker.library_paths << [
    '/opt/oce/lib'
  ]
  spec.cxx.flags << "\
    -Wno-unused-function -Wno-unused-variable \
    -L/opt/oce/lib -I/opt/oce/include/oce \
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

