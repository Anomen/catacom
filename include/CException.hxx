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

#if !defined __CEXCEPTION_HXX__
#define      __CEXCEPTION_HXX__

#include <sstream>

#define CEXCEPTION nsUtil::CException

inline CEXCEPTION::CException (int Num) throw()
{
    std::ostringstream oss;
    oss << Num;
    m_Str = oss.str();
}

inline CEXCEPTION::CException (std::string Str) throw()
    : m_Str (Str) { }

inline CEXCEPTION::~CException (void) throw() { }

inline const std::string & CEXCEPTION::GetStr (void) const throw()
{
    return m_Str;
}

#endif    /*  __CEXCEPTION_HXX__ */

