/*
** Reaction.h: Definition of a chemical reaction.
**
** Wim Hordijk   Last modified: 9 March 2019
*/

#ifndef _REACTION_H_
#define _REACTION_H_

#include "def.h"
#include "Molecule.h"
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
  int       getNrInhibitors   ();
  Molecule *getInhibitorFirst ();
  Molecule *getInhibitorNext  ();
  bool      hasInhibitor      (Molecule *mol);
  void      addInhibitor      (Molecule *mol);
  void      removeInhibitor   (Molecule *mol);
  void      clearInhibitors   ();
  double    getRate           ();
  void      setRate           (double r);
  void      setDirection      (int dir);
  int       getDirection      ();

  /*
  ** Public member variables (these can be freely used by other methods for
  ** their own purposes).
  */
  int  id;
  bool isInSet, closureF;
  
 private:
  /*
  ** Private member variables.
  */
  string                    ID;
  int                       direction;
  double                    rate;
  list<Molecule*>           reactants, products, catalysts, inhibitors;
  list<Molecule*>::iterator itReactant, itProduct, itCatalyst, itInhibitor;
};


#endif  /* _REACTION_H_ */

/*
** EoF: Reaction.h
*/
