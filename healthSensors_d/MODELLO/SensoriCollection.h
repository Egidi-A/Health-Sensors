#ifndef SENSORICOLLECTION_H
#define SENSORICOLLECTION_H

#include "Sensore.h"
#include <vector>
#include <string>

// Dichiarazione della classe SensoriCollection
class SensoriCollection {
private:
    // Vettore di puntatori a oggetti Sensore, sostituisce std::list<Training*> per la gestione dei sensori
    std::vector<Sensore *> sensori;
    static std::vector<Sensore *> copy(const SensoriCollection &copy_collection);

public:
    // Costruttore di default
    SensoriCollection();
    // Costruttore di copia
    SensoriCollection(const SensoriCollection& other);
    // Distruttore
    ~SensoriCollection();

    // Metodo per aggiungere un sensore alla collezione
    void addSensore(Sensore* sensore);
    // Metodo per rimuovere un sensore dalla collezione
    void removeSensore(int ID_sensore);
    // Metodo per settare il nome di un sensore
    void setSensoreNome(int id, std::string nome);
    // Metodo per creare una nuova simulazione del sensore scelto
    void setSimulazione_collection(int id);
    // Metodo per trovare un sensore tramite ID, restituisce il puntatore al sensore se trovato, altrimenti nullptr
    Sensore* findSensoreById(int id) const;
    // Metodo per ottenere tutti i sensori nella collezione, restituisce un vettore di puntatori a Sensore
    std::vector<Sensore*> getSensori() const;

    // Operatore di assegnazione
    SensoriCollection& operator=(const SensoriCollection& other);
};

#endif // SENSORICOLLECTION_H
