#include "filehandler.h"
#include"./MODELLO/BPM.h"
#include"./MODELLO/Ossigenazione.h"
#include"./MODELLO/Temperatura.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void FileHandler::salvaDati(const SensoriCollection* collezione, const std::string& percorsoFile){
    std::ofstream file(percorsoFile);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file per la scrittura: " << percorsoFile << std::endl;
        return;
    }

    for (const auto& sensore : collezione->getSensori()) {

        BPM* sensoreBPM = dynamic_cast<BPM*>(sensore);
        if(sensoreBPM!=nullptr){
            file <<"BPM";
        }
        Ossigenazione* sensoreOssigenazione = dynamic_cast<Ossigenazione*>(sensore);
        if (sensoreOssigenazione != nullptr) {
            file <<"Ossigenazione";
        }
        Temperatura* sensoreTemperatura = dynamic_cast<Temperatura*>(sensore);
        if (sensoreTemperatura != nullptr) {
            file <<"Temperatura";
        }

        file << "," << sensore->getSensoreID();
        file << "," << sensore->getValidMin();
        file << "," << sensore->getValidMax();
        file << "," << sensore->getFrequenzaMisurazione();
        file << "," << sensore->getSensoreNome();
        if(sensoreBPM!=nullptr){
            file << "," << sensoreBPM->getSportMin();
            file << ","<< sensoreBPM->getSportMax();
        }
        if (sensoreOssigenazione != nullptr) file << "," << sensoreOssigenazione->getAlertMin();

        for(auto misurazione : sensore->getMisurazioni())
            file << "," << misurazione;
        file << std::endl;
    }
    file.close();
}

SensoriCollection* FileHandler::caricaDati(const std::string& percorsoFile) {
    SensoriCollection* collezione = new SensoriCollection();
    std::ifstream file(percorsoFile);

    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file per la lettura: " << percorsoFile << std::endl;
        return collezione;
    }

    std::string riga;

    while (std::getline(file, riga)) {
        std::stringstream ss(riga);
        std::string tipo, id, nome;
        int valMin, valMax, frequenza, sportMin = 0, sportMax = 0, alertMin = 0;
        std::vector<int> misurazioni;

        std::getline(ss, tipo, ',');
        std::getline(ss, id, ',');
        ss >> valMin; ss.ignore();
        ss >> valMax; ss.ignore();
        ss >> frequenza; ss.ignore();
        std::getline(ss, nome, ',');

        if (tipo == "BPM") {
            ss >> sportMin; ss.ignore();
            ss >> sportMax; ss.ignore();
        } else if (tipo == "Ossigenazione") {
            ss >> alertMin; ss.ignore();
        }

        std::string misuraStr;
        while (std::getline(ss, misuraStr, ',')) {
            if (!misuraStr.empty()) {
                int misura = std::stoi(misuraStr);
                misurazioni.push_back(misura);
            }
        }

        int idInt = std::stoi(id);
        Sensore* nuovoSensore = nullptr;
        if (tipo == "BPM") {
            nuovoSensore = new BPM(idInt, nome, frequenza, sportMin, sportMax, valMin, valMax);
        } else if (tipo == "Ossigenazione") {
            nuovoSensore = new Ossigenazione(idInt, nome, frequenza, alertMin, valMin, valMax);
        } else if (tipo == "Temperatura") {
            nuovoSensore = new Temperatura(idInt, nome, frequenza, valMin, valMax);
        }

        if (nuovoSensore != nullptr) {
            collezione->addSensore(nuovoSensore);
            nuovoSensore->setMisurazioni(misurazioni);
        }
    }

    return collezione;
}

