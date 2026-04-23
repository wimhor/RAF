![RAF logo](/img/RAFlogo.jpg)

# RAF
Code for detecting and analyzing Reflexively Autocatalytic and Food-generated (RAF) sets, and for generating random instances of the Binary Polymer Model.

This code is a cleaned-up version of what was developed over many years as typical research code with all kinds of trials and errors. The current code provides the basic functionality of finding the maxRAF, CAF, and random samples of irreducible RAFs (iRAFs) and closed RAFs (cRAFs) in a given chemical reaction network. For an introduction to autocatalytic sets, see
- W. Hordijk and M. Steel. [Autocatalytic networks at the basis of life's origin and organization](https://www.mdpi.com/2075-1729/8/4/62). _Life_ 8:62, 2018.
- W. Hordijk. [A history of autocatalytic sets](https://link.springer.com/article/10.1007/s13752-019-00330-w). _Biological Theory_ 14(4):224-246, 2019.

There are two programs, one for generating random instances of the binary polymer model, and one for computing various RAF sets. This code comes without any warranty, but feel free to use it for your own purposes. If you do so, a reference to the [current repo](https://github.com/wimhor/RAF) will be appreciated.

## Compile
To compile, go into the `src` directory and type

    make BPM

to compile the `BinPolModel` program or

    make RAF

to compile the `RAF` program. The executables will be placed in the parent directory.

## Run
To run, go back up to the parent directory and type

    ./BinPolModel -help

or

    ./RAF -help
    
to see the list of required and optional program arguments.

## Arguments
Both programs require at least a certain number of arguments, while others are optional.

For the `BinPolModel` program, the following arguments are required:
  - `n`: The maximum polymer length (`n > 1`).
  - `t`: The maximum food polymer length (`1 <= t <= n`).
  - `p`: The catalysis probability (`p >= 0.0`).
  
while these are optional (defaults indicated):
  - `-c C`:  The catalysis assignment method `C`: `unif` for uniform (default) or `plaw` for power law (the value of `p` will be used for the power law parameter).
  - `-i I`:  The number of instances `I` to generate (`I > 0`, default = 1).
  - `-f`:    Do not allow food molecules to be catalysts.
  - `-s S`:  The random seed `S` (`S >= 0`, default = 0: use current time).
  - `-help`: Print this help message and exit.

For the `RAF` program, the following argument is required:
  - `<infile>`: The file from which to read the reaction network.

while these are optional (defaults indicated):
  - `-CAF`:     Compute the CAF.
  - `-iRAF I`:  Generate a random sample of size `I` of irreducible RAFs (iRAFs; only unique ones are shown). If `I=0`, find all iRAFs (this may take very long!).
  - `-cRAF C`:  Generate a random sample of size `C` of closed RAFs (cRAFs; only unique ones are shown). If `C=0`, write the maxRAF to a file 'pyCOT.crn' to compute all organizations with pyCOT.
  - `-print P`: What to print: `none` = nothing (default), `ID` = reaction IDs only, `reac` = full reactions.
  - `-help`:    Print this help message and exit.

Note that the `RAF` program always computes the maxRAF by default. If `cRAF 0` is included as an argument, the maxRAF is written to a file 'pyCOT.crn' that can be used as an input file to the [pyCOT](https://github.com/tveloz/pyCOT) program to compute all organizations within the maxRAF.

## Example
The `BinPolModel` program generates input files for the `RAF` program in the required format. One example input file is included (`example.crn`) containing an instance of the binary polymer model with `n=5`, `t=2`, and `p=0.0055`. This reaction network has a maxRAF of 20 reactions, which contains a CAF of 6 reactions, 3 iRAFs, and 6 cRAFs. Run the following command to see these results:

    ./RAF example.crn -CAF -iRAF 100 -cRAF 100 -print ID

Note that not all iRAFs or cRAFs may show up each time the program is run, depending on the sample size, due to the random sampling method.

## Input format
See the example input file `example.crs` for the required format for the reaction network. A detailed description will be added here eventually...

## Notes
- This repo is under continuous development, and improvements and new functionality will hopefully be added over time.
- The `BinPolModel` program uses an implementation of the Zipf distribution (zipf.c) by [Ken Christensen](https://cse.usf.edu/~kchriste/christen.html) to generate power law distributed values.
- Compiling and running these programs has been tested in a Linux environment, and although only standard C & C++ libraries are used, no guarantees are given that the programs compile and work properly on other operating systems.

## Acknowledgements
This repo was made possible in part by funding from the [MATOMIC project](https://www.sdu.dk/en/forskning/matomic).

![MATOMIC logo](/img/matomic.png)

