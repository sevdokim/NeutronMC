#include "NeutronMCParticle.h"

#include <TObjArray.h>
#include <TParticle.h>

/// \cond CLASSIMP
ClassImp(NeutronMCParticle)
    /// \endcond

    //_____________________________________________________________________________
    NeutronMCParticle::NeutronMCParticle(Int_t id, TParticle *particle)
    : fID(id), fParticle(particle), fMother(0), fDaughters(0) {
  /// Standard constructor
  /// \param  id        The particle id
  /// \param  particle  The particle definition (TParticle)
}

//_____________________________________________________________________________
NeutronMCParticle::NeutronMCParticle(Int_t id, TParticle *particle, NeutronMCParticle *mother)
    : fID(id), fParticle(particle), fMother(mother), fDaughters(0) {
  /// Standard constructor
  /// \param  id        The particle id
  /// \param  particle  The particle definition (TParticle)
  /// \param  mother    The particle mother
}

//_____________________________________________________________________________
NeutronMCParticle::NeutronMCParticle() : fID(0), fParticle(0), fMother(0), fDaughters(0) {
  /// Default constructor
}

//_____________________________________________________________________________
NeutronMCParticle::~NeutronMCParticle() {
  /// Destructor
  delete fParticle;
  if (fDaughters) {
    fDaughters->Delete();
    delete fDaughters;
  }
}

// operators

// public methods

//_____________________________________________________________________________
void NeutronMCParticle::AddDaughter(NeutronMCParticle *particle) {
  /// Add particles daughter
  /// \param particle  The daughter particle

  if (!fDaughters)
    fDaughters = new TObjArray();

  fDaughters->Add(particle);
}

//_____________________________________________________________________________
void NeutronMCParticle::SetMother(NeutronMCParticle *particle) {
  /// Set particle mother
  /// \param  particle  The mother particle

  fMother = particle;
}

//_____________________________________________________________________________
Int_t NeutronMCParticle::GetID() const {
  /// \return The particle Id.

  return fID;
}

//_____________________________________________________________________________
TParticle *NeutronMCParticle::GetParticle() const {
  /// \return The particle definition (TParticle).

  return fParticle;
}

//_____________________________________________________________________________
NeutronMCParticle *NeutronMCParticle::GetMother() const {
  /// \return The particle mother.

  return fMother;
}

//_____________________________________________________________________________
Int_t NeutronMCParticle::GetNofDaughters() const {
  /// \return The number of daughters.

  if (!fDaughters)
    return 0;

  return fDaughters->GetEntriesFast();
}

//_____________________________________________________________________________
NeutronMCParticle *NeutronMCParticle::GetDaughter(Int_t i) const {
  /// \return   \em i -th daughter
  /// \param i  The daughter index

  // add test if i

  return (NeutronMCParticle *)fDaughters->At(i);
}
//_____________________________________________________________________________
void NeutronMCParticle::Print() {
  // print info about particle
  std::cout << "Id=" << std::setw(5) << fID << "; Mother=" << std::setw(5)
            << fParticle->GetMother(0) << "; PDG=" << std::setw(10)
            << fParticle->GetPdgCode() << "; ";
  fParticle->Print();
}
