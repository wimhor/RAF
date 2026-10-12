/*
** Reaction.h: Definition of a chemical reaction.
**
** Wim Hordijk   Last modified: 12 October 2026
*/

#ifndef _REACTION_H_
#define _REACTION_H_

#include "Molecule.h"
#include <algorithm>
#include <map>


/*
** Defines:
**   - UNI_DIR: Uni-directional reaction.
**   - BI_DIR:  Bi-directional reaction.
*/

#define UNI_DIR 0
#define BI_DIR  1


/*
** Reaction: The reaction class.
*/

class Reaction
{
 public:
  /*
  ** Constructors and destructors.
  */
   Reaction (string id);
  ~Reaction ();

  /*
  ** Public member functions.
  */
  void      getID             (string& id);
  int       getNrReactants    ();
  Molecule *getReactantFirst  ();
  Molecule *getReactantNext   ();
  bool      hasReactant       (Molecule *mol);
  int       getReacStoich     (Molecule *mol);
  void      addReactant       (Molecule *mol, int n=1);
  void      removeReactant    (Molecule *mol);
  void      clearReactants    ();
  int       getNrProducts     ();
  Molecule *getProductFirst   ();
  Molecule *getProductNext    ();
  bool      hasProduct        (Molecule *mol);
  int       getProdStoich     (Molecule *mol);
  void      addProduct        (Molecule *mol, int n=1);
  void      removeProduct     (Molecule *mol);
  void      clearProducts     ();
  int       getNrCatalysts    ();
  int       getCatalystFirst  (list<Molecule*>& cat);
  int       getCatalystNext   (list<Molecule*>& cat);
  bool      hasCatalyst       (Molecule *mol);
  void      addCatalyst       (list<Molecule*>& cat);
  void      addMultiCatalyst  (Molecule *cat);
  void      removeCatalyst    (list<Molecule*>& cat);
  void      clearCatalysts    ();
  void      setDirection      (int dir);
  int       getDirection      ();

  /*
  ** Public member variables (for faster closure computation).
  */
  bool applied;
  
 private:
  /*
  ** Private member variables.
  */
  string                          ID;
  int                             direction;
  list<Molecule*>                 reactants, products;
  list<list<Molecule*>>           catalysts;
  list<Molecule*>::iterator       itReactant, itProduct, itCatalyst;
  list<list<Molecule*>>::iterator itCatList;
  map<Molecule*,int>              reacStoich, prodStoich;
};


#endif  /* _REACTION_H_ */

/*
** EoF: Reaction.h
*/
