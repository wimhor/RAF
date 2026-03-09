/*
** ReacSet.h: Definition of a chemical reaction set.
**
** Wim Hordijk   Last modified: 9 March 2026
*/

#ifndef _REACSET_H_
#define _REACSET_H_

#include <fstream>
#include <vector>
#include "Reaction.h"
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
   ReacSet ();
  ~ReacSet ();

  /*
  ** Public member functions.
  */
  int       getNrMolecules     ();
  Molecule *getMoleculeFirst   ();
  Molecule *getMoleculeNext    ();
  Molecule *getMoleculeBySeq   (string seq);
  void      addMolecule        (Molecule *mol);
  void      removeMolecule     (Molecule *mol);
  void      clearMolecules     ();
  int       getNrFoodMolecules ();
  Molecule *getFoodSetFirst    ();
  Molecule *getFoodSetNext     ();
  bool      isInFoodSet        (Molecule *mol);
  void      addToFoodSet       (Molecule *mol);
  void      removeFromFoodSet  (Molecule *mol);
  void      clearFoodSet       ();
  int       getNrReactions     ();
  Reaction *getReactionFirst   ();
  Reaction *getReactionNext    ();
  bool      isInReacSet        (Reaction *reac);
  void      addReaction        (Reaction *reac);
  void      removeReaction     (Reaction *reac);
  void      clearReactions     ();
  int       findMaxRAF         ();
  int       getNrRAFMolecules  ();
  Reaction *getMaxRAFFirst     ();
  Reaction *getMaxRAFNext      ();
  bool      isInMaxRAF         (Reaction *reac);
  bool      isInClosureF       (Molecule *mol);
  int       findCAF            ();
  int       readFromFile       (ifstream& is);
  void      writeToFile        (ofstream& os);
  void      printReaction      (Reaction *reac);
  void      printMaxRAF        (bool full);
  void      printCAF           (bool full);

 private:
  /*
  ** Private member variables.
  */
  list<Molecule*>            molecules, foodSet, closure;
  list<Reaction*>            reactions;
  list<Molecule*>::iterator  itMolecule, itFoodSet, itClosure;
  list<Reaction*>::iterator  itReaction;
  map<string,Molecule*>      molMap;
  ReacSet                   *maxRAF, *CAF;

  /*
  ** Private member functions.
  */
  int  applyRAFalgo    ();
  int  applyCAFalgo    ();
  void computeClosureF ();
};


#endif  /* _REACSET_H_ */

/*
** EoF: ReacSet.h
*/
