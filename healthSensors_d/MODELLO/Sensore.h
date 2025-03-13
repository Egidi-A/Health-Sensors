#ifndef SENSORE_H
#define SENSORE_H

#include <vector>
#include <string>

class Sensore {
private:
    int sensoreID;
    int validMin;
    int validMax;
    int frequenzaMisurazione;
    std::vector<int> misurazioni;
    std::string sensoreNome;

public:
    Sensore(int id, 
            int min, 
            int max, 
            int frequenza = 1,
            std::string nome = "Generic Sensor");
    virtual ~Sensore();
    
    virtual void daySimulazione() = 0;
    virtual int dayLifeQuality() const = 0;
    virtual Sensore* clone(int nuovoID) const = 0;

    void setSensoreID(int id);
    void setValidMin(int min);
    void setValidMax(int max);
    void setFrequenzaMisurazione(int frequenza);
    void setSensoreNome(std::string nome);
    void setMisurazioni(std::vector<int> misurazioniSensore);
    void addMisurazione(int misurazione);

    int getSensoreID() const;
    int getValidMin() const;
    int getValidMax() const;
    int getFrequenzaMisurazione() const;
    std::string getSensoreNome() const;
    std::vector<int> getMisurazioni() const;
    void eraseMisurazioni();

};

#endif // SENSORE_H
