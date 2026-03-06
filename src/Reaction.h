/*
** Reaction.h: Definition of a chemical reaction.
**
** Wim Hordijk   Last modified: 6 March 2026
*/

#ifndef _REACTION_H_
#define _REACTION_H_

#include "def.h"
#include "Molecule.h"
#include <algorithm>
#include <list>


/*
** Reaction: The reaction class.
*/

class Reaction
{
 public:
  /*
  ** Constructors and destructors.
  */
  Reaction  (string id);
  ~Reaction ();

  /*
  ** Public member functions.
  */
  void      getID             (string *id);
  int       getNrReactants    ();
  Molecule *getReactantFirst  ();
  Molecule *getReactantNext   ();
  bool      hasReactant       (Molecule *mol);
  void      addReactant       (Molecule *mol);
  void      removeReactant    (Molecule *mol);
  void      clearReactants    ();
  int       getNrProducts     ();
  Molecule *getProductFirst   ();
  Molecule *getProductNext    ();
  bool      hasProduct        (Molecule *mol);
  void      addProduct        (Molecule *mol);
  void      removeProduct     (Molecule *mol);
  void      clearProducts     ();
  int       getNrCatalysts    ();
  Molecule *getCatalystFirst  ();
  Molecule *getCatalystNext   ();
  bool      hasCatalyst       (Molecule *mol);
  void      addCatalyst       (Molecule *mol);
  void      removeCatalyst    (Molecule *mol);
  void      clearCatalysts    ();
  void      setDirection      (int dir);
  int       getDirection      ();

 private:
  /*
  ** Private member variables.
  */
  string                    ID;
  int                       direction;
  list<Molecule*>           reactants, products, catalysts;
  list<Molecule*>::iterator itReactant, itProduct, itCatalyst;
};


#endif  /* _REACTION_H_ */

/*
** EoF: Reaction.h
*/
