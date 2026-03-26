/*
** BinPolModel.cxx: Program for generating random instances of the binary polymer model.
**
** Wim Hordijk   Last modified: 26 March 2026
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <list>
#include <algorithm>
#include "zipf.h"

using namespace std;

/*
** Defines.
*/
#define UNIF01  (double)random () / RAND_MAX
#define UNIFCAT 0
#define PLAWCAT 1

/*
** Function prototypes.
*/
int  getArguments      (int argc, char **argv);
void initBinPolModel   ();
void uniformCatalysis  ();
void powerlawCatalysis ();
int  indexToString     (int index, string& s);
int  stringToIndex     (string& s);
void generateFileName  (string& s, int i, int len);
void writeToFile       (ofstream& os);

/*
** Global variables.
*/
int        n, t, nrMolecules, nrFoodMols, nrReactions, catMethod, seed, nrInstances;
float      p;
bool       noFoodCat;
string    *molecules, **reactions;
list<int> *catalysts;


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
  int      status, i, l;
  string   fName;
  ofstream ofs;

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
  ** Set the random seed.
  */
  if (seed == 0)
  {
    seed = time (NULL);
  }
  srandom (seed);
  if (catMethod == PLAWCAT)
  {
    rand_val (seed);
  }

  /*
  ** Initialize the binary polymer model.
  */
  initBinPolModel ();
  
  /*
  ** Generate random instances of the binary polymer model and write them to file.
  */
  l = (int)rint (floor (log10 (nrInstances))) + 1;
  for (i = 1; i <= nrInstances; i++)
  {
    if (catMethod == UNIFCAT)
    {
      uniformCatalysis ();
    }
    else if (catMethod == PLAWCAT)
    {
      powerlawCatalysis ();
    }
    generateFileName (fName, i, l);
    ofs.open (fName + ".crs");
    writeToFile (ofs);
    ofs.close ();
  }
  
 End_of_Routine:
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
  n = 4;
  t = 2;
  p = 0.01;
  catMethod = UNIFCAT;
  nrInstances = 1;
  noFoodCat = false;
  seed = 0;
  
  /*
  ** Get and check all arguments.
  */
  if (argc < 4)
  {
    if (argc > 1 && strcmp (argv[1], "-help") == 0)
    {
      status = -1;
      cout << "Usage: " << argv[0]
	   << " n t p [-c {unif|plaw}] [-i I] [-f] [-s S] [-help]" << endl << endl
	   << "  n:     The maximum polymer length (n > 1)." << endl
	   << "  t:     The maximum food polymer length (1 <= t <= n)." << endl
	   << "  p:     The catalysis probability (p >= 0.0)." << endl
	   << "  -c C:  The catalysis assignment method C: 'unif' for uniform " << endl
	   << "         probability (default), or 'plaw' for power law distribution."
	   << endl
	   << "  -i I:  The number of instances I to generate (I > 0; default = 1)."
	   << endl
	   << "  -f:    Do not allow food molecules to be catalysts." << endl
	   << "  -s S:  The random seed S (S >= 0; default = 0: use current time)."
	   << endl
	   << "  -help: Print this help message and exit." << endl;
      goto End_of_Routine;
    }
    else
    {
      status = -1;
      cerr << "Arguments 'n', 't', and 'p' are mandatory. Use '" << argv[0]
	   << " -help' to see the required and optional program arguments." << endl;
      goto End_of_Routine;
    }
  }
  if ((sscanf (argv[1], "%d", &n) != 1) || (n < 2))
  {
    status = -1;
    cerr << "Invalid value for n: " << argv[1] << " (should be n>1)." << endl;
    goto End_of_Routine;
  }
  if ((sscanf (argv[2], "%d", &t) != 1) || (t < 1) || (t > n))
  {
    status = -1;
    cerr << "Invalid value for t: " << argv[2] << " (should be 1<=t<=n)." << endl;
    goto End_of_Routine;
  }
  if ((sscanf (argv[3], "%f", &p) != 1) || (p < 0.0))
  {
    status = -1;
    cerr << "Invalid value for p: " << argv[3] << " (should be p >= 0.0)." << endl;
    goto End_of_Routine;
  }
  i = 4;
  while (i < argc)
  {
    if (strcmp (argv[i], "-c") == 0)
    {
      sscanf (argv[++i], "%s", arg);
      if (strcmp (arg, "unif") == 0)
      {
	catMethod = UNIFCAT;
      }
      else if (strcmp (arg, "plaw") == 0)
      {
	catMethod = PLAWCAT;
      }
      else
      {
	status = -1;
	cerr << "Invalid catalysis assignment method: " << arg
	     << " (should be 'unif' (default) or 'plaw')." << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-i") == 0)
    {
      if ((sscanf (argv[++i], "%d", &nrInstances) != 1) || (nrInstances < 1))
      {
	status = -1;
	cerr << "Invalid value for I: " << argv[i] << " (should be I > 0)." << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-f") == 0)
    {
      noFoodCat = true;
      i++;
    }
    else if (strcmp (argv[i], "-s") == 0)
    {
      if ((sscanf (argv[++i], "%d", &seed) != 1) || (seed < 0))
      {
	status = -1;
	cerr << "Invalid value for S: " << argv[i] << " (should be S >= 0)." << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else
    {
      status = -1;
      cerr << "Unknow option " << argv[i] << endl;
      goto End_of_Routine;
    }
  }

  /*
  ** Calculate the number of molecules and reactions.
  */
  nrMolecules = pow ((double)2, (double)(n+1)) - 2;
  nrFoodMols = pow ((double)2, (double)(t+1)) - 2;
  nrReactions = (n-2) * pow ((double)2, (double)(n+1)) + 4;

 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** initBinPolModel: Initialize the binary polymer model by creating all
**                  molecules and all reactions.
**
** Returns:
**   If everything went fine:  0.
**   Otherwise:               -1.
*/

void initBinPolModel ()
{
  int    i, j, l, iter;
  string seq;

  /*
  ** Allocate the necessary memory.
  */
  molecules = new string[nrMolecules];
  reactions = new string*[nrReactions];
  for (i = 0; i < nrReactions; i++)
  {
    reactions[i] = new string[3];
  }
  catalysts = new list<int>[nrReactions];
  
  /*
  ** Create all molecules.
  */
  for (i = 0; i < nrMolecules; i++)
  {
    seq.clear ();
    l = indexToString (i, seq);
    (molecules[i]).assign (seq);
  }

  /*
  ** Create all reactions.
  */
  iter = 0;
  for (i = 0; i < nrMolecules; i++)
  {
    for (j = 0; j < nrMolecules; j++)
    {
      /*
      ** Concatenate the reactants and check the length of the product.
      */
      seq.assign (molecules[i]);
      seq.append (molecules[j]);
      if (seq.length () <= n)
      {
	/*
	** Add the reaction.
	*/
	l = stringToIndex (seq);
	(reactions[iter][0]).assign (molecules[i]);
	(reactions[iter][1]).assign (molecules[j]);
	(reactions[iter][2]).assign (molecules[l]);
	iter++;
      }
    }
  }
}


/*
** uniformCatalysis: Assign catalysts to reactions uniformly with probability p.
*/

void uniformCatalysis ()
{
  int i, j, start;

  /*
  ** Clear the current catalysts.
  */
  for (i = 0; i < nrReactions; i++)
  {
    (catalysts[i]).clear ();
  }

  /*
  ** Consider each possible (molecule, reaction) pair and assign the given molecule
  ** as a catalyst to the given reaction with probability p.
  */
  if (noFoodCat)
  {
    start = nrFoodMols;
  }
  else
  {
    start = 0;
  }
  for (i = start; i < nrMolecules; i++)
  {
    for (j = 0; j < nrReactions; j++)
    {
      /*
      ** Add the catalyst to the reaction with probability p.
      */
      if (UNIF01 < p)
      {
	(catalysts[j]).push_back (i);
      }
    }
  }
}


/*
** powerlawCatalysis: Assign catalysts to reactions according to a power law
**                    distribution.
*/

void powerlawCatalysis ()
{
  int                 i, j, nrCat, rnd, start;
  list<int>::iterator itCat;

  /*
  ** Clear the current catalysts.
  */
  for (i = 0; i < nrReactions; i++)
  {
    (catalysts[i]).clear ();
  }
  
  /*
  ** For each molecule, draw a random number from the Zipf distribution and
  ** assign it as a catalyst to that many random reactions.
  */
  if (noFoodCat)
  {
    start = nrFoodMols;
  }
  else
  {
    start = 0;
  }
  for (i = start; i < nrMolecules; i++)
  {
    /*
    ** Get the number of reactions the current molecule will catalyze.
    */
    nrCat = zipf (p, nrReactions) - 1;
    if (nrCat > nrReactions)
    {
      nrCat = nrReactions;
    }
    /*
    ** Draw 'nrReacs' random reactions to be catalyzed. Since most molecules will
    ** catalyze only a small number of reactions (or even none), this is just done
    ** with replacement to keep it simple.
    */
    for (j = 0; j < nrCat; j++)
    {
      rnd = random () % (nrReactions);
      itCat = find ((catalysts[rnd]).begin (), (catalysts[rnd]).end (), i);
      if (itCat == (catalysts[rnd]).end ())
      {
	(catalysts[rnd]).push_back (i);
      }
    }
  }
}


/*
** indexToString: Convert an index to the corresponding binary string.
**
** Parameters:
**   - index: The index to convert (a non-negative integer).
**   - s:     A pointer to a string to put the result in.
**
** Returns:
**   The length of the converted string.
*/

int indexToString (int index, string& s)
{
  int len, dec, l;

  /*
  ** Check the index.
  */
  if (index < 0)
  {
    len = 0;
    s.assign ("");
    goto End_of_Routine;
  }
  
  /*
  ** Convert the index to a string.
  */
  len = (int)rint (floor (log2 (index+2)));
  dec = index - (int)rint (pow ((double)2, (double)len)) + 2;
  for (l = 0; l < len; l++)
  {
    if (dec % 2 == 1)
    {
      s.insert (0, "1");
    }
    else
    {
      s.insert (0, "0");
    }
    dec /= 2;
  }

 End_of_Routine:
  /*
  ** Return the string length.
  */
  return (len);
}


/*
** stringToIndex: Get the corresponding index of a binary string.
**
** Parameters:
**   - s: A binary string.
**
** Returns:
**   The index of s (-1 if s is not a valid bit string).
*/

int stringToIndex (string& s)
{
  int  len, index, dec, inc, l;
  char c;

  /*
  ** Check the string.
  */
  len = s.length ();
  if (len == 0)
  {
    index = -1;
    goto End_of_Routine;
  }

  /*
  ** Convert the string to its index.
  */
  dec = 0;
  inc = 1;
  for (l = len-1; l >= 0; l--)
  {
    c = s.at (l);
    if (c == '1')
    {
      dec += inc;
    }
    else if (c != '0')
    {
      index = -1;
      goto End_of_Routine;
    }
    inc *= 2;
  }
  index = (int)rint (pow ((double)2, (double)len) - 2 + dec);

 End_of_Routine:
  /*
  ** Return the index.
  */
  return (index);
}


/*
** generateFileName: Generate a file name with enough leading zeros.
**
** Parameters:
**   - s:   A string to put the result in.
**   - i:   The current file number.
**   - len: The required length for the number (i.e., including leading zeros).
*/

void generateFileName (string& s, int i, int len)
{
  int d, k;

  s.assign ("bpm");
  d = (int)rint (floor (log10 (i))) + 1;
  for (k = d; k < len; k++)
  {
    s.append ("0");
  }
  s.append (to_string (i));
}


/*
** writeToFile: Write the reaction set to an output file stream.
**
** Parameters:
**   - os: The output file stream to write to.
*/

void writeToFile (ofstream& os)
{
  int                 i, j, nrCat;
  list<int>::iterator itCat;

  /*
  ** Write the reactions.
  */
  os << "#Reactions"<< endl;
  for (i = 0; i < nrReactions; i++)
  {
    os << "r" << i+1 << ": ";
    if ((reactions[i][0]).compare (reactions[i][1]) == 0)
    {
      os << "2 " << reactions[i][0];
    }
    else
    {
      os << reactions[i][0] << " + " << reactions[i][1];
    }
    os << " <=> " << reactions[i][2];
    if ((nrCat = (catalysts[i]).size ()) > 0)
    {
      j = 1;
      os << " (";
      itCat = (catalysts[i]).begin ();
      while (itCat != (catalysts[i]).end ())
      {
	os << molecules[*itCat];
	if (j < nrCat)
	{
	  os << " ";
	}
	j++;
	itCat++;
      }
      os << ")";
    }
    os << endl;
  }
  /*
  ** Write the food set.
  */
  os << "#Food" << endl;
  for (i = 0; i < nrFoodMols; i++)
  {
    os << molecules[i] << endl;
  }
}


/*
** EoF: BinPolModel.cxx
*/
