#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include "Sensore.h"
#include<string>

class Temperatura : public Sensore {
public:
    Temperatura(int id, 
                std::string nome = "Body Temperature Sensor", 
                int frequenza = 60,
                int validMin = 97, 
                int validMax = 100);
    ~Temperatura();

    void daySimulazione() override;
    int dayLifeQuality() const override;
    Temperatura* clone(int nuovoID) const override;
    bool febbre() const;
};

#endif // TEMPERATURA_H