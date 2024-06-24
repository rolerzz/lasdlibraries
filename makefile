cc = g++
cflags = -Wall -pedantic -O3 -std=c++20 -fsanitize=address

objects = main.o

libcon = container/container.hpp container/testable.hpp container/traversable.cpp container/traversable.hpp container/mappable.hpp container/dictionary.cpp container/dictionary.hpp container/linear.cpp container/linear.hpp

libexc1a = vector/vector.cpp vector/vector.hpp list/list.cpp list/list.hpp

libexc1b = stack/stack.hpp stack/lst/stacklst.cpp stack/lst/stacklst.hpp stack/vec/stackvec.cpp stack/vec/stackvec.hpp queue/queue.hpp queue/lst/queuelst.cpp queue/lst/queuelst.hpp queue/vec/queuevec.cpp queue/vec/queuevec.hpp

libexc2a = iterator/iterator.hpp binarytree/binarytree.cpp binarytree/binarytree.hpp binarytree/lnk/binarytreelnk.cpp binarytree/lnk/binarytreelnk.hpp binarytree/vec/binarytreevec.cpp binarytree/vec/binarytreevec.hpp

libexc2b = bst/bst.cpp bst/bst.hpp

libexc3 = hashtable/hashtable.cpp hashtable/hashtable.hpp hashtable/clsadr/htclsadr.cpp hashtable/clsadr/htclsadr.hpp hashtable/opnadr/htopnadr.cpp hashtable/opnadr/htopnadr.hpp

main: $(objects)
	$(cc) $(cflags) $(objects) -o main

clean:
	clear; rm -rfv *.o; rm -fv main

main.o: main.cpp
	$(cc) $(cflags) -c main.cpp
