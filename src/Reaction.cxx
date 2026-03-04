/*
** Reaction.cxx: Chemical reaction class.
**
** Wim Hordijk   Last modified: 4 March 2026
*/

#include "Reaction.h"


/*
** Reaction: The constructor.
**
** Parameters:
**   - id:  The reaction ID (can be any string).
*/

Reaction::Reaction (string id)
{
  /*
  ** Initialize the variables.
  */
  ID.assign (id);
  itReactant = reactants.begin ();
  itProduct = products.begin ();
  itCatalyst = catalysts.begin ();
  this->id = 0;
  isInSet = false;
  direction = UNI_DIR;
}


/*
** ~Reaction: The destructor.
*/

Reaction::~Reaction ()
{
  Molecule *mol;

  /*
  ** Remove this reaction from its reactants, products, and catalyst, and
  ** clear all lists.
  */
  itReactant = reactants.begin ();
  while (itReactant != reactants.end ())
  {
    mol = *itReactant;
    mol->removeAsReactant (this);
    itReactant++;
  }
  reactants.clear ();
  itProduct = products.begin ();
  while (itProduct != products.end ())
  {
    mol = *itProduct;
    mol->removeAsProduct (this);
    itProduct++;
  }
  products.clear ();
  itCatalyst = catalysts.begin ();
  while (itCatalyst != catalysts.end ())
  {
    mol = *itCatalyst;
    mol->removeAsCatalyst (this);
    itCatalyst++;
  }
  catalysts.clear ();
}


/*
** getID: Get the reaction ID.
**
** Parameters:
**   - id: A pointer to a string to hold (a copy of) the reaction ID.
*/

void Reaction::getID (string *id)
{
  /*
  ** Copy the reaction ID.
  */
  id->assign (ID);
}


/*
** getNrReactants: Get the number of reactants in the reaction.
**
** Returns:
**   - The number of reactants.
*/
int Reaction::getNrReactants ()
{
  /*
  ** Return the number of reactants.
  */
  return (reactants.size ());
}


/*
** getReactantFirst: Get the first reactant in the list.
**
** Returns:
**   - A pointer to the first reactant in the list (NULL if list is empty).
*/

Molecule *Reaction::getReactantFirst ()
{
  Molecule *mol;

  /*
  ** Get the first reactant.
  */
  itReactant = reactants.begin ();
  if (itReactant != reactants.end ())
  {
    mol = *itReactant;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** getReactantNext: Get the next reactant in the list.
**
** Returns:
**   - A pointer to the next reactant in the list (NULL if end of list).
*/

Molecule *Reaction::getReactantNext ()
{
  Molecule *mol;

  /*
  ** Get the next reactant.
  */
  itReactant++;
  if (itReactant != reactants.end ())
  {
    mol = *itReactant;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** hasReactant: Check if the reaction has a given molecule as a reactant.
**
** Parameters:
**   - mol: A molecule type.
**
** Returns:
**   - If the molecule is a reactant: true.
**   - Otherwise:                     false.
*/

bool Reaction::hasReactant (Molecule *mol)
{
  bool hasReac;

  /*
  ** Check whether the molecule is a reactant.
  **
  ** Note that we are simply comparing pointers here, so it is assumed
  ** that each molecule type is defined only once (as it should be)!
  */
  hasReac = false;
  itReactant = reactants.begin ();
  while (itReactant != reactants.end ())
  {
    if (mol == *itReactant)
    {
      hasReac = true;
      break;
    }
    itReactant++;
  }

  /*
  ** Return the result.
  */
  return (hasReac);
}


/*
** addReactant: Add a reactant to the list.
**
** Parameters:
**   - mol: The molecule to add.
*/

void Reaction::addReactant (Molecule *mol)
{
  /*
  ** Add the reactant to the list.
  */
  reactants.push_back (mol);
  mol->addAsReactant (this);
}


/*
** removeReactant: Remove a reactant from the list.
**
** Parameters:
**   - mol: The molecule to remove.
*/

void Reaction::removeReactant (Molecule *mol)
{
  /*
  ** Remove the molecule from the list.
  */
  reactants.remove (mol);
  mol->removeAsReactant (this);
}


/*
** clearReactants: Clear the reactants list.
*/

void Reaction::clearReactants ()
{
  Molecule *mol;

  /*
  ** Clear the reactants list.
  */
  itReactant = reactants.begin ();
  while (itReactant != reactants.end ())
  {
    mol = *itReactant;
    mol->removeAsReactant (this);
    itReactant++;
  }
  reactants.clear ();
  itReactant = reactants.begin ();
}


/*
** getNrProducts: Get the number of products in the reaction.
**
** Returns:
**   - The number of products.
*/
int Reaction::getNrProducts ()
{
  /*
  ** Return the number of products.
  */
  return (products.size ());
}


/*
** getProductFirst: Get the first product in the list.
**
** Returns:
**   - A pointer to the first product in the list (NULL if list is empty).
*/

Molecule *Reaction::getProductFirst ()
{
  Molecule *mol;

  /*
  ** Get the first product.
  */
  itProduct = products.begin ();
  if (itProduct != products.end ())
  {
    mol = *itProduct;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** getProductNext: Get the next product in the list.
**
** Returns:
**   - A pointer to the next product in the list (NULL if end of list).
*/

Molecule *Reaction::getProductNext ()
{
  Molecule *mol;

  /*
  ** Get the next product.
  */
  itProduct++;
  if (itProduct != products.end ())
  {
    mol = *itProduct;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** hasProduct: Check if the reaction has a given molecule as a product.
**
** Parameters:
**   - mol: A molecule type.
**
** Returns:
**   - If the molecule is a product: true.
**   - Otherwise:                    false.
*/

bool Reaction::hasProduct (Molecule *mol)
{
  bool hasProd;

  /*
  ** Check whether the molecule is a product.
  **
  ** Note that we are simply comparing pointers here, so it is assumed
  ** that each molecule type is defined only once (as it should be)!
  */
  hasProd = false;
  itProduct = products.begin ();
  while (itProduct != products.end ())
  {
    if (mol == *itProduct)
    {
      hasProd = true;
      break;
    }
    itProduct++;
  }

  /*
  ** Return the result.
  */
  return (hasProd);
}


/*
** addProduct: Add a product to the list.
**
** Parameters:
**   - mol: The molecule to add.
*/

void Reaction::addProduct (Molecule *mol)
{
  /*
  ** Add the product to the list.
  */
  products.push_back (mol);
  mol->addAsProduct (this);
}


/*
** removeProduct: Remove a product from the list.
**
** Parameters:
**   - mol: The molecule to remove.
*/

void Reaction::removeProduct (Molecule *mol)
{
  /*
  ** Remove the molecule from the list.
  */
  products.remove (mol);
  mol->removeAsProduct (this);
}


/*
** clearProducts: Clear the products list.
*/

void Reaction::clearProducts ()
{
  Molecule *mol;

  /*
  ** Clear the products list.
  */
  itProduct = products.begin ();
  while (itProduct != products.end ())
  {
    mol = *itProduct;
    mol->removeAsProduct (this);
    itProduct++;
  }
  products.clear ();
  itProduct = products.begin ();
}


/*
** getNrCatalysts: Get the number of catalysts in the reaction.
**
** Returns:
**   - The number of catalysts.
*/
int Reaction::getNrCatalysts ()
{
  /*
  ** Return the number of catalysts.
  */
  return (catalysts.size ());
}


/*
** getCatalystFirst: Get the first catalyst in the list.
**
** Returns:
**   - A pointer to the first catalyst in the list (NULL if list is empty).
*/

Molecule *Reaction::getCatalystFirst ()
{
  Molecule *mol;

  /*
  ** Get the first catalyst.
  */
  itCatalyst = catalysts.begin ();
  if (itCatalyst != catalysts.end ())
  {
    mol = *itCatalyst;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** getCatalystNext: Get the next catalyst in the list.
**
** Returns:
**   - A pointer to the next catalyst in the list (NULL if end of list).
*/

Molecule *Reaction::getCatalystNext ()
{
  Molecule *mol;

  /*
  ** Get the next catalyst.
  */
  itCatalyst++;
  if (itCatalyst != catalysts.end ())
  {
    mol = *itCatalyst;
  }
  else
  {
    mol = NULL;
  }

  /*
  ** Return the result.
  */
  return (mol);
}


/*
** hasCatalyst: Check if the reaction has a given molecule as a catalyst.
**
** Parameters:
**   - mol: A molecule type.
**
** Returns:
**   - If the molecule is a catalyst: true.
**   - Otherwise:                     false.
*/

bool Reaction::hasCatalyst (Molecule *mol)
{
  bool hasCat;

  /*
  ** Check whether the molecule is a catalyst.
  **
  ** Note that we are simply comparing pointers here, so it is assumed
  ** that each molecule type is defined only once (as it should be)!
  */
  hasCat = false;
  itCatalyst = catalysts.begin ();
  while (itCatalyst != catalysts.end ())
  {
    if (mol == *itCatalyst)
    {
      hasCat = true;
      break;
    }
    itCatalyst++;
  }

  /*
  ** Return the result.
  */
  return (hasCat);
}


/*
** addCatalyst: Add a catalyst to the list.
**
** Parameters:
**   - mol: The molecule to add.
*/

void Reaction::addCatalyst (Molecule *mol)
{
  /*
  ** Add the catalyst to the list.
  */
  catalysts.push_back (mol);
  mol->addAsCatalyst (this);
}


/*
** removeCatalyst: Remove a catalyst from the list.
**
** Parameters:
**   - mol: The molecule to remove.
*/

void Reaction::removeCatalyst (Molecule *mol)
{
  /*
  ** Remove the molecule from the list.
  */
  catalysts.remove (mol);
  mol->removeAsCatalyst (this);
}


/*
** clearCatalysts: Clear the catalysts list.
*/

void Reaction::clearCatalysts ()
{
  Molecule *mol;

  /*
  ** Clear the catalysts list.
  */
  itCatalyst = catalysts.begin ();
  while (itCatalyst != catalysts.end ())
  {
    mol = *itCatalyst;
    mol->removeAsCatalyst (this);
    itCatalyst++;
  }
  catalysts.clear ();
  itCatalyst = catalysts.begin ();
}


/*
** setDirection: Set the reaction direction.
**
** Parameters:
**   - dir: The direction to set (either UNI_DIR or BI_DIR).
*/

void Reaction::setDirection (int dir)
{
  if (dir == UNI_DIR || dir == BI_DIR)
  {
    direction = dir;
  }
}


/*
** getDirection: Get the reaction direction.
**
** Returns:
**   - Either UNI_DIR or BI_DIR.
*/

int Reaction::getDirection ()
{
  return (direction);
}


/*
** EoF: Reaction.cxx
*/
