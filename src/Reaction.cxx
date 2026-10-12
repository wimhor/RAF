/*
** Reaction.cxx: Chemical reaction class.
**
** Wim Hordijk   Last modified: 6 October 2026
*/

#include "Reaction.h"


/*
** Reaction: The constructor.
**
** Arguments:
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
  itCatList = catalysts.begin ();
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
** Arguments:
**   - id: A pointer to a string to hold (a copy of) the reaction ID.
*/

void Reaction::getID (string& id)
{
  /*
  ** Copy the reaction ID.
  */
  id.assign (ID);
}


/*
** getNrReactants: Get the number of reactants in the reaction.
**
** Returns:
**   The number of reactants.
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
**   A pointer to the first reactant in the list (NULL if list is empty).
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
**   A pointer to the next reactant in the list (NULL if end of list).
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
** Arguments:
**   - mol: A molecule type.
**
** Returns:
**   If the molecule is a reactant: true.
**   Otherwise:                     false.
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
** Arguments:
**   - mol: A molecule type.
**
** Returns:
**   If the molecule is a reactant: Its stoichiometry.
**   Otherwise:                     0.
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
** Arguments:
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
** Arguments:
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
**   The number of products.
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
**   A pointer to the first product in the list (NULL if list is empty).
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
**   A pointer to the next product in the list (NULL if end of list).
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
** Arguments:
**   - mol: A molecule type.
**
** Returns:
**   If the molecule is a product: true.
**   Otherwise:                    false.
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
** Arguments:
**   - mol: A molecule type.
**
** Returns:
**   If the molecule is a product: Its stoichiometry.
**   Otherwise:                    0.
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
** Arguments:
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
** Arguments:
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
**   The number of catalysts.
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
** Arguments:
**   - A reference to a list of molecules (to be modified).
**
** Returns:
**   If there is at least one catalyst: 1 ('cat' will contain the first catalyst).
**   Otherwise:                         0 ('cat' remains unchanged).
*/

int Reaction::getCatalystFirst (list<Molecule*>& cat)
{
  int status;

  /*
  ** Get the first catalyst, if there is one.
  */
  status = 0;
  itCatList = catalysts.begin ();
  if (itCatList != catalysts.end ())
  {
    cat.clear ();
    itCatalyst = itCatList->begin ();
    while (itCatalyst != itCatList->end ())
    {
      cat.push_back (*itCatalyst);
      itCatalyst++;
    }
    status = 1;
  }

  /*
  ** Return the result.
  */
  return (status);
}


/*
** getCatalystNext: Get the next catalyst in the list.
**
** Arguments:
**   - A reference to a list of molecules (to be modified).
**
** Returns:
**   If there is another catalyst: 1 ('cat' will contain the next catalyst).
**   Otherwise:                    0 ('cat' remains unchanged).
*/

int Reaction::getCatalystNext (list<Molecule*>& cat)
{
  int status;

  /*
  ** Get the next catalyst.
  */
  status = 0;
  itCatList++;
  if (itCatList != catalysts.end ())
  {
    cat.clear ();
    itCatalyst = itCatList->begin ();
    while (itCatalyst != itCatList->end ())
    {
      cat.push_back (*itCatalyst);
      itCatalyst++;
    }
    status = 1;
  }

  /*
  ** Return the result.
  */
  return (status);
}


/*
** hasCatalyst: Check if the reaction has a given molecule as a catalyst, possibly
**              as part of a catalyst complex.
**
** Arguments:
**   - mol: A molecule type.
**
** Returns:
**   If the molecule is a catalyst: true.
**   Otherwise:                     false.
*/

bool Reaction::hasCatalyst (Molecule *mol)
{
  bool hasCat;

  /*
  ** See if the given molecule is in the catalysts list.
  */
  hasCat = false;
  itCatList = catalysts.begin ();
  while (itCatList != catalysts.end ())
  {
    itCatalyst = find (itCatList->begin (), itCatList->end (), mol);
    if (itCatalyst != itCatList->end ())
    {
      hasCat = true;
      break;
    }
    itCatList++;
  }

  /*
  ** Return the result.
  */
  return (hasCat);
}


/*
** addCatalyst: Add a catalyst to the list. Note that a check for duplicates is *not*
**              performed!
**
** Arguments:
**   - cat: A reference to a list of molecules to be added.
*/

void Reaction::addCatalyst (list<Molecule*>& cat)
{
  Molecule        *mol;
  list<Molecule*> *newCat;
  
  /*
  ** Add the catalyst complex to the list, and add the current reaction to each
  ** molecule's "as catalyst" list.
  */
  newCat = new list<Molecule*> ();
  itCatalyst = cat.begin ();
  while (itCatalyst != cat.end ())
  {
    mol = *itCatalyst;
    newCat->push_back (mol);
    mol->addAsCatalyst (this);
    itCatalyst++;
  }
  catalysts.push_back (*newCat);
}


/*
** addMultiCatalyst: Add a "multi-catalyst", i.e., a catalyst that needs to be present
**                   together with any other catalysts already in the list.
**                   Note that a check for duplicates is *not* performed!
**
** Arguments:
**   - mol: A molecule to be added as multi-catalyst.
*/

void Reaction::addMultiCatalyst (Molecule *cat)
{
  /*
  ** Add the multi-catalyst to each catalyst already in the list, and add the current
  ** reaction to the multi-catalyst's "as catalyst" list.
  */
  itCatList = catalysts.begin ();
  while (itCatList != catalysts.end ())
  {
    itCatList->push_back (cat);
    cat->addAsCatalyst (this);
    itCatList++;
  }
}


/*
** removeCatalyst: Remove a catalyst from the list.
**
** Arguments:
**   - A reference to a list of molecules (to be removed).
*/

void Reaction::removeCatalyst (list<Molecule*>& cat)
{
  Molecule *mol;
  
  /*
  ** Remove the catalyst from the list.
  */
  catalysts.remove (cat);
  itCatalyst = cat.begin ();
  while (itCatalyst != cat.end ())
  {
    mol = *itCatalyst;
    if (!this->hasCatalyst (mol))
    {
      mol->removeAsCatalyst (this);
    }
    itCatalyst++;
  }
  cat.clear ();
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
  itCatList = catalysts.begin ();
  while (itCatList != catalysts.end ())
  {
    itCatalyst = itCatList->begin ();
    while (itCatalyst != itCatList->end ())
    {
      mol = *itCatalyst;
      mol->removeAsCatalyst (this);
      itCatalyst++;
    }
    itCatList->clear ();
    itCatList++;
  }
  catalysts.clear ();
  itCatList = catalysts.begin ();
}


/*
** setDirection: Set the reaction direction.
**
** Arguments:
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
**   Either UNI_DIR or BI_DIR.
*/

int Reaction::getDirection ()
{
  return (direction);
}


/*
** EoF: Reaction.cxx
*/
