/*
** Reaction.cxx: Chemical reaction class.
**
** Wim Hordijk   Last modified: 23 March 2026
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
  direction = UNI_DIR;
  applied = false;
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
  clearReactants ();
  clearProducts ();
  clearCatalysts ();
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
  ** See if the given molecule is in the reactants list.
  */
  itReactant = find (reactants.begin (), reactants.end (), mol);
  if (itReactant != reactants.end ())
  {
    hasReac = true;
  }
  else
  {
    hasReac = false;
  }

  /*
  ** Return the result.
  */
  return (hasReac);
}


/*
** getReacStoich: Get the stoichiometry of a reactant.
**
** Parameters:
**   - mol: A molecule type.
**
** Returns:
**   - If the molecule is a reactant: Its stoichiometry.
**   - Otherwise:                     0.
*/

int Reaction::getReacStoich (Molecule *mol)
{
  int n;

  /*
  ** Get the stoichiometry of the given reactant.
  */
  itReactant = find (reactants.begin (), reactants.end (), mol);
  if (itReactant != reactants.end ())
  {
    n = reacStoich[mol];
  }
  else
  {
    n = 0;
  }

  /*
  ** Return the result.
  */
  return (n);
}


/*
** addReactant: Add a reactant to the list of reactants. If the reactant already
**              exists, increase its stoichiometry.
**
** Parameters:
**   - mol: The molecule to add.
**   - n:   The stoichiometry of the reactant (default = 1).
*/

void Reaction::addReactant (Molecule *mol, int n)
{
  /*
  ** If the reactant does not exist yet, add it to the list. Otherwise, increase
  ** its stoichiometry.
  */
  itReactant = find (reactants.begin (), reactants.end (), mol);
  if (itReactant == reactants.end ())
  {
    reactants.push_back (mol);
    mol->addAsReactant (this);
    reacStoich[mol] = n;
  }
  else
  {
    reacStoich[mol] += n;
  }
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
  reacStoich.erase (mol);
}


/*
** clearReactants: Clear the reactants list.
*/

void Reaction::clearReactants ()
{
  Molecule *mol;

  /*
  ** Remove this reaction from all its reactants and clear the list.
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
  reacStoich.clear ();
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
  ** See if the given molecule is in the products list.
  */
  itProduct = find (products.begin (), products.end (), mol);
  if (itProduct != products.end ())
  {
    hasProd = true;
  }
  else
  {
    hasProd = false;
  }

  /*
  ** Return the result.
  */
  return (hasProd);
}


/*
** getProdStoich: Get the stoichiometry of a product.
**
** Parameters:
**   - mol: A molecule type.
**
** Returns:
**   - If the molecule is a product: Its stoichiometry.
**   - Otherwise:                    0.
*/

int Reaction::getProdStoich (Molecule *mol)
{
  int n;

  /*
  ** Get the stoichiometry of the given product.
  */
  itProduct = find (products.begin (), products.end (), mol);
  if (itProduct != products.end ())
  {
    n = prodStoich[mol];
  }
  else
  {
    n = 0;
  }

  /*
  ** Return the result.
  */
  return (n);
}


/*
** addProduct: Add a product to the list. If the product already exists, increase
**             its stoichiometry.
**
** Parameters:
**   - mol: The molecule to add.
**   - n:   The stoichiometry of the product (default = 1).
*/

void Reaction::addProduct (Molecule *mol, int n)
{
  /*
  ** If the product does not yet exist, add it to the list. Otherwise, increase
  ** its stoichiometry.
  */
  itProduct = find (products.begin (), products.end (), mol);
  if (itProduct == products.end ())
  {
    products.push_back (mol);
    mol->addAsProduct (this);
    prodStoich[mol] = n;
  }
  else
  {
    prodStoich[mol] += n;
  }
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
  prodStoich.erase (mol);
}


/*
** clearProducts: Clear the products list.
*/

void Reaction::clearProducts ()
{
  Molecule *mol;

  /*
  ** Remove this reaction from its products and clear the list.
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
  prodStoich.clear ();
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
  ** See if the given molecule is in the catalysts list.
  */
  itCatalyst = find (catalysts.begin (), catalysts.end (), mol);
  if (itCatalyst != catalysts.end ())
  {
    hasCat = true;
  }
  else
  {
    hasCat = false;
  }

  /*
  ** Return the result.
  */
  return (hasCat);
}


/*
** addCatalyst: Add a catalyst to the list if it does not already exist.
**
** Parameters:
**   - mol: The molecule to add.
*/

void Reaction::addCatalyst (Molecule *mol)
{
  /*
  ** Add the catalyst to the list if it's not already there.
  */
  itCatalyst = find (catalysts.begin (), catalysts.end (), mol);
  if (itCatalyst == catalysts.end ())
  {
    catalysts.push_back (mol);
    mol->addAsCatalyst (this);
  }
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
  ** Remove this reaction from its catalysts and clear the list.
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
