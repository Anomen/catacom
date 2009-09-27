/**
 * @File   : CException.hxx
 *
 * @Author : Kévin Vicrey
 *
 * @Date   : 11/12/2007
 *
**/

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

