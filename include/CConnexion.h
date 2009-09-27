#if !defined __CCONNEXION_H__
#define      __CCONNEXION_H__

#include <string>
#include <map>
#include "CException.h"

namespace nsRes
{
    using std::string;
    using std::map;
    using nsUtil::CException;

    class CConnexion
    {
      public:
        CConnexion (string Serveur = "", int Port = -1);
        ~CConnexion();

        void Init () throw (CException);
        void Close();

        string Read    ()           throw (CException);
        void   Write   (string Str) throw (CException);
        string Demande (string Str) throw (CException);

        // Les modifieurs
        void SetServeur (string Serveur);
        void SetPort    (int    Port   );

      private:
        map<int, string> Error;
        string m_Serveur;
        int    m_Sd, m_Port;

        void Convert (string & Str) const;
    };
}

#include "CConnexion.hxx"

#endif
