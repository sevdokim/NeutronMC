# Geant4
# External G4Root (if required)
if (Geant4VMC_USE_EXTERN_G4Root)
    find_package(G4Root REQUIRED)
endif()

# Geant4VMC
# (it includes also Geant4 configuration options used in Geant4 VMC installation)
set(Geant4VMC_DIR "" CACHE PATH "Directory where Geant4VMC is installed")
find_package(Geant4VMC REQUIRED)
# Geant4
set(_components)
if(Geant4VMC_USE_GEANT4_UI)
  list(APPEND _components ui_all)
endif()
if(Geant4VMC_USE_GEANT4_VIS)
  list(APPEND _components vis_all)
endif()
if(Geant4VMC_USE_GEANT4_G3TOG4)
  list(APPEND _components g3tog4)
endif()
find_package(Geant4 REQUIRED ${_components})
add_definitions(-DUSE_GEANT4)
# G4Root
if (Geant4VMC_USE_G4Root)
  if (NOT G4Root_FOUND)
    find_package(G4Root REQUIRED)
  endif()
endif()
 # VGM
if (Geant4VMC_USE_VGM)
  find_package(VGM REQUIRED)
endif()

# If all required packages above were found we can update MCPackages_FOUND
set(MCPackages_FOUND TRUE)


