/*
 * This file is part of Catacom.
 * Copyright (C) 2008-2009  Kevin Vicrey <kevin.vicrey@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdlib.h> // atoi()
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <map>
#include <vector>

#include "CConnexion.h"
#include "CException.h"

using namespace std;
using namespace nsUtil;
using namespace nsRes;

namespace
{
    int Isdigit( int x ) { return isdigit( x ); }

    CConnexion *Conn;
    enum Command_t { Add = 1, Remove, List, Show, Engines };
    map<Command_t, string> VCommand;
    string Engine ("");
    string Usage ("catacom -s <serveur> -p <port> [-a <film> | -d <film> | -l | -v <film> | -e[engine]]");

    void analyseCommande(int argc, char *argv[])
    {
        int c;
        bool noCmd = true;
        while ((c = getopt(argc, argv, "s:p:la:e::d:v:")) != -1)
        {
            noCmd = false;
            switch (c)
            {
              case '?':
                throw CException (Usage);
              break;

              case 'a': VCommand[Add] = optarg ? optarg : "";   break;
              case 'd': VCommand[Remove] = optarg;              break;
              case 'l': VCommand[List] = "";                    break;
              case 'v': VCommand[Show] = optarg;                break;
              case 'e': 
                VCommand[Engines] = optarg ? optarg : "";
                if (optarg != 0)
                    Engine = optarg; 
              break;

              case 'p': Conn->SetPort (atoi(optarg));       break;
              case 's': Conn->SetServeur (optarg);          break;
            }
        }

        if (noCmd)
            throw CException (Usage);
    }

    void CmdAdd (string Film)
    {
        // On recherche le film concerné
        cout << "Recherche en cours...\n";

        string Rech = Conn->Demande("SEARCH " + Engine + " " + Film);
        istringstream oss (Rech);

        vector<string> VRes;
        string Ligne;
        while (getline (oss, Ligne))
            VRes.push_back (Ligne);

        int c(0), Taille (VRes.size());
        while (c < Taille)
        {
            cout << endl;

            int j (0);
            for (; j < 10 && c < Taille; ++j && ++c)
                cout << "    " << VRes[c] << endl;

            cout << "\ns: suivant, p: precedent, numero: enregistrement, q: quit\n";

            while (1)
            {
                cout << "Votre choix: ";
                string Choix;
                cin >> Choix;

                if (Choix == "p")
                {
                    if (c-j == 0) continue;
                    c -= j + 10;
                    if (c < 0) c = 0;
                    break;
                }
                else if (count_if (Choix.begin(), Choix.end(), Isdigit) == (int) Choix.size())
                {
                    if (atoi (Choix.c_str()) > Taille || atoi (Choix.c_str()) <= 0)
                    {
                        cout << "Le choix n'est pas correct.\n";
                        continue;
                    }

                    string Titre = VRes[atoi(Choix.c_str())-1];
                    cout << "Demande d'enregistrement en cours...\n";
                    Conn->Demande("ADD " + Engine + " " + Film + " " + Choix);
                    cout << "Film \"" << Titre.substr (strcspn (Titre.c_str(), " ") + 1, Titre.size()) << "\" ajouté !\n";
                    c = Taille;
                    break;
                }
                else if (Choix == "q")
                {
                    c = Taille;
                    break;
                }
                else if (Choix != "s")
                    cout << "Le choix n'est pas correct.\n";
                else if ((Choix != "s" || c != Taille))
                    break;
            }
        }

    } // CmdAdd()

    void CmdRemove (string Film)
    {
        cout << "Demande de suppression en cours...\n";
        Conn->Demande ("REMOVE " + Film + " 1");
        cout << "Film supprimé !\n";

    } // CmdRemove()

    void CmdView (string Film)
    {
        cout << Conn->Demande ("SHOW " + Film) << endl;

    } // CmdRemove()

}


int main (int argc, char **argv)
{
    Conn = new CConnexion;

    try
    {
        analyseCommande (argc, argv);

        for (map<Command_t, string>::iterator i = VCommand.begin(); i != VCommand.end(); i++)
        {
            if (i->second != "")
                switch (i->first)
                {
                    case Add:    CmdAdd   (i->second);   break;
                    case Remove: CmdRemove(i->second);   break;
                    case Show:   CmdView  (i->second);   break;
                    case List:    break;
                    case Engines: break;
                }
            else
            {
                if (i->first == List)
                    cout << Conn->Demande("LIST") << endl;
                if (i->first == Engines)
                    cout << Conn->Demande("ENGINES") << endl;
            }
        }
    }
    catch (const CException & E)
    {
        cout << E.GetStr() << endl;
    }

    return 0;
}
