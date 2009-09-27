#if !defined __CCONNEXION_HXX__
#define      __CCONNEXION_HXX__

#include <unistd.h> // close()

#define CCONNEXION nsRes::CConnexion

inline CCONNEXION::CConnexion (string Serveur /* = "" */, int Port /* = -1 */)
    : m_Serveur (Serveur), m_Sd (0), m_Port (Port)
{
    Error[300] = "Le serveur n'arrive pas à vous renvoyer le résultat.";
    Error[301] = "Erreur de connexion à la Base de Donnée.";
    Error[302] = "Erreur de Base de Donnée.";
    Error[303] = "Aucun film trouvé.";
    Error[304] = "Film déjà dans la base de donnée.";
    Error[305] = "Erreur de commande.";
    Error[306] = "Erreur sur l'indice du film.";
    Error[307] = "Le moteur de recherche est incorrecte.";
}

inline CCONNEXION::~CConnexion()
{
    Close();
}

inline void CCONNEXION::Close()
{
    close (m_Sd);
    m_Sd = 0;
}

inline void CCONNEXION::SetPort (int Port)
{
    m_Port = Port;
}

inline void CCONNEXION::SetServeur (string Serveur)
{
    m_Serveur = Serveur;
}

#endif
