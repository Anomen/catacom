#
# This file is part of Catacom.
# Copyright (C) 2008-2009  Kevin Vicrey <kevin.vicrey@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
