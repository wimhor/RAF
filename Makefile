RAF:
	cd src; \
	g++ -o ../RAF RAF.cxx Molecule.cxx Reaction.cxx ReacSet.cxx; \
	cd ..

clean:
	cd src; rm -f *~ *.o; cd ..
