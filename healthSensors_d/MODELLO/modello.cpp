#include "modello.h"

Modello::Modello():collezioneSensori(new SensoriCollection()) {}
Modello::~Modello(){
    delete collezioneSensori;
}


Sensore* Modello::creaSensore(const std::string& type){
    int id = -1;
    int size = collezioneSensori->getSensori().size();

    if(size > 0) {
        Sensore* sensore = collezioneSensori->getSensori().at(size-1);
        if(collezioneSensori->getSensori().size()) id = sensore->getSensoreID();
    }

    if(type=="BPM") return new BPM(id+1);
    if(type=="Ossigenazione") return new Ossigenazione(id+1);
    if(type=="Temperatura") return new Temperatura(id+1);
    throw std::invalid_argument("Il sensore non esiste");
}

void Modello::aggiungiSensore(const std::string& type){
    collezioneSensori->addSensore(creaSensore(type));
}

void Modello::rimuoviSensore(int id){
    collezioneSensori->removeSensore(id);
}

Sensore* Modello::getSensore(int id) const{
    return collezioneSensori->findSensoreById(id);
}

std::vector<Sensore *> Modello::getSensori() const{
    return collezioneSensori->getSensori();
}

SensoriCollection* Modello::getCollezioneSensori_modello() const
{
    return collezioneSensori;
}

void Modello::setSensoreNome_modello(int id, std::string nome){
    collezioneSensori->setSensoreNome(id, nome);
}

void Modello::setSimulazione_modello(int id)
{
    collezioneSensori->setSimulazione_collection(id);

}

void Modello::setCollezioneSensori_modello(SensoriCollection *collection){
    collezioneSensori = collection;
}
