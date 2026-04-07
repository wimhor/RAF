/*
** RAF.cxx: Find various RAF sets within a given chemical reaction network.
**
** Wim Hordijk   Last modified: 7 April 2026
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
int    smplSizeI, smplSizeC;
bool   computeCAF, sampleiRAFs, samplecRAFs, showID, showReac;
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
  ** Find various RAF sets as requested. Always start with the maxRAF.
  */
  rSize = rSet->findMaxRAF ();
  cout << "maxRAF: " << rSize << endl;
  if (showReac)
  {
    rSet->printMaxRAF (true);
  }
  else if (showID)
  {
    rSet->printMaxRAF (false);
  }
  cout << endl;
  /*
  ** Find the CAF, if requested.
  */
  if (computeCAF)
  {
    rSize = rSet->findCAF ();
    cout << "CAF: " << rSize << endl;
    if (showReac)
    {
      rSet->printCAF (true);
    }
    else if (showID)
    {
      rSet->printCAF (false);
    }
    cout << endl;
  }
  /*
  ** Find iRAFs, if requested.
  */
  if (sampleiRAFs)
  {
    if (smplSizeI > 0)
    {
      /*
      ** Get a random iRAF sample.
      */
      rSize = rSet->sampleiRAFs (smplSizeI);
      cout << "iRAFs: " << rSize << endl;
      if (showReac)
      {
	rSet->printiRAFs (true);
      }
      else if (showID)
      {
	rSet->printiRAFs (false);
      }
      cout << endl;
    }
    else
    {
      /*
      ** Find all iRAFs.
      */
      rSet->findiRAFs ();
    }
  }
  /*
  ** Find cRAFs, if requested.
  */
  if (samplecRAFs)
  {
    if (smplSizeC > 0)
    {
      /*
      ** Get a random cRAF sample.
      */
      rSize = rSet->samplecRAFs (smplSizeC);
      cout << "cRAFs: " << rSize << endl;
      if (showReac)
      {
	rSet->printcRAFs (true);
      }
      else if (showID)
      {
	rSet->printcRAFs (false);
      }
      cout << endl;
    }
    else
    {
      /*
      ** Write the maxRAF in pyCOT format to calculate its organizations.
      */
      // To come...
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
  computeCAF = false;
  sampleiRAFs = false;
  samplecRAFs = false;
  showID = false;
  showReac = false;
  inputFile.assign ("");
  smplSizeI = 100;
  smplSizeC = 100;
  
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
	 << " <inFile> [-CAF] [-iRAF I] [-cRAF C] [-print {none|ID|reac}] [-help]"
	 << endl << endl
	 << "  <inFile>: The file from which to read the reaction network." << endl
	 << "  -CAF:     Compute the CAF." << endl
	 << "  -iRAF I:  Generate a random sample of size I of iRAFs (only unique ones "
	 << endl
	 << "            are shown). If I=0, find all iRAFs (this may take very long!)."
	 << endl
	 << "  -cRAF C:  Generate a random sample of size C of cRAFs (only unique ones "
	 << endl
	 << "            are shown)."
	 << endl
	 << "  -print P: What to print: 'none' = nothing (default), 'ID' = reaction"
	 << endl
	 << "            IDs only, 'reac' = full reactions." << endl
	 << "  -help:    Print this help message and exit." << endl;
    goto End_of_Routine;
  }
  inputFile.assign (argv[1]);
  i = 2;
  while (i < argc)
  {
    if (strcmp (argv[i], "-CAF") == 0)
    {
      computeCAF = true;
      i++;
    }
    else if (strcmp (argv[i], "-iRAF") == 0)
    {
      i++;
      if (i >= argc)
      {
	status = -1;
	cerr << "Missing value for argument '-iRAF'." << endl;
	goto End_of_Routine;
      }
      if ((sscanf (argv[i], "%d", &smplSizeI) != 1) || (smplSizeI < 0))
      {
	status = -1;
	cerr << "Invalid value for iRAF sample size: " << argv[i] << endl;
	goto End_of_Routine;
      }
      sampleiRAFs = true;
      i++;
    }
    else if (strcmp (argv[i], "-cRAF") == 0)
    {
      i++;
      if (i >= argc)
      {
	status = -1;
	cerr << "Missing value for argument '-cRAF'." << endl;
	goto End_of_Routine;
      }
      if ((sscanf (argv[i], "%d", &smplSizeC) != 1) || (smplSizeC < 1))
      {
	status = -1;
	cerr << "Invalid value for cRAF sample size: " << argv[i] << endl;
	goto End_of_Routine;
      }
      samplecRAFs = true;
      i++;
    }
    else if (strcmp (argv[i], "-print") == 0)
    {
      i++;
      if (i >= argc)
      {
	status = -1;
	cerr << "Missing value for argument '-print'." << endl;
	goto End_of_Routine;
      }
      else if (strcmp (argv[i], "none") == 0)
      {
	showID = false;
	showReac = false;
      }
      else if (strcmp (argv[i], "ID") == 0)
      {
	showID = true;
	showReac = false;
      }
      else if (strcmp (argv[i], "reac") == 0)
      {
	showID = false;
	showReac = true;
      }
      else
      {
	status = -1;
	cerr << "Invalid value for argument '-show': " << argv[i] << "." << endl
	     << "  Should be 'none', 'ID', or 'reac'." << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else
    {
      status = -1;
      cerr << "Unknow option " << argv[i] << "." << endl;
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
