#ifndef NeutronMC_STACK_H
#define NeutronMC_STACK_H

#include "NeutronMCParticle.h"

#include <TVirtualMCStack.h>

#include <stack>

/// \ingroup E01
/// \brief Implementation of the TVirtualMCStack interface
///
/// \date 05/04/2002
/// \author I. Hrivnacova; IPN, Orsay

class NeutronMCStack : public TVirtualMCStack {
public:
  NeutronMCStack(Int_t size);
  NeutronMCStack();
  virtual ~NeutronMCStack();

  // methods
  virtual void PushTrack(Int_t toBeDone, Int_t parent, Int_t pdg, Double_t px,
                         Double_t py, Double_t pz, Double_t e, Double_t vx,
                         Double_t vy, Double_t vz, Double_t tof, Double_t polx,
                         Double_t poly, Double_t polz, TMCProcess mech,
                         Int_t &ntr, Double_t weight, Int_t is);
  virtual TParticle *PopNextTrack(Int_t &itrack);
  virtual TParticle *PopPrimaryForTracking(Int_t i);
  void Reset();
  void Print();

  // set methods
  virtual void SetCurrentTrack(Int_t itrack);

  // get methods
  virtual Int_t GetNtrack() const;
  virtual Int_t GetNprimary() const;
  virtual TParticle *GetCurrentTrack() const;
  virtual Int_t GetCurrentTrackNumber() const;
  virtual Int_t GetCurrentParentTrackNumber() const;

private:
  // methods
  NeutronMCParticle *GetParticle(Int_t id) const;

  // data members
  std::stack<NeutronMCParticle *> fStack; //!< The stack of particles (transient)
  TObjArray *fParticles;             ///< The array of particle (persistent)
  Int_t fCurrentTrack;               ///< The current track number
  Int_t fNPrimary;                   ///< The number of primaries

  ClassDef(NeutronMCStack, 1) // NeutronMCMCStack
};

#endif // NeutronMC_STACK_H
