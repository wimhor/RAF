/*
** RAF.cxx: Find the maxRAF in a given reaction network.
**
** Wim Hordijk   Last modified: 6 March 2026
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
  char      fileName[256];
  ifstream  ifs;
  ofstream  ofs;
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
  strcpy (fileName, argv[1]);

  /*
  ** Read the reaction network from the given input file.
  */
  ifs.open (fileName);
  if (!ifs.is_open ())
  {
    status = 1;
    cerr << "Could not open input file " << fileName << endl;
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
  ** Write the reaction network to an output file.
  */
  ofs.open ("out.txt");
  rSet->writeToFile (ofs);
  ofs.close ();

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
