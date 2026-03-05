/*
** ReacSet.cxx: Implementation of the reaction set class.
**
** Wim Hordijk   Last modified: 5 March 2026
*/

#include <string.h>
#include <iostream>
#include "def.h"
#include "ReacSet.h"

using namespace std;


/*
** ReacSet: Constructor.
*/

ReacSet::ReacSet ()
{
  /*
  ** Initialize everything.
  */
  itMolecule = molecules.begin ();
  itReaction = reactions.begin ();
  itFoodSet = foodSet.begin ();
  maxRAF = NULL;
}


/*
** ~ReacSet: Destructor.
*/

ReacSet::~ReacSet ()
{
  /*
  ** Clear the lists.
  */
  molecules.clear ();
  reactions.clear ();
  foodSet.clear ();
  closure.clear ();
  molMap.clear ();
  if (maxRAF != NULL)
  {
    delete maxRAF;
  }
}


/*
** getNrMolecules: Get the number of molecules in the reaction set.
**
** Returns:
**   - The number of molecules in the reaction set.
*/

int ReacSet::getNrMolecules ()
{
  /*
  ** Return the number of molecules.
  */
  return (molecules.size ());
}


/*
** getMoleculeFirst: Get the first element from the molecule list.
**
** Returns:
**   - A pointer to the first element in the molecule list (NULL if the
**     molecule list is empty).
*/

Molecule *ReacSet::getMoleculeFirst ()
{
  Molecule *mol;

  /*
  ** Get the pointer to the first element in the list.
  */
  itMolecule = molecules.begin ();
  if (itMolecule != molecules.end ())
  {
    mol = *itMolecule;
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
** getMoleculeNext: Get the next element from the molecule list. This assumes
**                  that the list has not been changed since the previous call.
**
** Returns:
**   - A pointer to the next element in the molecule list (NULL if end of list
       is reached).
*/

Molecule *ReacSet::getMoleculeNext ()
{
  Molecule *mol;

  /*
  ** Get the pointer to the next element.
  */
  itMolecule++;
  if (itMolecule != molecules.end ())
  {
    mol = *itMolecule;
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
** getMoleculeBySeq: Get an element from the molecule list by its sequence
**                   string.
**
** Parameters:
**   - seq: The molecule sequence (a string).
**
** Returns:
**   - A pointer to the element in the molecule list with the given
**     sequence (NULL if nonexistent).
*/

Molecule *ReacSet::getMoleculeBySeq (string seq)
{
  string                           s;
  Molecule                        *mol;
  map<string,Molecule*>::iterator  it;

  /*
  ** Get the pointer to the element with the given sequence.
  */
  it = molMap.find (seq);
  if (it != molMap.end())
  {
    mol = it->second;
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
** addMolecule: Add an element to the molecule list. If a molecule with the
**              same sequence already exists, no new element is added.
**
** Parameters:
**   - mol: A pointer to the element to add.
*/

void ReacSet::addMolecule (Molecule *mol)
{
  string                          seq;
  map<string,Molecule*>::iterator it;

  /*
  ** See if an element with the given sequence already exists. If not, add it
  ** to the list.
  */
  mol->getSequence (&seq);
  it = molMap.find (seq);
  if (it == molMap.end())
  {
    molecules.push_back (mol);
    molMap[seq] = mol;
  }
}


/*
** removeMolecule: Remove an element from the molecule list.
**
** Parameters:
**   - mol: A pointer to the element to remove.
*/

void ReacSet::removeMolecule (Molecule *mol)
{
  string seq;

  /*
  ** Remove the molecule from the list.
  */
  molecules.remove (mol);
  mol->getSequence (&seq);
  molMap.erase (seq);
}


/*
** clearMolecules: Clear the molecule list.
*/

void ReacSet::clearMolecules ()
{
  /*
  ** Clear the molecule list.
  */
  molecules.clear ();
  itMolecule = molecules.begin ();
  molMap.clear ();
}


/*
** getNrFoodMolecules: Get the number of molecules in the food set.
**
** Returns:
**   - The number of molecules in the food set.
*/

int ReacSet::getNrFoodMolecules ()
{
  /*
  ** Return the number of food molecules.
  */
  return (foodSet.size ());
}


/*
** getFoodSetFirst: Get the first molecule in the food set.
**
** Returns:
**   - A pointer to the first molecule in the food set (NULL if list is empty).
*/

Molecule *ReacSet::getFoodSetFirst ()
{
  Molecule *mol;

  /*
  ** Get the first molecule.
  */
  itFoodSet = foodSet.begin ();
  if (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
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
** getFoodSetNext: Get the next molecule in the food set.
**
** Returns:
**   - A pointer to the next molecule in the food set (NULL if end of list).
*/

Molecule *ReacSet::getFoodSetNext ()
{
  Molecule *mol;

  /*
  ** Get the next molecule.
  */
  itFoodSet++;
  if (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
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
** isInFoodSet: Check whether a molecule is in the food set.
**
** Parameters:
**   - mol: The molecule to check for.
**
** Returns:
**   - If the molecule is in the food set: true.
**   - Otherwise:                          false.
*/

bool ReacSet::isInFoodSet (Molecule *mol)
{
  bool                      inFoodSet;
  list<Molecule*>::iterator itFood;

  /*
  ** See if the given element is in the food set.
  */
  itFood = find (foodSet.begin (), foodSet.end (), mol);
  if (itFood != foodSet.end ())
  {
    inFoodSet = true;
  }
  else
  {
    inFoodSet = false;
  }

  /*
  ** Return the result.
  */
  return (inFoodSet);
}


/*
** addToFoodSet: Add a molecule to the food set.
**
** Parameters:
**   - mol: The molecule to add.
*/

void ReacSet::addToFoodSet (Molecule *mol)
{
  /*
  ** Add the molecule to the food set.
  */
  foodSet.push_back (mol);
}


/*
** removeFromFoodSet: Remove a molecule from the food set.
**
** Parameters:
**   - mol: The molecule to remove.
*/

void ReacSet::removeFromFoodSet (Molecule *mol)
{
  /*
  ** Remove the molecule from the food set.
  */
  foodSet.remove (mol);
}


/*
** clearFoodSet: Clear the food set list.
*/

void ReacSet::clearFoodSet ()
{
  /*
  ** Clear the food set list.
  */
  foodSet.clear ();
  itFoodSet = foodSet.begin ();
}


/*
** getNrReactions: Get the number of reactions in the reaction set.
**
** Returns:
**   - The number of reactions in the reaction set.
*/

int ReacSet::getNrReactions ()
{
  /*
  ** Return the number of reactions.
  */
  return (reactions.size ());
}


/*
** getReactionFirst: Get the first reaction in the list.
**
** Returns:
**   - A pointer to the first reaction in the list (NULL if list is empty).
*/

Reaction *ReacSet::getReactionFirst ()
{
  Reaction *reac;

  /*
  ** Get the first reaction.
  */
  itReaction = reactions.begin ();
  if (itReaction != reactions.end ())
  {
    reac = *itReaction;
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
** getReactionNext: Get the next reaction in the list.
**
** Returns:
**   - A pointer to the next reaction in the list (NULL if end of list).
*/

Reaction *ReacSet::getReactionNext ()
{
  Reaction *reac;

  /*
  ** Get the next reaction.
  */
  itReaction++;
  if (itReaction != reactions.end ())
  {
    reac = *itReaction;
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
** isInReacSet: Check whether a reaction is in the reaction set.
**
** Parameters:
**   - reac: The reaction to check for.
**
** Returns:
**   - If the reaction is in the reaction set: true.
**   - Otherwise:                              false.
*/

bool ReacSet::isInReacSet (Reaction *reac)
{
  bool                      inReacSet;
  list<Reaction*>::iterator itReac;

  /*
  ** See if the given reaction is in the reaction set.
  */
  itReac = find (reactions.begin (), reactions.end (), reac);
  if (itReac != reactions.end ())
  {
    inReacSet = true;
  }
  else
  {
    inReacSet = false;
  }

  /*
  ** Return the result.
  */
  return (inReacSet);
}


/*
** addReaction: Add a reaction to the list.
**
** Parameters:
**   - reac: The reaction to add.
*/

void ReacSet::addReaction (Reaction *reac)
{
  /*
  ** Add the reaction to the list.
  */
  reactions.push_back (reac);
}


/*
** removeReaction: Remove a reaction from the list.
**
** Parameters:
**   - reac: The reaction to remove.
*/

void ReacSet::removeReaction (Reaction *reac)
{
  /*
  ** Remove the reaction from the list.
  */

  reactions.remove (reac);
}


/*
** clearReactions: Clear the reaction list.
*/

void ReacSet::clearReactions ()
{
  /*
  ** Clear the reaction list.
  */
  reactions.clear ();
  itReaction = reactions.begin ();
}


/*
** applyRAF: Apply the RAF algorithm to the current reaction set. The resulting
**           reaction set is the maxRAF, or is empty if there is no RAF.
**
** Returns:
**   The size of the found RAF set (zero if empty).
*/

int ReacSet::applyRAF ()
{
  bool      reactionsRemoved, remove;
  Molecule *mol;
  Reaction *reac;

  /*
  ** While reactions could be removed and the current reaction set is not empty,
  ** iterate the RAF algorithm.
  */
  reactionsRemoved = true;
  while (reactionsRemoved && reactions.size () > 0)
  {
    /*
    ** Compute the closure of the food set.
    */
    computeClosure ();
    /*
    ** Remove all reactions for which not all the reactants and at least one
    ** catalyst are in the closure of the food set.
    */
    reactionsRemoved = false;
    itReaction = reactions.begin ();
    while (itReaction != reactions.end ())
    {
      reac = *itReaction;
      /*
      ** Check the reactants.
      **
      ** Note: In case of a bi-directional reaction, if all products are in the closure
      **       then all reactants will be too, so no need to check both directions.
      */
      remove = false;
      mol = reac->getReactantFirst ();
      while (mol != NULL)
      {
	if (!isInClosure (mol))
	{
	  remove = true;
	  break;
	}
	mol = reac->getReactantNext ();
      }
      /*
      ** Check catalysts, if still necessary.
      */
      if (!remove)
      {
	remove = true;
	mol = reac->getCatalystFirst ();
	while (mol != NULL)
	{
	  if (isInClosure (mol))
	  {
	    remove = false;
	    break;
	  }
	  mol = reac->getCatalystNext ();
	}
      }
      /*
      ** Remove the reaction, if so indicated.
      */
      if (remove)
      {
	itReaction = reactions.erase (itReaction);
	reactionsRemoved = true;
      }
      else
      {
	itReaction++;
      }
    }
  }

  /*
  ** Return the size of the resulting reaction set.
  */
  return (reactions.size ());
}


/*
** findMaxRAF: Find the maximal RAF set in the current reaction set.
**
** Returns:
**   - The size of the maximal RAF set (zero if empty).
*/

int ReacSet::findMaxRAF ()
{
  int       size;
  string    id;
  Reaction *reac;

  /*
  ** Create a new reaction set to contain the maxRAF and copy the current
  ** reaction set's content to it.
  */
  maxRAF = new ReacSet ();
  maxRAF = this;
  
  /*
  ** Apply the RAF algorithm on the new set.
  */
  size = maxRAF->applyRAF ();

  /*
  ** Return the size of the maximal RAF set.
  */
  return (size);
}


/*
** getMaxRAFFirst: Get the first reaction in the maxRAF set.
**
** Returns:
**   - A pointer to the first reaction in the maxRAF (NULL if it is empty).
*/

Reaction *ReacSet::getMaxRAFFirst ()
{
  Reaction *reac;

  /*
  ** Get the first reaction.
  */
  if (maxRAF != NULL)
  {
    reac = maxRAF->getReactionFirst ();
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
** getMaxRAFNext: Get the next reaction in the maxRAF set.
**
** Returns:
**   - A pointer to the next reaction in the maxRAF (NULL if end of list).
*/

Reaction *ReacSet::getMaxRAFNext ()
{
  Reaction *reac;

  /*
  ** Get the next reaction.
  */
  if (maxRAF != NULL)
  {
    reac = maxRAF->getReactionNext ();
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
** isInMaxRAF: Check whether a reaction is in the maxRAF.
**
** Parameters:
**   - reac: The reaction to check for.
**
** Returns:
**   - If the reaction is in the maxRAF: true.
**   - Otherwise:                        false.
*/

bool ReacSet::isInMaxRAF (Reaction *reac)
{
  bool                      inMaxRAF;
  list<Reaction*>::iterator itRAF;

  /*
  ** See if the given element is in the maxRAF.
  */
  inMaxRAF = maxRAF->isInReacSet (reac);
  
  /*
  ** Return the result.
  */
  return (inMaxRAF);
}


/*
** isInClosure: Check whether a molecule is in the current closure of the food set.
**
** Parameters:
**   - mol: The molecule to check for.
**
** Returns:
**   - If the molecule is in the closure: true.
**   - Otherwise:                         false.
*/

bool ReacSet::isInClosure (Molecule *mol)
{
  bool                      inClosure;
  list<Molecule*>::iterator itMol;

  /*
  ** See if the given element is in the closure.
  */
  itMol = find (closure.begin (), closure.end (), mol);
  if (itMol != closure.end ())
  {
    inClosure = true;
  }
  else
  {
    inClosure = false;
  }

  /*
  ** Return the result.
  */
  return (inClosure);
}


/*
** computeClosure: Compute the closure of the food set.
*/

void ReacSet::computeClosure ()
{
  Molecule                  *mol, *r, *p;
  Reaction                  *reac;
  bool                       apply;
  string                     seq;
  list<Molecule*>::iterator  itMolecule;
  list<Reaction*>::iterator  itReac;

  /*
  ** Clear the closure and copy all food molecules to it.
  */
  closure.clear ();
  itFoodSet = foodSet.begin ();
  while (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
    closure.push_back (mol);
    itFoodSet++;
  }

  /*
  ** Iteratively construct the closure of the food set.
  */
  itClosure = closure.begin ();
  while (itClosure != closure.end ())
  {
    /*
    ** Get the next molecule from the closure so far.
    */
    mol = *itClosure;
    /*
    ** Check all current reactions for which the current molecule is a reactant
    ** and see if they can be applied.
    */
    reac = mol->getAsReactantFirst ();
    while (reac != NULL && isInReacSet (reac))
    {
      /*
      ** Check all reactants.
      */
      apply = true;
      r = reac->getReactantFirst ();
      while (r != NULL)
      {
	if (!isInClosure (r))
	{
	  apply = false;
	  break;
	}
	r = reac->getReactantNext ();
      }
      /*
      ** If the reaction can be applied, add all products to the closure if
      ** they are not already in there.
      */
      if (apply)
      {
	p = reac->getProductFirst ();
	while (p != NULL)
	{
	  if (!isInClosure (p))
	  {
	    closure.push_back (p);
	  }
	  p = reac->getProductNext ();
	}
      }
      /*
      ** Get the next reaction.
      */
      reac = mol->getAsReactantNext ();
    }
    /*
    ** Check all bi-directional reactions for which the current molecule is a product
    ** and see if they can be applied.
    */
    reac = mol->getAsProductFirst ();
    while (reac != NULL && isInReacSet (reac))
    {
      /*
      ** If the reaction is bi-directional, check all products.
      */
      apply = false;
      if (reac->getDirection () == BI_DIR)
      {
	apply = true;
	p = reac->getProductFirst ();
	while (p != NULL)
	{
	  if (!isInClosure (p))
	  {
	    apply = false;
	    break;
	  }
	  p = reac->getProductNext ();
	}
      }
      /*
      ** If the reaction can be applied, add all reactants to the closure if
      ** they are not already in there.
      */
      if (apply)
      {
	r = reac->getReactantFirst ();
	while (r != NULL)
	{
	  if (!isInClosure (r))
	  {
	    closure.push_back (r);
	  }
	  r = reac->getReactantNext ();
	}
      }
      /*
      ** Get the next reaction.
      */
      reac = mol->getAsProductNext ();
    }
    /*
    ** Get the next molecule in the current closure.
    */
    itClosure++;
  }
  
  /*
  ** Print the closure (for debugging purposes).
  */
  cout << "Closure (" << closure.size () << "): ";
  itMolecule = closure.begin ();
  while (itMolecule != closure.end ())
  {
    mol = *itMolecule;
    mol->getSequence (&seq);
    cout << seq << " ";
    itMolecule++;
  }
  cout << endl;
}


/*
** readFromFile: Read a reaction set from an input file stream.
**
** Parameters:
**   - ifs: The input file stream to read from.
**
** Returns:
**   - If reaction set could be read successfully:  0.
**   - Otherwise:                                  -1.
*/

int ReacSet::readFromFile (ifstream& is)
{
  int       n, len, status, lineNr;
  char      s[1024];
  bool      bidirectional;
  string    line, label, reactants, products, catalysts;
  size_t    pos;
  Molecule *mol;
  Reaction *reac, *bReac;

  status = 0;
  lineNr = 0;
  
  /*
  ** Clear the current reaction set.
  */
  molecules.clear ();
  reactions.clear ();
  foodSet.clear ();

  /*
  ** Read the reactions.
  */
  is.getline (s, 1024);
  lineNr++;
  if (strcmp (s, "#Reactions") != 0)
  {
    status = -1;
    cerr << "First line in input file should be '#Reactions'" << endl;
    goto End_of_Routine;
  }
  is.getline (s, 1024);
  lineNr++;
  while (strcmp (s, "#Food") != 0)
  {
    line.assign (s);
    /*
    ** Get reaction ID.
    */
    if ((pos = line.find (':')) == string::npos)
    {
      status = -1;
      cerr << "No ':' present in line " << lineNr << " of input file." << endl;
      goto End_of_Routine;
    }
    label.assign (line, 0, pos);
    reac = new Reaction (label);
    line.erase (0, pos+1);
    /*
    ** Reactants.
    */
    if ((pos = line.find_first_of ("<=")) == string::npos)
    {
      status = -1;
      cerr << "No valid reaction arrow in line " << lineNr << " of input file." << endl
	   << "  (should be '=>' or '<=>')." << endl;
      goto End_of_Routine;
    }
    reactants.assign (line, 0, pos);
    if (line.compare (pos+1, 2, "=>") == 0)
    {
      reac->setDirection (UNI_DIR);
      len = 2;
    }
    else if (line.compare (pos+1, 3, "<=>") == 0)
    {
      reac->setDirection (BI_DIR);
      len = 3;
    }
    else
    {
      status = -1;
      cerr << "No valid reaction arrow in line " << lineNr << " of input file." << endl
	   << "  (should be '=>' or '<=>')." << endl;
      goto End_of_Routine;
    }
    line.erase (0, pos+len);
    
    
    
    token1 = strtok_r (NULL, ";", &saveptr1);
    token2 = strtok_r (token1, " ", &saveptr2);
    while (token2 != NULL)
    {
      n = -1;
      if (strcmp (token2, "+") == 0)
      {
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else if (strcmp (token2, "=>") == 0)
      {
	reac->setDirection (UNI_DIR);
	token2 = NULL;
      }
      else if (strcmp (token2, "<=>") == 0)
      {
	reac->setDirection (BI_DIR);
	token2 = NULL;
      }
      else if ((sscanf (token2, "%d%c", &n, &c) != 2) && n != -1)
      {
	stoichiometry = n;
	token2 = strtok_r (NULL, " ", &saveptr2);
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	for (j = 1; j <= stoichiometry; j++)
	{
	  reac->addReactant (mol);
	}
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addReactant (mol);
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
    }
    /*
    ** Products.
    */
    token2 = strtok_r (NULL, " ", &saveptr2);
    while (token2 != NULL)
    {
      n = -1;
      if (strcmp (token2, "+") == 0)
      {
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else if ((sscanf (token2, "%d%c", &n, &c) != 2) && n != -1)
      {
	stoichiometry = n;
	token2 = strtok_r (NULL, " ", &saveptr2);
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	for (j = 1; j <= stoichiometry; j++)
	{
	  reac->addProduct (mol);
	}
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addProduct (mol);
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
    }
    /*
    ** Catalysts.
    */
    token1 = strtok_r (NULL, ";", &saveptr1);
    //cout << token1 << endl;
    if (strchr (token1, '(') != NULL)
    {
      token1 = parseCatalystRule (token1);
    }
    //cout << token1 << endl;
    token2 = strtok_r (token1, " ", &saveptr2);
    while (token2 != NULL)
    {
      if (strchr (token2, '&') != NULL)
      {
	if (addCatalystCompound (reac, token2) == -1)
	{
	  nrCat = -1;
	  goto End_of_Routine;
	}
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addCatalyst (mol);
	nrCat++;
      }
      token2 = strtok_r (NULL, " ", &saveptr2);
    }
    /*
    ** Add the reaction to the reaction set and read the next line.
    */
    addReaction (reac);
    is.getline (s, 1024);
  }
  /*
  ** Read the food set.
  */
  is.getline (s, 1024);
  while (!is.eof ())
  {
    if ((mol = getMoleculeBySeq (s)) == NULL)
    {
      mol = new Molecule (s);
      addMolecule (mol);
    }
    addToFoodSet (mol);
    is.getline (s, 1024);
  }
  
  /*
  ** Reset the list iterators.
  */
  itMolecule = molecules.begin ();
  itReaction = reactions.begin ();

  /*
  ** Return the status.
  */
 End_of_Routine:
  return (nrCat);
}


/*
** readFromFile2: Read a reaction set from an input file stream (original version).
**
** Parameters:
**   - ifs: The input file stream to read from.
**
** Returns:
**   - If reaction set could be read successfully:  The number of catalysis events.
**   - Otherwise:                                  -1.
*/

int ReacSet::readFromFile2 (ifstream& is)
{
  int       i, j, nrMols, nrReacs, nrFSet, n, nrCat, stoichiometry;
  char      s[1024], seq[1024], *token1, *token2, *saveptr1, *saveptr2, c;
  float     rate;
  bool      bidirectional;
  string    id;
  Molecule *mol;
  Reaction *reac, *bReac;

  nrCat = 0;

  /*
  ** Clear the current reaction set.
  */
  molecules.clear ();
  reactions.clear ();
  foodSet.clear ();

  /*
  ** Read the reactions.
  */
  is.getline (s, 1024);
  if (strcmp (s, "#Reactions") != 0)
  {
    nrCat = -1;
    cerr << "First line in input file should be '#Reactions'" << endl;
    goto End_of_Routine;
  }
  is.getline (s, 1024);
  while (strcmp (s, "#Food") != 0)
  {
    /*
    ** Reaction ID.
    */
    token1 = strtok_r (s, ":", &saveptr1);
    reac = new Reaction (token1);
    /*
    ** Reactants.
    */
    token1 = strtok_r (NULL, ";", &saveptr1);
    token2 = strtok_r (token1, " ", &saveptr2);
    while (token2 != NULL)
    {
      n = -1;
      if (strcmp (token2, "+") == 0)
      {
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else if (strcmp (token2, "=>") == 0)
      {
	reac->setDirection (UNI_DIR);
	token2 = NULL;
      }
      else if (strcmp (token2, "<=>") == 0)
      {
	reac->setDirection (BI_DIR);
	token2 = NULL;
      }
      else if ((sscanf (token2, "%d%c", &n, &c) != 2) && n != -1)
      {
	stoichiometry = n;
	token2 = strtok_r (NULL, " ", &saveptr2);
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	for (j = 1; j <= stoichiometry; j++)
	{
	  reac->addReactant (mol);
	}
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addReactant (mol);
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
    }
    /*
    ** Products.
    */
    token2 = strtok_r (NULL, " ", &saveptr2);
    while (token2 != NULL)
    {
      n = -1;
      if (strcmp (token2, "+") == 0)
      {
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else if ((sscanf (token2, "%d%c", &n, &c) != 2) && n != -1)
      {
	stoichiometry = n;
	token2 = strtok_r (NULL, " ", &saveptr2);
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	for (j = 1; j <= stoichiometry; j++)
	{
	  reac->addProduct (mol);
	}
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addProduct (mol);
	token2 = strtok_r (NULL, " ", &saveptr2);
      }
    }
    /*
    ** Catalysts.
    */
    token1 = strtok_r (NULL, ";", &saveptr1);
    //cout << token1 << endl;
    if (strchr (token1, '(') != NULL)
    {
      token1 = parseCatalystRule (token1);
    }
    //cout << token1 << endl;
    token2 = strtok_r (token1, " ", &saveptr2);
    while (token2 != NULL)
    {
      if (strchr (token2, '&') != NULL)
      {
	if (addCatalystCompound (reac, token2) == -1)
	{
	  nrCat = -1;
	  goto End_of_Routine;
	}
      }
      else
      {
	if ((mol = getMoleculeBySeq (token2)) == NULL)
	{
	  mol = new Molecule (token2);
	  addMolecule (mol);
	}
	reac->addCatalyst (mol);
	nrCat++;
      }
      token2 = strtok_r (NULL, " ", &saveptr2);
    }
    /*
    ** Add the reaction to the reaction set and read the next line.
    */
    addReaction (reac);
    is.getline (s, 1024);
  }
  /*
  ** Read the food set.
  */
  is.getline (s, 1024);
  while (!is.eof ())
  {
    if ((mol = getMoleculeBySeq (s)) == NULL)
    {
      mol = new Molecule (s);
      addMolecule (mol);
    }
    addToFoodSet (mol);
    is.getline (s, 1024);
  }
  
  /*
  ** Reset the list iterators.
  */
  itMolecule = molecules.begin ();
  itReaction = reactions.begin ();

  /*
  ** Return the status.
  */
 End_of_Routine:
  return (nrCat);
}


/*
** writeToFile: Write the reaction set to an output file stream.
**
** Parameters:
**   - os: The output file stream to write to.
*/

void ReacSet::writeToFile (ofstream& os)
{
  string    s;
  Molecule *mol;
  Reaction *reac;

  /*
  ** Write the reaction set.
  **
  ** Meta-data.
  */
  os << "<meta-data>" << endl;
  os << "nrMolecules = " << molecules.size () << endl;
  os << "nrFoodSet   = " << foodSet.size () << endl;
  os << "nrReactions = " << reactions.size () << endl;
  os << endl;

  /*
  ** Molecules.
  */
  os << "<molecules>" << endl;
  itMolecule = molecules.begin ();
  while (itMolecule != molecules.end ())
  {
    mol = *itMolecule;
    mol->getSequence (&s);
    os << s << "\t" << s << endl;
    itMolecule++;
  }
  os << endl;

  /*
  ** Food set.
  */
  os << "<food set>" << endl;
  itFoodSet = foodSet.begin ();
  while (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
    mol->getSequence (&s);
    os << s << "\t" << s << endl;
    itFoodSet++;
  }
  os << endl;

  /*
  ** Reactions.
  */
  os << "<reactions>" << endl;
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    reac->getID (&s);
    if (s.find (CMP_PREFIX) == string::npos)
    {
      os << s << "\t";
      /*
      ** Reactants.
      */
      mol = reac->getReactantFirst ();
      if (mol != NULL)
      {
	mol->getSequence (&s);
	os << s << " ";
	mol = reac->getReactantNext ();
	while (mol != NULL)
	{
	  mol->getSequence (&s);
	  os << "+ " << s << " ";
	  mol = reac->getReactantNext ();
	}
      }
      /*
      ** Reaction arrow.
      */
      if (reac->getDirection () == UNI_DIR)
      {
	os << "=> ";
      }
      else
      {
	os << "<=> ";
      }
      /*
      ** Products.
      */
      mol = reac->getProductFirst ();
      if (mol != NULL)
      {
	mol->getSequence (&s);
	os << s;
	mol = reac->getProductNext ();
	while (mol != NULL)
	{
	  mol->getSequence (&s);
	  os << " + " << s;
	  mol = reac->getProductNext ();
	}
      }
      os << "\t";
      /*
      ** Catalysts.
      */
      mol = reac->getCatalystFirst ();
      if (mol != NULL)
      {
	mol->getSequence (&s);
	os << s;
	mol = reac->getCatalystNext ();
	while (mol != NULL)
	{
	  mol->getSequence (&s);
	  os << " " << s;
	  mol = reac->getCatalystNext ();
	}
      }
      if (reac->getNrCatalysts () == 0)
      {
	os << " ";
      }
      os << "\t";
      /*
      ** Reaction rate.
      */
      os << "1" << endl;
    }
    itReaction++;
  }
}


/*
** printReaction: Print a reaction.
*/

void ReacSet::printReaction (Reaction *reac)
{
  string    s;
  Molecule *mol;

  reac->getID (&s);
  cout << s << "\t";
  mol = reac->getReactantFirst ();
  if (mol != NULL)
  {
    mol->getSequence (&s);
    cout << s << " ";
    mol = reac->getReactantNext ();
    while (mol != NULL)
    {
      mol->getSequence (&s);
      cout << "+ " << s << " ";
      mol = reac->getReactantNext ();
    }
  }
  if (reac->getDirection () == UNI_DIR)
  {
    cout << "=> ";
  }
  else
  {
    cout << "<=> ";
  }
  mol = reac->getProductFirst ();
  if (mol != NULL)
  {
    mol->getSequence (&s);
    cout << s << " ";
    mol = reac->getProductNext ();
    while (mol != NULL)
    {
      mol->getSequence (&s);
      cout << "+ " << s << " ";
      mol = reac->getProductNext ();
    }
  }
  cout << " (";
  mol = reac->getCatalystFirst ();
  if (mol != NULL)
  {
    mol->getSequence (&s);
    cout << s;
    mol = reac->getCatalystNext ();
    while (mol != NULL)
    {
      mol->getSequence (&s);
      cout << " " << s;
      mol = reac->getCatalystNext ();
    }
  }
  if (reac->getNrCatalysts () == 0)
  {
    cout << "_";
  }
  cout << ")" << endl;
}


/*
** printMaxRAF: Print the maxRAF set.
**
** Parameters:
**   full: Boolean indicating whether to print the full reaction ('true') or
**         only the reaction IDs ('false').
*/

void ReacSet::printMaxRAF (bool full)
{
  string    s;
  Reaction *reac;

  /*
  ** Print the reactions in the maxRAF.
  */
  reac = maxRAF->getReactionFirst ();
  while (reac != NULL)
  {
    if (full)
    {
      printReaction (reac);
    }
    else
    {
      reac->getID (&s);
      cout << s << endl;
    }
    reac = maxRAF->getReactionNext ();
  }
}


/*
** getNrRAFMolecules: Return the number of molecule types in the maxRAF set.
**
** Returns:
**   The size of the closure of the food set.
*/

int ReacSet::getNrRAFMolecules ()
{
  return (closure.size ());
}


/*
** addCatalystCompound: Add a catalyst compound.
**
** Parameters:
**   reac: The reaction to add the catalyst compound to.
**   cat:  The catalyst compound.
**
** Returns:
**   If everything went fine:  0.
**   Otherwise:               -1.
*/

int ReacSet::addCatalystCompound (Reaction *reac, char *cat)
{
  int       status;
  char     *token, *saveptr;
  string    id;
  Molecule *mol;
  Reaction *cmp_reac;

  status = 0;

  /*
  ** Add a new molecule and reaction to create the catalyst compound, and add
  ** it as a catalyst to the current reaction.
  */
  id.assign (CMP_PREFIX);
  id.append (cat);
  mol = new Molecule (cat);
  addMolecule (mol);
  reac->addCatalyst (mol);
  cmp_reac = new Reaction (id);
  cmp_reac->addProduct (mol);
  cmp_reac->addCatalyst (mol);
  token = strtok_r (cat, "&", &saveptr);
  while (token != NULL)
  {
    if ((mol = getMoleculeBySeq (token)) == NULL)
    {
      status = -1;
      reac->getID (&id);
      cerr << "Invalid catalyst " << token << " in reaction " << id << "." << endl;
      goto End_of_Routine;
    }
    cmp_reac->addReactant (mol);
    token = strtok_r (NULL, "&", &saveptr);
  }
  addReaction (cmp_reac);
  
 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** parseCatalystRule: Parse a complex catalyst rule into "or" elements.
**
** Parameters:
**   - rule: The comples rule to parse.
**
** Returns:
**   - A pointer to a newly allocated string containing the parsed rule.
*/

char *ReacSet::parseCatalystRule (char *rule)
{
  char *parsed, or_part[1024], and_part[1024], *p, *token, *saveptr;

  /*
  ** Allocate memory for the parsed rule.
  */
  parsed = new char[1024];
  parsed[0] = '\0';
  p = strchr (rule, ')');
  strcpy (and_part, p+1);
  strncpy (p, "\0", 1);
  strcpy (or_part, rule+1);
  //cout << or_part << " " << and_part << endl;
  token = strtok_r (or_part, " ", &saveptr);
  while (token != NULL)
  {
    strcat (parsed, token);
    strcat (parsed, and_part);
    token = strtok_r (NULL, " ", &saveptr);
    if (token != NULL)
    {
      strcat (parsed, " ");
    }
  }
  //cout << parsed << endl;

  return (parsed);
}


/*
** EOF: ReacSet.cxx
*/
