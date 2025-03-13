#include "Sensore.h"

// Costruttore
Sensore::Sensore(int id, 
                int min, 
                int max, 
                int frequenza, 
                std::string nome)
    : sensoreID(id), validMin(min), validMax(max), frequenzaMisurazione(frequenza), sensoreNome(nome) {
}

// Distruttore
Sensore::~Sensore() {}

// Setter methods
void Sensore::setSensoreID(int id) {
    sensoreID = id;
}

void Sensore::setValidMin(int min) {
    validMin = min;
}

void Sensore::setValidMax(int max) {
    validMax = max;
}

void Sensore::setFrequenzaMisurazione(int frequenza) {
    frequenzaMisurazione = frequenza;
}

void Sensore::setSensoreNome(std::string nome) {
    sensoreNome = nome;
}

void Sensore::setMisurazioni(std::vector<int> misurazioniSensore) {
    misurazioni = misurazioniSensore;
}

void Sensore::addMisurazione(int misurazione) {
    misurazioni.push_back(misurazione);
}

int Sensore::getSensoreID() const {
    return sensoreID;
}

int Sensore::getValidMin() const {
    return validMin;
}

int Sensore::getValidMax() const {
    return validMax;
}

int Sensore::getFrequenzaMisurazione() const {
    return frequenzaMisurazione;
}

std::string Sensore::getSensoreNome() const {
    return sensoreNome;
}

std::vector<int> Sensore::getMisurazioni() const {
    return misurazioni;
}

void Sensore::eraseMisurazioni() {
    misurazioni.clear();
}





