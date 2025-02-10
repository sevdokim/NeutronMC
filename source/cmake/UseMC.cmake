# VMC packages
#
if (NOT VMCPackages_FOUND)
  find_package(VMCPackages REQUIRED)
endif(NOT VMCPackages_FOUND)

# MC packages
#
if (NOT MCPackages_FOUND)
  find_package(MCPackages)
endif(NOT MCPackages_FOUND)

set(MCPackages_LIBRARIES)

# ROOT (required)
include_directories(${ROOT_INCLUDE_DIRS})

# Geant4
add_definitions(-DUSE_GEANT4)
# Workaround for upstream bug: http://bugzilla-geant4.kek.jp/show_bug.cgi?id=1663
#include(${Geant4_USE_FILE})
include(${Geant4_USE_FILE})
if(Geant4VMC_FOUND)
   # build outside Geant4VMC
  include_directories(${Geant4VMC_INCLUDE_DIRS})
  set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} ${Geant4VMC_LIBRARIES})
else()
  # build inside Geant4VMC
  include_directories(${Geant4VMC_SOURCE_DIR}/source/global/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/geometry/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/digits+hits/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/physics/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/physics_list/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/physics_monopole/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/event/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/run/include)
  include_directories(${Geant4VMC_SOURCE_DIR}/source/visualization/include)
  set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} geant4vmc)
endif(Geant4VMC_FOUND)

if(G4Root_FOUND)
  # build outside Geant4VMC
  set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} ${G4Root_LIBRARIES})
else()
  # build inside Geant4VMC
  include_directories(${Geant4VMC_SOURCE_DIR}/g4root/include)
  set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} g4root)
endif(G4Root_FOUND)

if(VGM_FOUND)
  set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} ${VGM_LIBRARIES})
endif(VGM_FOUND)

set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} ${Geant4_LIBRARIES})
set(MC_PREFIX "g4")

# Finally add Root libraries
set(MCPackages_LIBRARIES ${MCPackages_LIBRARIES} ${ROOT_LIBRARIES})
