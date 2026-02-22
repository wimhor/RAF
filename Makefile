RAF: RAF.cxx Molecule.h Molecule.cxx Reaction.h Reaction.cxx ReacSet.h ReacSet.cxx def.h
	g++ -o RAF RAF.cxx Molecule.cxx Reaction.cxx ReacSet.cxx

winRAF: RAF.cxx Molecule.h Molecule.cxx Reaction.h Reaction.cxx ReacSet.h ReacSet.cxx def.h
	x86_64-w64-mingw32-c++ -o winRAF.exe RAF.cxx Molecule.cxx Reaction.cxx ReacSet.cxx -static-libgcc -static -lpthread

clean:
	rm -f *~ *.o

