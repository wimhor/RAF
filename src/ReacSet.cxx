/*
** ReacSet.cxx: Implementation of the reaction set class.
**
** Wim Hordijk   Last modified: 10 March 2026
*/

#include <string.h>
#include <iostream>
//#include "def.h"
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
  if (CAF != NULL)
  {
    delete CAF;
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
  ** While reactions could be removed and the current reaction set is not empty,
  ** iterate the RAF algorithm.
  */
  reactionsRemoved = true;
  while (reactionsRemoved && reactions.size () > 0)
  {
    /*
    ** Compute the closure of the food set.
    */
    computeClosureF ();
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
	if (!isInClosureF (mol))
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
	  if (isInClosureF (mol))
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
	if (!isInClosureF (r))
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
	  if (!isInClosureF (p))
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
	  if (!isInClosureF (p))
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
	  if (!isInClosureF (r))
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
  ** Print the closure (for debugging purposes only).
  **
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
  */
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
    ** Get the reactants and (optinally) their stoichiometry.
    */
    token = strtok (segment, "+");
    while (token != NULL)
    {
      n = 1;
      if ((sscanf (token, "%d %s", &n, label) == 2) ||
	  (sscanf (token, "%s", label) == 1))
      {
	if ((mol = getMoleculeBySeq (label)) == NULL)
	{
	  mol = new Molecule (label);
	  addMolecule (mol);
	}
	if (!reac->hasReactant (mol))
	{
	  reac->addReactant (mol, n);
	}
      }
      else
      {
	status = -1;
	cerr << "Invalid reactant in line " << lineNr << " of input file." << endl;
	goto End_of_Routine;	
      }
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
      n = 1;
      if ((sscanf (token, "%d %s", &n, label) == 2) ||
	  (sscanf (token, "%s", label) == 1))
      {
	if ((mol = getMoleculeBySeq (label)) == NULL)
	{
	  mol = new Molecule (label);
	  addMolecule (mol);
	}
	if (!reac->hasProduct (mol))
	{
	  reac->addProduct (mol, n);
	}
      }
      else
      {
	status = -1;
	cerr << "Invalid product in line " << lineNr << " of input file." << endl;
	goto End_of_Routine;	
      }
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
** writeToFile: Write the reaction set to an output file stream.
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
      mol->getSequence (&s);
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
	mol->getSequence (&s);
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
      mol->getSequence (&s);
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
	mol->getSequence (&s);
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
  CAF = new ReacSet ();
  CAF = this;
  
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
  ** Iteratively add reactions that can proceed catalyzed and their products.
  */
  reacsAdded = true;
  while (reacsAdded)
  {
    reacsAdded = false;
    /*
    ** Check each reaction to see if it can proceed catalyzed.
    */
    itReaction = reactions.begin ();
    while (itReaction != reactions.end ())
    {
      /*
      ** If the reaction has not already been applied, check if it can now.
      */
      reac = *itReaction;
      itCAF = find (tmpCAF.begin (), tmpCAF.end (), reac);
      if (itCAF == tmpCAF.end ())
      {
	/*
	** Check all reactants.
	*/
	apply = true;
	mol = reac->getReactantFirst ();
	while (mol != NULL)
	{
	  if (!isInClosureF (mol))
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
	    if (isInClosureF (mol))
	    {
	      apply = true;
	      break;
	    }
	    mol = reac->getCatalystNext ();
	  }
	}
	/*
	** Apply the reaction, if so indicated. If not, check the reverse
	** direction, if relevant.
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
	    if (!isInClosureF (mol))
	    {
	      closure.push_back (mol);
	    }
	    mol = reac->getProductNext ();
	  }
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
	    if (!isInClosureF (mol))
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
	      if (isInClosureF (mol))
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
	      if (!isInClosureF (mol))
	      {
		closure.push_back (mol);
	      }
	      mol = reac->getReactantNext ();
	    }
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
  ** Return the size of the CAF.
  */
  return (reactions.size ());
}


/*
** printCAF: Print the CAF set.
**
** Parameters:
**   full: Boolean indicating whether to print the full reaction ('true') or
**         only the reaction IDs ('false').
*/

void ReacSet::printCAF (bool full)
{
  string    s;
  Reaction *reac;

  /*
  ** Print the reactions in the CAF.
  */
  reac = CAF->getReactionFirst ();
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
    reac = CAF->getReactionNext ();
  }
}


/*
** EOF: ReacSet.cxx
*/
