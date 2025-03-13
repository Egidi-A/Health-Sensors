#ifndef MODELLO_H
#define MODELLO_H
#include <string>
#include "SensoriCollection.h"
#include "BPM.h"
#include "Ossigenazione.h"
#include "Temperatura.h"
#include <stdexcept>

class Modello
{
private:
    SensoriCollection* collezioneSensori;
    Sensore* creaSensore(const std::string& type);
public:
    Modello();
    ~Modello();
    void aggiungiSensore(const std::string& type);
    void rimuoviSensore(int id);
    Sensore* getSensore(int id) const;
    std::vector<Sensore *> getSensori() const;
    SensoriCollection* getCollezioneSensori_modello() const;


    void setSensoreNome_modello(int id, std::string);
    void setSimulazione_modello(int id);
    void setCollezioneSensori_modello(SensoriCollection* collection);
};

#endif // MODELLO_H
