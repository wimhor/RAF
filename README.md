![RAF logo](/img/RAFlogo.jpg)

# RAF
Code for detecting and analyzing Reflexively Autocatalytic and Food-generated (RAF) sets, and for generating random instances of the Binary Polymer Model.

This code is a cleaned-up version of what was developed over many years as typical research code with all kinds of trials and errors. The current code provides the basic functionality of finding the maxRAF, CAF, and a sample of irreducible RAFs (iRAFs) in a given reaction network. For an introduction to autocatalytic sets, see
- W. Hordijk and M. Steel. [Autocatalytic networks at the basis of life's origin and organization](https://www.mdpi.com/2075-1729/8/4/62). _Life_ 8:62, 2018.
- W. Hordijk. [A history of autocatalytic sets](https://link.springer.com/article/10.1007/s13752-019-00330-w). _Biological Theory_ 14(4):224-246, 2019.

There are two programs, one for computing various RAF sets, and one for generating random instances of the binary polymer model. This code comes without any warranty, but feel free to use it for your own purposes. If you do so, a reference to the [current repo](https://github.com/wimhor/RAF) will be appreciated.

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
  - `-c C`:  The catalysis assignment method C: `unif` for uniform (default) or `plaw` for power law (the value of `p` will be used for the power law parameter).
  - `-i I`:  The number of instances I to generate (`I > 0`, default = 1).
  - `-f`:    Do not allow food molecules to be catalysts.
  - `-s S`:  The random seed S (`S >= 0`, default = 0: use current time).
  - `-help`: Print this help message and exit.

For the `RAF` program, the following argument is required:
  - `<infile>`: The file from which to read the reaction network.

while these are optional (defaults indicated):
  - `-maxRAF`:  Compute the maxRAF.
  - `-CAF`:     Compute the CAF.
  - `-iRAF S`:  Generate a sample of iRAFs of size S (only unique ones are saved).
  - `-print P`: What to print: `none` = nothing (default), `ID` = reaction IDs only, `reac` = full reactions.
  - `-help`:    Print this help message and exit.

## Example
The `BinPolModel` program generates input files for the `RAF` program in the required format. One example input file is included (`example.crs`) containing an instance of the binary polymer model with `n=5`, `t=2`, and `p=0.0055`. This reaction network has a maxRAF of 7 reactions, which contains a CAF of 4 reactions and 3 iRAFs each of just 1 reaction. Run the following command to see these results:

    ./RAF example.crs -maxRAF -CAF -iRAF 10 -print ID

See the example input file for the required format for the reaction network. (A detailed description will be added here soon(ish)).

## Note
This repo is under continuous development, and improvements and new functionality will hopefully be added over time.

## Acknowledgements
This repo was made possible in part by funding from the [MATOMIC project](https://www.sdu.dk/en/forskning/matomic).

![MATOMIC logo](/img/matomic.png)

