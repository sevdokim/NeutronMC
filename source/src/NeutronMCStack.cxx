#include "NeutronMCStack.h"

#include <TError.h>
#include <TObjArray.h>
#include <TParticle.h>

/// \cond CLASSIMP
ClassImp(NeutronMCStack);
/// \endcond

//_____________________________________________________________________________
NeutronMCStack::NeutronMCStack(Int_t size)
    : fParticles(0), fCurrentTrack(-1), fNPrimary(0) {
  /// Standard constructor
  /// \param size  The stack size

  fParticles = new TObjArray(size);
}

//_____________________________________________________________________________
NeutronMCStack::NeutronMCStack() : fParticles(0), fCurrentTrack(-1), fNPrimary(0) {
  /// Default constructor
}

//_____________________________________________________________________________
NeutronMCStack::~NeutronMCStack() {
  /// Destructor

  if (fParticles)
    fParticles->Delete();
  delete fParticles;
}

// private methods

//_____________________________________________________________________________
NeutronMCParticle *NeutronMCStack::GetParticle(Int_t id) const {
  /// \return   The \em id -th particle in fParticles
  /// \param id The index of the particle to be returned

  if (id < 0 || id >= fParticles->GetEntriesFast())
    Fatal("GetParticle", "Index out of range");

  return (NeutronMCParticle *)fParticles->At(id);
}

// public methods

//_____________________________________________________________________________
void NeutronMCStack::PushTrack(Int_t toBeDone, Int_t parent, Int_t pdg,
                            Double_t px, Double_t py, Double_t pz, Double_t e,
                            Double_t vx, Double_t vy, Double_t vz, Double_t tof,
                            Double_t polx, Double_t poly, Double_t polz,
                            TMCProcess mech, Int_t &ntr, Double_t weight,
                            Int_t is) {
  /// Create a new particle and push into stack;
  /// adds it to the particles array (fParticles) and if not done to the
  /// stack (fStack).
  /// \param toBeDone  1 if particles should go to tracking, 0 otherwise
  /// \param parent    number of the parent track, -1 if track is primary
  /// \param pdg       PDG encoding
  /// \param px        particle momentum - x component [GeV/c]
  /// \param py        particle momentum - y component [GeV/c]
  /// \param pz        particle momentum - z component [GeV/c]
  /// \param e         total energy [GeV]
  /// \param vx        position - x component [cm]
  /// \param vy        position - y component  [cm]
  /// \param vz        position - z component  [cm]
  /// \param tof       time of flight [s]
  /// \param polx      polarization - x component
  /// \param poly      polarization - y component
  /// \param polz      polarization - z component
  /// \param mech      creator process VMC code
  /// \param ntr       track number (is filled by the stack
  /// \param weight    particle weight
  /// \param is        generation status code

  const Int_t kFirstDaughter = -1;
  const Int_t kLastDaughter = -1;

  TParticle *particleDef =
      new TParticle(pdg, is, parent, -1, kFirstDaughter, kLastDaughter, px, py,
                    pz, e, vx, vy, vz, tof);

  particleDef->SetPolarisation(polx, poly, polz);
  particleDef->SetWeight(weight);
  particleDef->SetUniqueID(mech);

  NeutronMCParticle *mother = 0;
  if (parent >= 0)
    mother = GetParticle(parent);
  else
    fNPrimary++;

  NeutronMCParticle *particle = new NeutronMCParticle(GetNtrack(), particleDef, mother);

  fParticles->Add(particle);

  if (toBeDone)
    fStack.push(particle);

  ntr = GetNtrack() - 1;
}

//_____________________________________________________________________________
TParticle *NeutronMCStack::PopNextTrack(Int_t &itrack) {
  /// Get next particle for tracking from the stack.
  /// \return        The popped particle object
  /// \param itrack  The index of the popped track

  itrack = -1;
  if (fStack.empty())
    return 0;

  NeutronMCParticle *particle = fStack.top();
  fStack.pop();

  if (!particle)
    return 0;

  itrack = particle->GetID();
  fCurrentTrack = itrack;

  return particle->GetParticle();
}

//_____________________________________________________________________________
TParticle *NeutronMCStack::PopPrimaryForTracking(Int_t i) {
  /// Return \em i -th particle in fParticles.
  /// \return   The popped primary particle object
  /// \param i  The index of primary particle to be popped

  if (i < 0 || i >= fNPrimary)
    Fatal("GetPrimaryForTracking", "Index out of range");

  return ((NeutronMCParticle *)fParticles->At(i))->GetParticle();
}

//_____________________________________________________________________________
void NeutronMCStack::SetCurrentTrack(Int_t itrack) {
  /// Set the current track number to a given value.
  /// \param  itrack The current track number

  fCurrentTrack = itrack;
}

//_____________________________________________________________________________
Int_t NeutronMCStack::GetNtrack() const {
  /// \return  The total number of all tracks.

  return fParticles->GetEntriesFast();
}

//_____________________________________________________________________________
Int_t NeutronMCStack::GetNprimary() const {
  /// \return  The total number of primary tracks.

  return fNPrimary;
}

//_____________________________________________________________________________
TParticle *NeutronMCStack::GetCurrentTrack() const {
  /// \return  The current track particle

  NeutronMCParticle *current = GetParticle(fCurrentTrack);

  if (current)
    return current->GetParticle();
  else
    return 0;
}

//_____________________________________________________________________________
Int_t NeutronMCStack::GetCurrentTrackNumber() const {
  /// \return  The current track number

  return fCurrentTrack;
}
//_____________________________________________________________________________
Int_t NeutronMCStack::GetCurrentParentTrackNumber() const {
  /// \return  The current track parent ID.

  NeutronMCParticle *current = GetParticle(fCurrentTrack);

  if (!current)
    return -1;

  NeutronMCParticle *mother = current->GetMother();

  if (!mother)
    return -1;

  return mother->GetID();
}
//_____________________________________________________________________________
void NeutronMCStack::Reset() {
  /// Delete contained particles, reset particles array and stack.

  // reset fStack
  fCurrentTrack = -1;
  fNPrimary = 0;
  // fParticles->Delete();
  for (int i = 0; i < fParticles->GetEntriesFast(); i++) {
    delete fParticles->At(i);
  }
  fParticles->Clear();
  while (fStack.size()) {
    fStack.pop();
  }
}
//_____________________________________________________________________________
void NeutronMCStack::Print() {
  /// Print all particles in stack

  std::cout << "Particle stack has " << fParticles->GetEntriesFast()
            << " particles:" << std::endl;
  for (int i = 0; i < fParticles->GetEntriesFast(); i++) {
    ((NeutronMCParticle *)(fParticles->At(i)))->Print();
  }
}
