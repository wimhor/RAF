/*
** Molecule.h: Definition of a molecule type.
**
** Wim Hordijk   Last modified: 4 March 2026
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
  Molecule  (string seq);
  ~Molecule ();

  /*
  ** Public member functions.
  */
  void      getSequence         (string *seq);
  int       getSeqLength        ();
  void      addAsReactant       (Reaction *reac);
  void      removeAsReactant    (Reaction *reac);
  void      addAsProduct        (Reaction *reac);
  void      removeAsProduct     (Reaction *reac);
  void      addAsCatalyst       (Reaction *reac);
  void      removeAsCatalyst    (Reaction *reac);
  int       getNrAsReactant     ();
  int       getNrAsProduct      ();
  int       getNrAsCatalyst     ();
  Reaction *getAsReactantFirst  ();
  Reaction *getAsReactantNext   ();
  Reaction *getAsProductFirst   ();
  Reaction *getAsProductNext    ();
  Reaction *getAsCatalystFirst  ();
  Reaction *getAsCatalystNext   ();

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
  string                   sequence;
  set<Reaction*>           asReactant, asProduct, asCatalyst;
  set<Reaction*>::iterator itReactant, itProduct, itCatalyst;
};


#endif  /* _MOLECULE_H_ */

/*
** EoF: Molecule.h
*/
