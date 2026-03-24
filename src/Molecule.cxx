/*
** Molecule.cxx: Molecule class.
**
** Wim Hordijk   Last modified: 12 March 2026
*/

#include "Molecule.h"
#include "Reaction.h"


/*
** Molecule: The constructor.
**
** Parameters:
**   - seq: The molecule "sequence" (can be any string).
*/

Molecule::Molecule (string seq)
{
  /*
  ** Get the molecule information.
  */
  sequence.assign (seq);
  seqLength = sequence.length ();

  /*
  ** Set variables.
  */
  itAsReactant = asReactant.begin ();
  itAsProduct = asProduct.begin ();
  itAsCatalyst = asCatalyst.begin ();
}


/*
** ~Molecule: The destructor.
*/

Molecule::~Molecule ()
{
  /*
  ** Clear the lists.
  */
  asReactant.clear ();
  asProduct.clear ();
  asCatalyst.clear ();
}


/*
** getSequence: Get the molecule sequence.
**
** Parameters:
**   - seq: A string to hold (a copy of) the molecule sequence.
*/

void Molecule::getSequence (string& seq)
{
  /*
  ** Copy the molecule sequence.
  */
  seq.assign (sequence);
}


/*
** getSeqLength: Get the length of the molecule sequence.
**
** Returns:
**   - The length of the molecule sequence.
*/

int Molecule::getSeqLength ()
{
  /*
  ** Return the molecule length.
  */
  return (seqLength);
}


/*
** addAsReactant: Add a reaction for which the molecule is a reactant.
**
** Parameters:
**   - reac: A pointer to the reaction to add.
*/

void Molecule::addAsReactant (Reaction *reac)
{
  /*
  ** Add the reaction to the list if it's not already in there.
  */
  itAsReactant = find (asReactant.begin (), asReactant.end (), reac);
  if (itAsReactant == asReactant.end ())
  {
    asReactant.push_back (reac);
  }
}


/*
** removeAsReactant: Remove a reaction for which the molecule is a reactant.
**
** Parameters:
**   - reac: A pointer to the reaction to remove.
*/

void Molecule::removeAsReactant (Reaction *reac)
{
  /*
  ** Remove the reaction from the list.
  */
  asReactant.remove (reac);
}


/*
** addAsProduct: Add a reaction for which the molecule is a product.
**
** Parameters:
**   - reac: A pointer to the reaction to add.
*/

void Molecule::addAsProduct (Reaction *reac)
{
  /*
  ** Add the reaction to the list if it's not already in there.
  */
  itAsProduct = find (asProduct.begin (), asProduct.end (), reac);
  if (itAsProduct == asProduct.end ())
  {
    asProduct.push_back (reac);
  }
}


/*
** removeAsProduct: Remove a reaction for which the molecule is a product.
**
** Parameters:
**   - reac: A pointer to the reaction to remove.
*/

void Molecule::removeAsProduct (Reaction *reac)
{
  /*
  ** Remove the reaction from the list.
  */
  asProduct.remove (reac);
}


/*
** addAsCatalyst: Add a reaction for which the molecule is a catalyst.
**
** Parameters:
**   - reac: A pointer to the reaction to add.
*/

void Molecule::addAsCatalyst (Reaction *reac)
{
  /*
  ** Add the reaction to the list if it's not already in there.
  */
  itAsCatalyst = find (asCatalyst.begin (), asCatalyst.end (), reac);
  if (itAsCatalyst == asCatalyst.end ())
  {
    asCatalyst.push_back (reac);
  }
}


/*
** removeAsCatalyst: Remove a reaction for which the molecule is a catalyst.
**
** Parameters:
**   - reac: A pointer to the reaction to remove.
*/

void Molecule::removeAsCatalyst (Reaction *reac)
{
  /*
  ** Remove the reaction from the list.
  */
  asCatalyst.remove (reac);
}


/*
** getNrAsReactant: Get the number of reactions for which the molecule is
**                  a reactant.
**
** Returns:
**   - The number of reaction for which this molecule is a reactant.
*/

int Molecule::getNrAsReactant ()
{
  /*
  ** Return the number of reactions.
  */
  return (asReactant.size ());
}


/*
** getNrAsProduct: Get the number of reactions for which the molecule is
**                 a product.
**
** Returns:
**   - The number of reaction for which this molecule is a product.
*/

int Molecule::getNrAsProduct ()
{
  /*
  ** Return the number of reactions.
  */
  return (asProduct.size ());
}


/*
** getNrAsCatalyst: Get the number of reactions for which the molecule is
**                  a catalyst.
**
** Returns:
**   - The number of reaction for which this molecule is a catalyst.
*/

int Molecule::getNrAsCatalyst ()
{
  /*
  ** Return the number of reactions.
  */
  return (asCatalyst.size ());
}


/*
** getAsReactantFirst: Get the first reaction for which the molecule is a
**                     reactant.
**
** Returns:
**   - A pointer to the first reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsReactantFirst ()
{
  Reaction *reac;

  /*
  ** Get the first reaction.
  */
  itAsReactant = asReactant.begin ();
  if (itAsReactant != asReactant.end ())
  {
    reac = *itAsReactant;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** getAsReactantNext: Get the next reaction for which the molecule is a
**                    reactant.
**
** Returns:
**   - A pointer to the next reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsReactantNext ()
{
  Reaction *reac;

  /*
  ** Get the next reaction.
  */
  itAsReactant++;
  if (itAsReactant != asReactant.end ())
  {
    reac = *itAsReactant;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** getAsProductFirst: Get the first reaction for which the molecule is a
**                    product.
**
** Returns:
**   - A pointer to the first reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsProductFirst ()
{
  Reaction *reac;

  /*
  ** Get the first reaction.
  */
  itAsProduct = asProduct.begin ();
  if (itAsProduct != asProduct.end ())
  {
    reac = *itAsProduct;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** getAsProductNext: Get the next reaction for which the molecule is a
**                   product.
**
** Returns:
**   - A pointer to the next reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsProductNext ()
{
  Reaction *reac;

  /*
  ** Get the next reaction.
  */
  itAsProduct++;
  if (itAsProduct != asProduct.end ())
  {
    reac = *itAsProduct;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** getAsCatalystFirst: Get the first reaction for which the molecule is a
**                     catalyst.
**
** Returns:
**   - A pointer to the first reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsCatalystFirst ()
{
  Reaction *reac;

  /*
  ** Get the first reaction.
  */
  itAsCatalyst = asCatalyst.begin ();
  if (itAsCatalyst != asCatalyst.end ())
  {
    reac = *itAsCatalyst;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** getAsCatalystNext: Get the next reaction for which the molecule is a
**                    catalyst.
**
** Returns:
**   - A pointer to the first reaction (or NULL if out of bounds).
*/

Reaction *Molecule::getAsCatalystNext ()
{
  Reaction *reac;

  /*
  ** Get the next reaction.
  */
  itAsCatalyst++;
  if (itAsCatalyst != asCatalyst.end ())
  {
    reac = *itAsCatalyst;
  }
  else
  {
    reac = NULL;
  }

  /*
  ** Return the result.
  */
  return (reac);
}


/*
** EoF: Molecule.cxx
*/
