/*
** ReacSet.cxx: Implementation of the reaction set class.
**
** Wim Hordijk   Last modified: 25 March 2026
*/

#include <string.h>
#include <iostream>
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
  itClosure = closure.begin ();
  maxRAF = NULL;
  CAF = NULL;
}


/*
** ~ReacSet: Destructor.
*/

ReacSet::~ReacSet ()
{
  ReacSet *rset;
  
  /*
  ** Clear the lists.
  */
  molecules.clear ();
  reactions.clear ();
  foodSet.clear ();
  closure.clear ();
  molMap.clear ();
  essential.clear ();
  if (maxRAF != NULL)
  {
    delete maxRAF;
  }
  if (CAF != NULL)
  {
    delete CAF;
  }
  itSubRAF = iRAFs.begin ();
  while (itSubRAF != iRAFs.end ())
  {
    rset = *itSubRAF;
    delete rset;
  }
  iRAFs.clear ();
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
** getMoleculeBySeq: Get an element from the molecule list by its sequence string.
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
  mol->getSequence (seq);
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
  mol->getSequence (seq);
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
** addToFoodSet: Add a molecule to the food set if it does not already exist.
**
** Parameters:
**   - mol: The molecule to add.
*/

void ReacSet::addToFoodSet (Molecule *mol)
{
  /*
  ** Add the molecule to the food set if it's not already there.
  */
  itFoodSet = find (foodSet.begin (), foodSet.end (), mol);
  if (itFoodSet == foodSet.end ())
  {
    foodSet.push_back (mol);
  }
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
** compare: Compare the current reaction set with another one.
**
** Note: This comparison is based purely on pointers to reactions, so can only be
**       applied to subsets of the same original reaction set. Different instantiations
**       of the same reaction set will have different pointers to the same reactions!
**
** Parameters:
**   - rset: The reaction set to compare with.
**
** Returns:
**   - If the two sets are the same: true.
**   - Otherwise:                    false.
*/

bool ReacSet::compare (ReacSet *rset)
{
  bool      same;
  Reaction *reac;

  /*
  ** First compare their sizes.
  */
  same = true;
  if (reactions.size () != rset->getNrReactions ())
  {
    same = false;
  }

  /*
  ** While still necessary, compare all reaction pointers until a difference is found.
  */
  itReaction = reactions.begin ();
  while (same && (itReaction != reactions.end ()))
  {
    reac = *itReaction;
    if (rset->isInReacSet (reac))
    {
      itReaction++;
    }
    else
    {
      same = false;
    }
  }

  /*
  ** Return the result.
  */
  return (same);
}


/*
** addReaction: Add a reaction to the list if it does not alreayd exist.
**
** Parameters:
**   - reac: The reaction to add.
*/

void ReacSet::addReaction (Reaction *reac)
{
  /*
  ** Add the reaction to the list if it's not already there.
  */
  itReaction = find (reactions.begin (), reactions.end (), reac);
  if (itReaction == reactions.end ())
  {
    reactions.push_back (reac);
    essential[reac] = false;
  }
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
  essential.erase (reac);
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
** applyRAFalgo: Apply the RAF algorithm to the current reaction set. The resulting
**               reaction set is the maxRAF, or is empty if there is no RAF.
**
** Returns:
**   The size of the found RAF set (zero if empty).
*/

int ReacSet::applyRAFalgo ()
{
  bool      reactionsRemoved, remove;
  Molecule *mol;
  Reaction *reac;

  /*
  ** First remove all reactions that have no catalysts.
  */
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    if (reac->getNrCatalysts () == 0)
    {
      itReaction = reactions.erase (itReaction);
    }
    else
    {
      itReaction++;
    }
  }
  reactionsRemoved = true;
  
  /*
  ** While reactions could be removed and the current reaction set is not empty,
  ** iterate the RAF algorithm.
  */
  while (reactionsRemoved && reactions.size () > 0)
  {
    /*
    ** Compute the closure of the food set.
    */
    computeClosureF ();
    /*
    ** Remove all reactions that were not applied during the closure computation (i.e.,
    ** they do not have all their reactants in the closure), and also all applied
    ** reactions that have no catalysts in the closure of the food set.
    */
    reactionsRemoved = false;
    itReaction = reactions.begin ();
    while (itReaction != reactions.end ())
    {
      reac = *itReaction;
      if (reac->applied)
      {
	/*
	** Check the catalysts.
	*/
	remove = true;
	mol = reac->getCatalystFirst ();
	while (mol != NULL)
	{
	  if (mol->inClosure)
	  {
	    remove = false;
	    break;
	  }
	  mol = reac->getCatalystNext ();
	}
      }
      else
      {
	remove = true;
      }
      /*
      ** Remove the reaction, if so indicated.
      */
      if (remove)
      {
	reac->applied = false;
	itReaction = reactions.erase (itReaction);
	essential.erase (reac);
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
  int size;

  /*
  ** Create a copy of the current reaction set and apply the RAF algorithm to it.
  */
  if (maxRAF == NULL)
  {
    maxRAF = new ReacSet ();
  }
  maxRAF->copy (this);
  size = maxRAF->applyRAFalgo ();

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
** isInClosureF: Check whether a molecule is in the current closure of the food set.
**
** Parameters:
**   - mol: The molecule to check for.
**
** Returns:
**   - If the molecule is in the closure: true.
**   - Otherwise:                         false.
*/

bool ReacSet::isInClosureF (Molecule *mol)
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
** computeClosureF: Compute the closure of the food set.
*/

void ReacSet::computeClosureF ()
{
  bool      molsAdded;
  Molecule *mol, *r, *p;
  Reaction *reac;
  bool      apply;

  /*
  ** Reset all molecules and reactions.
  */
  itMolecule = molecules.begin ();
  while (itMolecule != molecules.end ())
  {
    mol = *itMolecule;
    mol->inClosure = false;
    itMolecule++;
  }
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    reac->applied = false;
    itReaction++;
  }

  /*
  ** Clear the closure and copy all food molecules to it.
  */
  closure.clear ();
  itFoodSet = foodSet.begin ();
  while (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
    closure.push_back (mol);
    mol->inClosure = true;
    itFoodSet++;
  }
  molsAdded = true;
  
  /*
  ** Iteratively construct the closure of the food set while new molecules
  ** were still added.
  */
  while (molsAdded)
  {
    molsAdded = false;
    /*
    ** Check all current reactions that were not already applied.
    */
    itReaction = reactions.begin ();
    while (itReaction != reactions.end ())
    {
      reac = *itReaction;
      if (!reac->applied)
      {
	/*
	** Check all reactants.
	*/
	apply = true;
	r = reac->getReactantFirst ();
	while (r != NULL)
	{
	  if (!r->inClosure)
	  {
	    apply = false;
	    break;
	  }
	  r = reac->getReactantNext ();
	}
	/*
	** If the reaction can be applied, add all products to the closure if
	** they are not already in there. Otherwise, check the reverse direction
	** if the reaction is bi-directional.
	*/
	if (apply)
	{
	  /*
	  ** Add products to the closure.
	  */
	  p = reac->getProductFirst ();
	  while (p != NULL)
	  {
	    if (!p->inClosure)
	    {
	      closure.push_back (p);
	      p->inClosure = true;
	    }
	    p = reac->getProductNext ();
	  }
	  reac->applied = true;
	  molsAdded = true;
	}
	else if (reac->getDirection () == BI_DIR)
	{
	  /*
	  ** Check all products.
	  */
	  apply = true;
	  p = reac->getProductFirst ();
	  while (p != NULL)
	  {
	    if (!p->inClosure)
	    {
	      apply = false;
	      break;
	    }
	    p = reac->getProductNext ();
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
	      if (!r->inClosure)
	      {
		closure.push_back (r);
		r->inClosure = true;
	      }
	      r = reac->getReactantNext ();
	    }
	    reac->applied = true;
	    molsAdded = true;
	  }
	}
      }
      /*
      ** Get the next reaction.
      */
      itReaction++;
    }
  }
}


/*
** readFromFile: Read a reaction set from an input file stream.
**
** Note: This function uses old-fashioned C character strings, as it allows for using
**       the 'strtok' function which is quite useful here.
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
  int              n, status, lineNr;
  bool             bidirectional;
  char             line[2048], segment[1024], label[64], *token, *pch;
  size_t           len;
  Molecule        *mol;
  Reaction        *reac, *bReac;
  list<Molecule*>  catalyst;

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
  is.getline (line, 1024);
  lineNr++;
  if (strcmp (line, "#Reactions") != 0)
  {
    status = -1;
    cerr << "First line in input file should be '#Reactions'" << endl;
    goto End_of_Routine;
  }
  is.getline (line, 1024);
  lineNr++;
  while (strcmp (line, "#Food") != 0)
  {
    /*
    ** Get reaction label.
    */
    if ((pch = strchr (line, ':')) == NULL)
    {
      status = -1;
      cerr << "No ':' present in line " << lineNr << " of input file." << endl;
      goto End_of_Routine;
    }
    len = pch - line;
    strncpy (label, line, len);
    label[len] = '\0';
    reac = new Reaction (label);
    /*
    ** Get the reactants segment and point to the beginning of the products segment.
    */
    if ((len = strcspn (pch+1, "<=")) == strlen (pch+1))
    {
      status = -1;
      cerr << "No valid reaction arrow in line " << lineNr << " of input file." << endl
	   << "  (should be '=>' or '<=>')." << endl;
      goto End_of_Routine;
    }
    strncpy (segment, pch+1, len);
    segment[len] = '\0';
    if (strncmp (pch+len+1, "=>", 2) == 0)
    {
      reac->setDirection (UNI_DIR);
      pch += (len + 3);
    }
    else if (strncmp (pch+len+1, "<=>", 3) == 0)
    {
      reac->setDirection (BI_DIR);
      pch += (len + 4);
    }
    else
    {
      status = -1;
      cerr << "No valid reaction arrow in line " << lineNr << " of input file." << endl
	   << "  (should be '=>' or '<=>')." << endl;
      goto End_of_Routine;
    }
    /*
    ** Get the reactants and (optionally) their stoichiometry.
    */
    token = strtok (segment, "+");
    while (token != NULL)
    {
      if (sscanf (token, "%d %s", &n, label) != 2)
      {
	if (sscanf (token, "%s", label) != 1)
	{
	  status = -1;
	  cerr << "Invalid reactant in line " << lineNr << " of input file." << endl;
	  goto End_of_Routine;	
	}
	n = 1;
      }
      if ((mol = getMoleculeBySeq (label)) == NULL)
      {
	mol = new Molecule (label);
	addMolecule (mol);
      }
      /*
      ** Add the reactant. If it already existed, its stoichiometry will be updated.
      */
      reac->addReactant (mol, n);
      token = strtok (NULL, "+");
    }
    /*
    ** Get the products segment and point to the beginning of the catalysts segment.
    */
    if ((token = strchr (pch, '(')) == NULL)
    {
      len = strlen (pch);
      strcpy (segment, pch);
    }
    else
    {
      len = token - pch;
      strncpy (segment, pch, len);
      segment[len] = '\0';
    }
    pch += len;
    /*
    ** Get the products. Stoichiometry can be included, but is ignored for now.
    */
    token = strtok (segment, "+");
    while (token != NULL)
    {
      if (sscanf (token, "%d %s", &n, label) != 2)
      {
	if (sscanf (token, "%s", label) != 1)
	{
	  status = -1;
	  cerr << "Invalid product in line " << lineNr << " of input file." << endl;
	  goto End_of_Routine;	
	}
	n = 1;
      }
      if ((mol = getMoleculeBySeq (label)) == NULL)
      {
	mol = new Molecule (label);
	addMolecule (mol);
      }
      /*
      ** Add the product. If it already existed, its stoichiometry will be updated.
      */
      reac->addProduct (mol, n);
      token = strtok (NULL, "+");
    }
    /*
    ** Get and parse the catalyst segment.
    */
    if ((token = strchr (pch, ')')) != NULL)
    {
      len = token - pch;
      strncpy (segment, pch+1, len-1);
      segment[len-1] = '\0';
      /*
      ** Get the catalysts.
      */
      token = strtok (segment, " ");
      while (token != NULL)
      {
	if ((mol = getMoleculeBySeq (token)) == NULL)
	{
	  mol = new Molecule (token);
	  addMolecule (mol);
	}
	if (!reac->hasCatalyst (mol))
	{
	  reac->addCatalyst (mol);
	}
	else
	{
	  status = -1;
	  cerr << "Catalyst " << token << " appears more than once in line "
	       << lineNr << " of input file." << endl;
	  goto End_of_Routine;	
	}
	token = strtok (NULL, " ");
      }
    }
    /*
    ** Add the reaction to the reaction set and read the next line.
    */
    addReaction (reac);
    is.getline (line, 1024);
  }
  /*
  ** Read the food set.
  */
  is.getline (label, 1024);
  while (!is.eof ())
  {
    if ((mol = getMoleculeBySeq (label)) == NULL)
    {
      mol = new Molecule (label);
      addMolecule (mol);
    }
    addToFoodSet (mol);
    is.getline (label, 1024);
  }
  
  /*
  ** Reset the list iterators.
  */
  itMolecule = molecules.begin ();
  itFoodSet = foodSet.begin ();
  itReaction = reactions.begin ();
  
  /*
  ** Return the status.
  */
 End_of_Routine:
  return (status);
}


/*
** writeToFile: Write the reaction set to an output file stream (in the old format).
**
** Parameters:
**   - os: The output file stream to write to.
*/

void ReacSet::writeToFile (ofstream& os)
{
  int       n;
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
    mol->getSequence (s);
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
    mol->getSequence (s);
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
    os << s << "\t";
    /*
    ** Reactants.
    */
    mol = reac->getReactantFirst ();
    if (mol != NULL)
    {
      n = reac->getReacStoich (mol);
      if (n > 1)
      {
	os << n << " ";
      }
      mol->getSequence (s);
      os << s << " ";
      mol = reac->getReactantNext ();
      while (mol != NULL)
      {
	os << "+ ";
	n = reac->getReacStoich (mol);
	if (n > 1)
	{
	  os << n << " ";
	}
	mol->getSequence (s);
	os << s << " ";
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
      n = reac->getProdStoich (mol);
      if (n > 1)
      {
	os << n << " ";
      }
      mol->getSequence (s);
      os << s;
      mol = reac->getProductNext ();
      while (mol != NULL)
      {
	os << " + ";
	n = reac->getProdStoich (mol);
	if (n > 1)
	{
	  os << n << " ";
	}
	mol->getSequence (s);
	os << s;
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
      mol->getSequence (s);
      os << s;
      mol = reac->getCatalystNext ();
      while (mol != NULL)
      {
	mol->getSequence (s);
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
    itReaction++;
  }
}


/*
** printReaction: Print a reaction.
*/

void ReacSet::printReaction (Reaction *reac)
{
  int       n;
  string    s;
  Molecule *mol;

  reac->getID (&s);
  cout << s << ": ";
  mol = reac->getReactantFirst ();
  if (mol != NULL)
  {
    n = reac->getReacStoich (mol);
    if (n > 1)
    {
      cout << n << " ";
    }
    mol->getSequence (s);
    cout << s << " ";
    mol = reac->getReactantNext ();
    while (mol != NULL)
    {
      cout << "+ ";
      n = reac->getReacStoich (mol);
      if (n > 1)
      {
	cout << n << " ";
      }
      mol->getSequence (s);
      cout << s << " ";
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
    n = reac->getProdStoich (mol);
    if (n > 1)
    {
      cout << n << " ";
    }
    mol->getSequence (s);
    cout << s << " ";
    mol = reac->getProductNext ();
    while (mol != NULL)
    {
      cout << "+ ";
      n = reac->getProdStoich (mol);
      if (n > 1)
      {
	cout << n << " ";
      }
      mol->getSequence (s);
      cout << s << " ";
      mol = reac->getProductNext ();
    }
  }
  if (reac->getNrCatalysts () > 0)
  {
    cout << "(";
    mol = reac->getCatalystFirst ();
    mol->getSequence (s);
    cout << s;
    mol = reac->getCatalystNext ();
    while (mol != NULL)
    {
      mol->getSequence (s);
      cout << " " << s;
      mol = reac->getCatalystNext ();
    }
    cout << ")" << endl;
  }
}


/*
** printReacSet: Print the current reaction set.
**
** Parameters:
**   full: Boolean indicating whether to print the full reaction ('true') or
**         only the reaction IDs ('false').
*/

void ReacSet::printReacSet (bool full)
{
  string    s;
  Reaction *reac;

  /*
  ** Print the reactions in the current set.
  */
  if (!full && (reactions.size () > 0))
  {
    cout << "  ";
  }
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    if (full)
    {
      cout << "  ";
      printReaction (reac);
    }
    else
    {
      reac->getID (&s);
      cout << s << " ";
    }
    itReaction++;
  }
  if (!full && (reactions.size () > 0))
  {
    cout << endl;
  }
}


/*
** printMaxRAF: Print the maxRAF reaction set.
**
** Parameters:
**   full: Boolean indicating whether to print the full reaction ('true') or
**         only the reaction IDs ('false').
*/

void ReacSet::printMaxRAF (bool full)
{
  /*
  ** Print the maxRAF reaction set.
  */
  maxRAF->printReacSet (full);
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
** findCAF: Find the CAF in the current reaction set.
**
** Returns:
**   - The size of the CAF set (zero if empty).
*/

int ReacSet::findCAF ()
{
  int size;

  /*
  ** Create a new reaction set to contain the CAF.
  */
  if (CAF == NULL)
  {
    CAF = new ReacSet ();
  }
  CAF->copy (this);
  
  /*
  ** Apply the CAF algorithm.
  */
  size = CAF->applyCAFalgo ();

  /*
  ** Return the size of the CAF.
  */
  return (size);
}


/*
** applyCAFalgo: Apply the CAF algorithm to the current reaction set.
**
** Returns:
**   - The size of the resulting CAF set.
*/

int ReacSet::applyCAFalgo ()
{
  int                        size;
  bool                       reacsAdded, apply;
  Molecule                  *mol;
  Reaction                  *reac;
  list<Reaction*>            tmpCAF;
  list<Reaction*>::iterator  itCAF;

  /*
  ** First remove all reactions that have no catalysts.
  */
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    reac->applied = false;
    if (reac->getNrCatalysts () == 0)
    {
      itReaction = reactions.erase (itReaction);
    }
    else
    {
      itReaction++;
    }
  }
  
  /*
  ** Reset all molecules.
  */
  itMolecule = molecules.begin ();
  while (itMolecule != molecules.end ())
  {
    mol = *itMolecule;
    mol->inClosure = false;
    itMolecule++;
  }

  /*
  ** Clear the closure and copy all food molecules to it.
  */
  closure.clear ();
  itFoodSet = foodSet.begin ();
  while (itFoodSet != foodSet.end ())
  {
    mol = *itFoodSet;
    closure.push_back (mol);
    mol->inClosure = true;
    itFoodSet++;
  }

  /*
  ** Iteratively add reactions that can proceed catalyzed, and add their products
  ** to the closure.
  */
  reacsAdded = true;
  while (reacsAdded)
  {
    reacsAdded = false;
    /*
    ** Check each reaction that has not been applied yet.
    */
    itReaction = reactions.begin ();
    while (itReaction != reactions.end ())
    {
      /*
      ** If the reaction has not already been applied, check if it can be now.
      */
      reac = *itReaction;
      if (!reac->applied)
      {
	/*
	** Check all reactants.
	*/
	apply = true;
	mol = reac->getReactantFirst ();
	while (mol != NULL)
	{
	  if (!mol->inClosure)
	  {
	    apply = false;
	    break;
	  }
	  mol = reac->getReactantNext ();
	}
	/*
	** Check catalysts, if still necessary.
	*/
	if (apply)
	{
	  apply = false;
	  mol = reac->getCatalystFirst ();
	  while (mol != NULL)
	  {
	    if (mol->inClosure)
	    {
	      apply = true;
	      break;
	    }
	    mol = reac->getCatalystNext ();
	  }
	}
	/*
	** Apply the reaction, if so indicated. If not, check the reverse
	** direction if the reaction is bi-directional.
	*/
	if (apply)
	{
	  /*
	  ** Add the reaction to the CAF and its products to the closure.
	  */
	  tmpCAF.push_back (reac);
	  mol = reac->getProductFirst ();
	  while (mol != NULL)
	  {
	    if (!mol->inClosure)
	    {
	      closure.push_back (mol);
	      mol->inClosure = true;
	    }
	    mol = reac->getProductNext ();
	  }
	  reac->applied = true;
	  reacsAdded = true;
	}
	else if (reac->getDirection () == BI_DIR)
	{
	  /*
	  ** Check all products.
	  */
	  apply = true;
	  mol = reac->getProductFirst ();
	  while (mol != NULL)
	  {
	    if (!mol->inClosure)
	    {
	      apply = false;
	      break;
	    }
	    mol = reac->getProductNext ();
	  }
	  /*
	  ** Check catalysts, if still necessary.
	  */
	  if (apply)
	  {
	    apply = false;
	    mol = reac->getCatalystFirst ();
	    while (mol != NULL)
	    {
	      if (mol->inClosure)
	      {
		apply = true;
		break;
	      }
	      mol = reac->getCatalystNext ();
	    }
	  }
	  /*
	  ** Apply the reaction, if so indicated.
	  */
	  if (apply)
	  {
	    /*
	    ** Add the reaction to the CAF and its reactants to the closure.
	    */
	    tmpCAF.push_back (reac);
	    mol = reac->getReactantFirst ();
	    while (mol != NULL)
	    {
	      if (!mol->inClosure)
	      {
		closure.push_back (mol);
		mol->inClosure = true;
	      }
	      mol = reac->getReactantNext ();
	    }
	    reac->applied = true;
	    reacsAdded = true;
	  }
	}
      }
      /*
      ** Get the next reaction.
      */
      itReaction++;
    }
  }

  /*
  ** Clear the current reaction set and copy the temporary CAF list to it.
  */
  reactions.clear ();
  itCAF = tmpCAF.begin ();
  while (itCAF != tmpCAF.end ())
  {
    reac = *itCAF;
    reactions.push_back (reac);
    itCAF++;
  }

  /*
  /*
  ** Return the size of the CAF.
  */
  return (reactions.size ());
}


/*
** printCAF: Print the CAF reaction set.
**
** Parameters:
**   full: Boolean indicating whether to print the full reaction ('true') or
**         only the reaction IDs ('false').
*/

void ReacSet::printCAF (bool full)
{
  /*
  ** Print the CAF reaction set.
  */
  CAF->printReacSet (full);
}


/*
** findiRAFs: Find all iRAFs within the maxRAF.
**
** Returns:
**   The number of iRAFS found.
*/

int ReacSet::findiRAFs ()
{
  int      nriRAFs;
  ReacSet *sraf;
  list<ReacSet*>::iterator itRSet;

  /*
  ** Apply the iRAF algorithm.
  */
  nriRAFs = 0;
  if (maxRAF->getNrReactions () > 0)
  {
    nriRAFs = maxRAF->applyiRAFsAlgo (subRAFs, iRAFs);
  }

  /*
  ** Clear the list of seen subRAFs.
  */
  itSubRAF = subRAFs.begin ();
  while (itSubRAF != subRAFs.end ())
  {
    sraf = *itSubRAF;
    itRSet = find (iRAFs.begin (), iRAFs.end (), sraf);
    if (itRSet == iRAFs.end ())
    {
      delete sraf;
    }
    itSubRAF++;
  }
  subRAFs.clear ();
  
  /*
  ** Return the result.
  */
  return (nriRAFs);
}


/*
** applyiRAFsAlgo: Recursively find all iRAFs within a RAF.
**
** Parameters:
**   - S: A list of subRAFs seen so far.
**   - I: A list of iRAFs found so far.
**
** Returns:
**   - The number of iRAFs found so far.
*/

int ReacSet::applyiRAFsAlgo (list<ReacSet*>& S, list<ReacSet*>& I)
{
  int       rSize;
  bool      isiRAF, seen;
  Reaction *reac;
  ReacSet  *recurse, *subRAF;

  /*
  ** Remove each reaction in turn and apply the RAF algorithm.
  */
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    if (!essential[reac])
    {
      /*
      ** Create a copy of the current reaction set, remove the current reaction,
      ** and apply the RAF algorithm.
      */
      recurse = new ReacSet ();
      recurse->copy (this);
      recurse->removeReaction (reac);
      rSize = recurse->applyRAFalgo ();
      /*
      ** Check the result and recurse, if needed.
      */
      if (rSize == 0)
      {
	/*
	** Current reaction is essential.
	*/
	essential[reac] = true;
	delete recurse;
      }
      else
      {
	/*
	** Check if the smaller subRAF has already been seen.
	*/
	seen = false;
	itSubRAF = S.begin ();
	while (itSubRAF != S.end ())
	{
	  subRAF = *itSubRAF;
	  if (recurse->compare (subRAF))
	  {
	    seen = true;
	    break;
	  }
	  itSubRAF++;
	}
	/*
	** If not yet seen, save and recurse. Otherwise, delete and ignore.
	*/
	if (!seen)
	{
	  S.push_back (recurse);
	  recurse->applyiRAFsAlgo (S, I);
	}
	else
	{
	  delete recurse;
	}
      }
    }
    /*
    ** Get the next reaction.
    */
    itReaction++;
  }

  /*
  ** Check if all reactions are essential.
  */
  isiRAF = true;
  itReaction = reactions.begin ();
  while (itReaction != reactions.end ())
  {
    reac = *itReaction;
    if (!essential[reac])
    {
      isiRAF = false;
      break;
    }
    itReaction++;
  }
  /*
  ** If an iRAF, save the current reaction set.
  */
  if (isiRAF)
  {
    I.push_back (this);
  }

  /*
  ** Return the number of iRAFs found so far.
  */
  return (I.size ());
}


/*
** sampleiRAFs: Generate a sample of iRAFs within the maxRAF.
**
** Returns:
**   The number of different iRAFS found.
*/

int ReacSet::sampleiRAFs (int sampleSize)
{
  int      i, nriRAFs;
  ReacSet *sraf;
  default_random_engine dre(time(NULL));
  
  /*
  ** Clear the current list.
  */
  itSubRAF = iRAFs.begin ();
  while (itSubRAF != iRAFs.end ())
  {
    sraf = *itSubRAF;
    delete sraf;
  }
  iRAFs.clear ();
  
  /*
  ** Generate random iRAFs and store them.
  */
  //seed = time (NULL);
  nriRAFs = 0;
  for (i = 0; i < sampleSize; i++)
  {
    sraf = randomiRAF (dre);
    iRAFs.push_back (sraf);
    nriRAFs++;
  }
  
  /*
  ** Return the result.
  */
  return (nriRAFs);
}


/*
** randomiRAF: Find a random iRAF.
**
** Returns:
**   A pointer to a reaction set containing an iRAF.
*/

ReacSet *ReacSet::randomiRAF (default_random_engine& dre)
{
  int                          i, reacIndex, rSize;
  Reaction                    *reac;
  ReacSet                     *sraf;
  vector<Reaction*>            shuffledReacs;
  vector<Reaction*>::iterator  itShufReac;

  /*
  ** Create a new reaction set and copy the maxRAF to it.
  */
  sraf = new ReacSet ();
  sraf->copy (maxRAF);

  /*
  ** Copy the maxRAF reactions and randomly shuffle them.
  */
  reac = maxRAF->getReactionFirst ();
  while (reac != NULL)
  {
    shuffledReacs.push_back (reac);
    reac = maxRAF->getReactionNext ();
  }
  shuffle (shuffledReacs.begin(), shuffledReacs.end(), dre);

  /*
  ** For each next reaction in the shuffled list, remove it and apply the RAF algorithm.
  */
  reacIndex = 0;
  while (reacIndex < shuffledReacs.size ())
  {
    /*
    ** Remove the next reaction in the set.
    */
    itShufReac = shuffledReacs.begin ();
    for (i = 0; i < reacIndex; i++)
    {
      itShufReac++;
    }
    reac = *itShufReac;
    sraf->removeReaction (reac);
    /*
    ** Apply the RAF algorithm and check the result.
    */
    rSize = sraf->applyRAFalgo ();
    if (rSize > 0)
    {
      /*
      ** Non-empty RAF: Remove all non-RAF reactions.
      */
      itShufReac = shuffledReacs.begin ();
      while (itShufReac != shuffledReacs.end ())
      {
	reac = *itShufReac;
	if (!sraf->isInReacSet (reac))
	{
	  itShufReac = shuffledReacs.erase (itShufReac);
	}
	else
	{
	  itShufReac++;
	}
      }
    }
    else
    {
      /*
      ** Empty RAF: Restore the RAF reactions and increase the index of
      **            the reaction to be removed next.
      */
      itShufReac = shuffledReacs.begin ();
      while (itShufReac != shuffledReacs.end ())
      {
	reac = *itShufReac;
	sraf->addReaction (reac);
	itShufReac++;
      }
      reacIndex++;
    }
  }

  /*
  ** Return the result.
  */
  return (sraf);
}


/*
** printiRAFs: Print the iRAF reaction sets.
**
** Parameters:
**   full: Print full reactions ('true') or only reaction IDs ('false').
*/

void ReacSet::printiRAFs (bool full)
{
  ReacSet *iraf;

  /*
  ** Print the reaction set for each iRAF.
  */
  itSubRAF = iRAFs.begin ();
  while (itSubRAF != iRAFs.end ())
  {
    iraf = *itSubRAF;
    cout << "  " << iraf->getNrReactions () << ":";
    if (full)
    {
      cout << endl;
    }
    iraf->printReacSet (full);
    itSubRAF++;
  }
}


/*
** copy: Copy the reaction network of another ReacSet object into the current one.
**
** Parameters:
**   - source: A pointer to another ReacSet object.
*/

void ReacSet::copy (ReacSet *source)
{
  /*
  ** Clear the various lists and copy the contents of the source reaction set.
  */
  molecules.clear ();
  foodSet.clear ();
  reactions.clear ();
  closure.clear ();
  molMap.clear ();
  essential.clear ();
  molecules = source->molecules;
  foodSet = source->foodSet;
  reactions = source->reactions;
  molMap = source->molMap;
  essential = source->essential;
  itMolecule = molecules.begin ();
  itFoodSet = foodSet.begin ();
  itReaction = reactions.begin ();
}


/*
** EOF: ReacSet.cxx
*/
