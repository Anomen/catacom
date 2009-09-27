#include <sys/types.h>  // socket(), connect()
#include <sys/socket.h> // socket(), AF_INET, connect()
#include <string.h>     // memset()
#include <limits.h>     // MAX_INPUT
#include <stdlib.h>     // atoi()
#include <netdb.h>      // gethostbyname()

#include <string>
#include <iostream>
#include <sstream>

#include "CConnexion.h"
#include "CException.h"

using namespace nsRes;
using namespace std;

void CConnexion::Init() throw (CException)
{
    if (m_Sd) return;

    if (m_Port == -1)
        throw CException ("Aucun port précisé.");

    if (m_Serveur == "")
        throw CException ("Aucun serveur précisé.");

    if ((m_Sd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        throw CException ("Erreur à l'ouverture de la socket.");

    hostent * Hostent = gethostbyname (m_Serveur.c_str());
    if (!Hostent)
        throw CException ("Erreur gethostbyname()");

    sockaddr_in Adr;
    memset (&Adr, 0, sizeof (Adr));
    Adr.sin_family      = AF_INET;
    Adr.sin_port        = htons (m_Port);
    Adr.sin_addr.s_addr = ((struct in_addr *) (Hostent->h_addr))->s_addr;

    if (connect (m_Sd, reinterpret_cast<sockaddr* > (&Adr), sizeof (Adr)) < 0)
        throw CException ("Erreur connect()");
}

string CConnexion::Read() throw (CException)
{
    Init();

    int NbLu (0);
    string Ret;
    char Buf[MAX_INPUT];

    while (1) {
        if (!(NbLu = read (m_Sd, Buf, MAX_INPUT))) break;
        Buf[NbLu] = '\0';
        Ret += string (Buf);

        if (NbLu < MAX_INPUT)
            break;
    }
    Ret[Ret.size()-1] = '\0';

    int Req = atoi (Ret.substr (0, 4).c_str());
    if (Req != 200)
        throw CException (Error[Req]);
    else
        Ret = Ret.substr (4, Ret.size()-8);

    return Ret;
}

void CConnexion::Write (string Str) throw (CException)
{
    Init();

    Str += "\nFIN";

    int NbEnv (0); 
    if ((NbEnv = write (m_Sd, Str.c_str(), Str.size())) <= 0)
        throw CException ("Erreur send()");
}

string CConnexion::Demande (string Str) throw (CException)
{
    Write (Str);
    return Read();
}
