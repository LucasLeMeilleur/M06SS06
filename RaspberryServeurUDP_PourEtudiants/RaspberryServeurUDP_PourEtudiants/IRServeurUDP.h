#ifndef IRSERVEURUDP_H
#define IRSERVEURUDP_H

#ifdef __unix__
#include <arpa/inet.h>
#include <unistd.h>
#elif _WIN32 || _WIN64
#include <winsock2.h>
//#pragma comment(lib, "Ws2_32.dll")
#endif

#include <string>

/*! La classe IRServeurUDP
    \brief La classe IRServeur UDP permet la mise en place d'un serveur UDP sur une interface réseau et un port souhaité. Une fois en écoute, le serveur UDP peut lire des message et répondre aux messages reçus.

    Pour créer un serveur UDP, commencer par créer un objet de la classe IRServeurUDP comme suit :
    \code
    IRServeurUDP serveur;
    \endcode
    La mise en écoute du serveur démarre avec la méthode OuvrirLaSocketDEcoute(). Il est possible d'écouter des messages uniquement en local sur le port 4000 par exemple en écrivant :
    \code
    serveur.OuvrirLaSocketDEcoute(4000, "127.0.0.1");
    \endcode
    ou bien d'écouter sur toutes les interfaces réseaux de la machine en tapant :
    \code
    serveur.OuvrirLaSocketDEcoute(4000, "0.0.0.0");
    \endcode
    Remarque : le numéro de port est a adapté en fonction de vos spécifications ou de vos besoins. Il est nécessaire que le client connaisse à l'avance ce numéro de port sans quoi il ne pourra jamais réussir à se connecter au serveur.
    Une fois la socket d'écoute ouverte, vous pouvez recevoir des messages de clients. Si les messages sont de type texte, on utilisera la méthode RecevoirUnMessage() comme dans l'exemple suivant :
    \code
    string message;
    serveur.RecevoirUnMessage(message);
    cout << message << endl;
    \endcode
    Si les messages sont une suite d'octets, on utilisera la méthode RecevoirDesOctets() comme dans l'exemple suivant :
    \code
    // Déclaration d'un tableau pouvant contenir 20 octets maximum. Cette taille est à adapter en fonction de vos besoins.
    unsigned char tab[20];
    int nbOctetsRecus = serveur.RecevoirDesOctets(tab, 20);
    // Affichage de chaque octet reçu en hexa :
    for(int i=0; i<nbOctetsRecus; i++)
    {
        cout << hex << (unsigned int) tab[i] << endl;
    }
    \endcode
    Une fois un message reçu, vous pouvez répondre au client, soit en lui envoyant un message de type texte, comme dans l'exemple suivant :
    \code
    serveur.EnvoyerUnMessage("Reponse");
    \endcode
    ou en lui envoyant un tableau d'octets comme suit :
    \code
    unsigned char reponse[4] = {0x01, 0x02, 0xFE, 0xFF};
    serveur.EnvoyerDesOctets(reponse, 4);
    \endcode
*/

class IRServeurUDP
{
    private :
        std::string m_adresseIPDEcoute;
        unsigned short m_portDEcoute;
        int m_socketServeurUDP;
        static int m_nbServeurUDP;
        struct sockaddr_in m_addrServeur;
        struct sockaddr_in from; // Le client

    public :
        //! Constructeur de la classe
        /*!
            \brief Le constructeur initialise les attributs de la classe. L'adresse IP d'écoute est initialisée à 127.0.0.1 et le port à 4000.
        */
        IRServeurUDP();
        //! Destructeur de la classe
        /*!
            \brief Le destructeur ferme la socket d'écoute si ce n'est pas fait.
        */
        ~IRServeurUDP();

        //! Méthode permettant d'ouvrir la socket d'écoute sur une adresse IP et un port donnés.
	    /*!
            \brief Méthode permettant d'ouvrir la socket serveur UDP et l'attacher à une adresse IP et un port.
            \param adresseIPDEcoute l'adresse IP du serveur UDP, 0.0.0.0 pour écouter sur toutes les interfaces réseaux disponibles
            \param portDEcoute le port d'écoute du serveur UDP
	        \return Cette méthode renvoie true si la socket serveur est bien ouverte, false sinon.
	        \sa FermerLaSocket()
	    */
        bool OuvrirLaSocketDEcoute(unsigned short portDEcoute, std::string adresseIPDEcoute = "0.0.0.0");

        //! Méthode permettant d'envoyer un message de type texte.
	    /*!
         *   @brief Méthode permettant d'envoyer un message au serveur UDP.
         *   @param message le message à envoyer
	     *   @return Cette méthode renvoie true si le message a été correctement émis, false sinon.
	     *   @sa EnvoyerDesOctets(const char * tableau, int taille)
	     */        
        bool EnvoyerUnMessage(std::string message);

        //! Méthode permettant d'envoyer un tableau d'octets.
	    /*!
         *   @brief Méthode permettant d'envoyer un tableau d'octets au serveur UDP.
         *   @param message le tableau d'octets à envoyer
         *   @param taille la taille du tableau d'octets à envoyer
	     *   @return Cette méthode renvoie true si le message a été correctement émis, false sinon.
	     *   @sa EnvoyerUnMessage(std::string message)
	     */     
        bool EnvoyerDesOctets(const unsigned char * tableau, int taille);

        //! Méthode permettant de recevoir un message de type texte.
	    /*!
         *   @brief Méthode permettant de recevoir un message provenant du serveur UDP.
         *   @param message une référence au message qui contiendra le message à recevoir 
	     *   @return Cette méthode renvoie le nombre d'octets reçus. En cas d'échec, cette méthode renvoie 0 ou une valeur négative.
	     *   @sa RecevoirDesOctets(char * tableau, int tailleMax)
	     */     
        int RecevoirUnMessage(std::string & message);
        
        //! Méthode permettant de recevoir un tableau d'octet.
	    /*!
         *   @brief Méthode permettant de recevoir un tableau d'octets provenant du serveur UDP.
         *   @param tableau le tableau d'octet qui contiendra les données à recevoir
         *   @param tailleMax le nombre d'octets maximum que peut contenir le tableau d'octet
	     *   @return Cette méthode renvoie le nombre d'octets reçus. En cas d'échec, cette méthode renvoie 0 ou une valeur négative.
	     *   @sa RecevoirDesOctets(char * tableau, int tailleMax)
	     */     
        int RecevoirDesOctets(unsigned char * tableau, int tailleMax);

        //! Méthode permettant de fermer la socket cliente UDP.
	    /*!
	        \return Cette méthode renvoie true si la socket de communication est bien fermée, false sinon.
	        \sa OuvrirLaSocket(std::string adresseIPServeur, unsigned short portServeur)
	    */


       
        bool FermerLaSocket();
};

#endif