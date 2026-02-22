/*
** RAF.cxx: Compute the maxRAF from a given reaction set.
**
** Wim Hordijk   Last modified: 9 March 2019
*/

#include <iostream>
#include <string.h>
#include "ReacSet.h"

using namespace std;


/*
** main: The main routine of the program.
**
** Parameters:
**   - argc: The number of arguments to the program.
**   - argv: A list with the arguments.
**
** Returns:
**   - If everything went fine: 0.
**   - Otherwise:               1.
*/

int main (int argc, char **argv)
{
  int       status, rSize;
  char      CRSfile[256];
  ifstream  ifs;
  ReacSet  *rSet;

  status = 0;

  /*
  ** Get the input file name.
  */
  if (argc != 2)
  {
    status = 1;
    cerr << "Invalid number of arguments." << endl;
    cerr << "  Usage: " << argv[0] << " <inputFile>" << endl;
    goto End_of_Routine;
  }
  strcpy (CRSfile, argv[1]);

  /*
  ** Read in the reaction set.
  */
  ifs.open (CRSfile);
  if (!ifs.is_open ())
  {
    status = 1;
    cerr << "Could not open input file " << CRSfile << endl;
    goto End_of_Routine;
  }
  rSet = new ReacSet ();
  if (rSet->readFromFile (ifs) == -1)
  {
    status = 1;
    goto End_of_Routine;
  }
  ifs.close ();

  /*
  ** Find the maxRAF.
  */
  rSize = rSet->findMaxRAF ();
  rSet->printMaxRAF (false);

 End_of_Routine:
  /*
  ** Close the input file, if necessary.
  */
  ifs.close ();
  /*
  ** Return the status.
  */
  return (status);
}


/*
** EoF: RAF.cxx
*/
