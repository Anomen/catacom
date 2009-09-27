# Les fichiers inclus
CONSTANTS_H  = include/constants.h
CEXCEPTION_H = include/CException.h include/CException.hxx
CCONNEXION_H = include/CConnexion.h include/CConnexion.hxx $(CEXCEPTION_H)

# Commande générique pour compiler
OPT = -Wall -O3 -Iinclude/
COMPILER = g++ -c $< -o $*.o $(OPT)

# Nom du programme à compiler
nom = catacom

$(nom): lib/$(nom).o lib/CConnexion.o
	g++ -s $^ -o $(nom) $(OPT) -lpthread -ldl

lib/$(nom).o: $(nom).cxx $(CEXCEPTION_H) $(CONSTANTS_H)
	$(COMPILER)

lib/CConnexion.o: util/CConnexion.cxx $(CCONNEXION_H)
	$(COMPILER)

clean:
	rm lib/*.o -fv; rm catacom -fv;
