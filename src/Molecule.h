/*
** Molecule.h: Definition of a molecule type.
**
** Wim Hordijk   Last modified: 23 April 2026
*/

#ifndef _MOLECULE_H_
#define _MOLECULE_H_

#include <list>
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
  void      getSequence         (string& seq);
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
  bool inClosure;
  
 private:
  /*
  ** Private member variables.
  */
  int                       seqLength;
  string                    sequence;
  list<Reaction*>           asReactant, asProduct, asCatalyst;
  list<Reaction*>::iterator itAsReactant, itAsProduct, itAsCatalyst;
};


#endif  /* _MOLECULE_H_ */

/*
** EoF: Molecule.h
*/
