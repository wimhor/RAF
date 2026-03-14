/*
** RAF.cxx: Find the maxRAF and the CAF in a given reaction network.
**
** Wim Hordijk   Last modified: 14 March 2026
*/

#include <iostream>
#include <string.h>
#include "ReacSet.h"

using namespace std;

/*
** Function prototypes.
*/
int getArguments (int argc, char **argv);

/*
** Global variables.
*/
bool   computeMaxRAF, computeCAF, computeIRAFs, computeCRAFs, showID, showReac;
string inputFile;

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
  ** Get the program arguments.
  */
  if (getArguments (argc, argv) != 0)
  {
    status = 1;
    goto End_of_Routine;
  }
  
  /*
  ** Read the reaction network from the given input file.
  */
  ifs.open (inputFile);
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
  **
  ofs.open ("out.txt");
  rSet->writeToFile (ofs);
  ofs.close ();
  */
  
  /*
  ** Find various RAF sets as requested.
  */
  if (computeMaxRAF)
  {
    /*
    ** Find the maxRAF.
    */
    rSize = rSet->findMaxRAF ();
    cout << "maxRAF: " << rSize << endl;
    if (showID && !showReac)
    {
      rSet->printMaxRAF (false);
    }
    else if (showReac)
    {
      rSet->printMaxRAF (true);
    }
  }
  if (computeCAF)
  {
    /*
    ** Find the CAF.
    */
    rSize = rSet->findCAF ();
    cout << "CAF: " << rSize << endl;
    if (showID && !showReac)
    {
      rSet->printCAF (false);
    }
    else if (showReac)
    {
      rSet->printCAF (true);
    }
  }
  
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
** getArguments: Get and parse the command line arguments.
**
** Parameters:
**   argc: The number of arguments.
**   argv: A list with the arguments.
**
** Returns:
**   - If everything went fine:  0.
**   - Otherwise:               -1.
*/

int getArguments (int argc, char **argv)
{
  int  status, i;
  char arg[32];

  status = 0;

  /*
  ** Set defaults.
  */
  computeMaxRAF = false;
  computeCAF = false;
  computeIRAFs = false;
  computeCRAFs = false;
  showID = false;
  showReac = false;
  inputFile.assign ("");
  
  /*
  ** Get and check all arguments.
  */
  if (argc < 2)
  {
    status = -1;
    cerr << "Providing an input file name is mandatory. Use '" << argv[0]
	 << " -help' to see the required and optional program arguments." << endl;
    goto End_of_Routine;
  }
  if (strcmp (argv[1], "-help") == 0)
  {
    status = -1;
    cout << "Usage: " << argv[0]
	 << " <inFile> [-maxRAF] [-CAF] [-id] [-reac] [-help]" << endl << endl
	 << "  <inFile>: The file from which to read the reaction network." << endl
	 << "  -maxRAF:  Compute the maxRAF." << endl
	 << "  -CAF:     Compute the CAF." << endl
	 << "  -id:      Show RAF reaction IDs." << endl
	 << "  -reac:    Show RAF reactions in full." << endl
	 << "  -help:    Print this help message and exit." << endl;
    goto End_of_Routine;
  }
  inputFile.assign (argv[1]);
  i = 2;
  while (i < argc)
  {
    if (strcmp (argv[i], "-maxRAF") == 0)
    {
      computeMaxRAF = true;
      i++;
    }
    else if (strcmp (argv[i], "-CAF") == 0)
    {
      computeCAF = true;
      i++;
    }
    else if (strcmp (argv[i], "-id") == 0)
    {
      showID = true;
      i++;
    }
    else if (strcmp (argv[i], "-reac") == 0)
    {
      showReac = true;
      i++;
    }
    else
    {
      status = -1;
      cerr << "Unknow option " << argv[i] << endl;
      goto End_of_Routine;
    }
  }

 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** EoF: RAF.cxx
*/
