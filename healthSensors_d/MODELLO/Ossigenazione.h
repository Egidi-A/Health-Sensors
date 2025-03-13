#ifndef OSSIGENAZIONE_H
#define OSSIGENAZIONE_H

#include "Sensore.h"
#include<string>

class Ossigenazione : public Sensore {
private:
    int alertMin;

public:
    Ossigenazione(int id,
                std::string nome = "Blood Oxygen Sensor", 
                int frequenza = 30, 
                int alertMin = 90, 
                int validMin = 95, 
                int validMax = 100);
    ~Ossigenazione();

    void daySimulazione() override;
    int dayLifeQuality() const override;
    bool segnalazione() const;
    Ossigenazione* clone(int nuovoID) const override;
    int getAlertMin() const;
};

#endif // OSSIGENAZIONE_H
