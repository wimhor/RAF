/*
** ReacSet.h: Definition of a chemical reaction set.
**
** Wim Hordijk   Last modified: 9 March 2019
*/

#ifndef _REACSET_H_
#define _REACSET_H_

#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "Reaction.h"
//#include "Subset.h"
#include "def.h"

using namespace std;


/*
** ReacSet: The reaction set class.
*/

class ReacSet
{
 public:
  /*
  ** Constructors and destructors.
  */
  ReacSet  ();
  ~ReacSet ();

  /*
  ** Public member functions.
  */
  int       getNrMolecules          ();
  Molecule *getMoleculeFirst        ();
  Molecule *getMoleculeNext         ();
  Molecule *getMoleculeBySeq        (string seq);
  void      addMolecule             (Molecule *mol);
  void      removeMolecule          (Molecule *mol);
  void      clearMolecules          ();
  int       getNrFoodMolecules      ();
  Molecule *getFoodSetFirst         ();
  Molecule *getFoodSetNext          ();
  bool      isInFoodSet             (Molecule *mol);
  void      addToFoodSet            (Molecule *mol);
  void      removeFromFoodSet       (Molecule *mol);
  void      clearFoodSet            ();
  int       getNrReactions          ();
  Reaction *getReactionFirst        ();
  Reaction *getReactionNext         ();
  void      addReaction             (Reaction *reac);
  void      removeReaction          (Reaction *reac);
  void      clearReactions          ();
  int       findMaxRAF              ();
  Reaction *getMaxRAFFirst          ();
  Reaction *getMaxRAFNext           ();
  bool      isInMaxRAF              (Reaction *reac);
  bool      isInClosure             (Molecule *mol);
  int       readFromFile            (ifstream& is);
  void      writeToFile             (ofstream& os);
  void      printReaction           (Reaction *reac);
  void      printMaxRAF             (bool full);
  int       nrRAFMolecules          ();

 private:
  /*
  ** Private member variables.
  */
  list<Molecule*>            molecules, foodSet, closure;
  list<Reaction*>            reactions, RAF, maxRAF;
  list<Molecule*>::iterator  itMolecule, itFoodSet, itClosure;
  list<Reaction*>::iterator  itReaction, itRAF;
  map<string,Molecule*>      molMap;

  /*
  ** Private member functions.
  */
  int   applyRAF              ();
  void  computeClosure        ();
  int   addCatalystCompound   (Reaction *reac, char *cat);
  char *parseCatalystRule     (char *rule);
};


#endif  /* _REACSET_H_ */

/*
** EoF: ReacSet.h
*/
