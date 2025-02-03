#ifndef NeutronMC_PARTICLE_H
#define NeutronMC_PARTICLE_H

#include <TObject.h>

class TParticle;

class NeutronMCParticle : public TObject {
public:
  NeutronMCParticle(Int_t id, TParticle *particle);
  NeutronMCParticle(Int_t id, TParticle *particle, NeutronMCParticle *mother);
  NeutronMCParticle();
  virtual ~NeutronMCParticle();

  // methods
  void SetMother(NeutronMCParticle *particle);
  void AddDaughter(NeutronMCParticle *particle);
  void Print();

  // get methods
  Int_t GetID() const;
  TParticle *GetParticle() const;
  NeutronMCParticle *GetMother() const;
  Int_t GetNofDaughters() const;
  NeutronMCParticle *GetDaughter(Int_t i) const;

private:
  // data members
  Int_t fID;             ///< The particle Id
  TParticle *fParticle;  ///< The particle definition
  NeutronMCParticle *fMother; ///< The particle mother
  TObjArray *fDaughters; ///< The particle daughters

  ClassDef(NeutronMCParticle, 1) // Extended TParticle
};

#endif // NeutronMC_PARTICLE_H
