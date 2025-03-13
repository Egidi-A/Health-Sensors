#include "SensoriCollection.h"
#include <stdexcept>
#include <algorithm>


// Implementazione del costruttore di default
SensoriCollection::SensoriCollection() {}

// Implementazione della clone
std::vector<Sensore *> SensoriCollection::copy(const SensoriCollection &copy_collection)
{
    std::vector<Sensore *> aux;
    int numSensori = copy_collection.getSensori().size();
    for (auto it = copy_collection.sensori.begin(); it != copy_collection.sensori.end(); ++it){
        numSensori++;
        aux.push_back((*it)->clone(numSensori));
    }
    return aux;
}

// Implementazione del distruttore
SensoriCollection::~SensoriCollection() {
    // Elimina tutti i sensori allocati dinamicamente nella collezione
    for (auto& sensore : sensori) {
        delete sensore;
    }
    sensori.clear();
}

// Implementazione della copia profonda
SensoriCollection::SensoriCollection(const SensoriCollection &collezione) : sensori(copy(collezione)) {}

// Metodo per aggiungere un sensore alla collezione
void SensoriCollection::addSensore(Sensore* sensore) {
    sensori.push_back(sensore);
}

// Metodo per rimuovere un sensore dalla collezione
void SensoriCollection::removeSensore(int ID_sensore) {
    // Trova il sensore nella collezione
    auto it = std::find(sensori.begin(), sensori.end(), findSensoreById(ID_sensore));
    delete *it;
    sensori.erase(it);
}

// Metodo per settare il nome di un sensore
void SensoriCollection::setSensoreNome(int id, std::string nome){
        Sensore* aux = findSensoreById(id);
    aux->setSensoreNome(nome);
}

void SensoriCollection::setSimulazione_collection(int id)
{
    Sensore* aux = findSensoreById(id);
    aux->daySimulazione();
}


// Metodo per trovare un sensore tramite ID
Sensore* SensoriCollection::findSensoreById(int id) const {
    for (auto& sensore : sensori) {
        if (sensore->getSensoreID() == id) {
            return sensore;
        }
    }
    throw std::invalid_argument("Il sensore non esiste");
}

// Metodo per ottenere tutti i sensori nella collezione
std::vector<Sensore*> SensoriCollection::getSensori() const {
    return sensori;
}

// Implementazione dell'operatore di assegnazione
SensoriCollection& SensoriCollection::operator=(const SensoriCollection& other) {
    if (this != &other) {
        // Pulisce la collezione corrente
        for (auto& sensore : sensori) {
            delete sensore;
        }
        sensori.clear();
        // Copia i sensori dall'altra collezione
        sensori = copy(other);
    }
    return *this;
}
