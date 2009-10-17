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
