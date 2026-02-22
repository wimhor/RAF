/*
** Molecule.h: Definition of a molecule type.
**
** Wim Hordijk   Last modified: 9 March 2019
*/

#ifndef _MOLECULE_H_
#define _MOLECULE_H_

#include <set>
#include <string>

using namespace std;

class Reaction;


/*
** Molecule: The molecule class.
*/

class Molecule
{
 public:
  /*
  ** Constructors and destructors.
  */
  Molecule  (string id, string seq);
  ~Molecule ();

  /*
  ** Public member functions.
  */
  void      getID               (string *id);
  void      getSequence         (string *seq);
  int       getSeqLength        ();
  void      addAsReactant       (Reaction *reac);
  void      removeAsReactant    (Reaction *reac);
  void      addAsProduct        (Reaction *reac);
  void      removeAsProduct     (Reaction *reac);
  void      addAsCatalyst       (Reaction *reac);
  void      removeAsCatalyst    (Reaction *reac);
  void      addAsInhibitor      (Reaction *reac);
  void      removeAsInhibitor   (Reaction *reac);
  int       getNrAsReactant     ();
  int       getNrAsProduct      ();
  int       getNrAsCatalyst     ();
  int       getNrAsInhibitor    ();
  Reaction *getAsReactantFirst  ();
  Reaction *getAsReactantNext   ();
  Reaction *getAsProductFirst   ();
  Reaction *getAsProductNext    ();
  Reaction *getAsCatalystFirst  ();
  Reaction *getAsCatalystNext   ();
  Reaction *getAsInhibitorFirst ();
  Reaction *getAsInhibitorNext  ();

  /*
  ** Public member variables.
  */
  int  closureF;
  bool isInSet;
  
 private:
  /*
  ** Private member variables.
  */
  int                      seqLength;
  string                   ID, sequence;
  set<Reaction*>           asReactant, asProduct, asCatalyst, asInhibitor;
  set<Reaction*>::iterator itReactant, itProduct, itCatalyst, itInhibitor;
};


#endif  /* _MOLECULE_H_ */

/*
** EoF: Molecule.h
*/
