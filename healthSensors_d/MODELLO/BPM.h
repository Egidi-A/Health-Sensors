#ifndef BPM_H
#define BPM_H

#include "Sensore.h"
#include<string>

class BPM : public Sensore {
private:
    int sportMin;
    int sportMax;

public:
    BPM(int id, 
        std::string nome = "Heart Rate Sensor", 
        int frequenza = 10, 
        int sportMin = 101, 
        int sportMax = 180, 
        int validMin = 45, 
        int validMax = 100);
    ~BPM();
    
    void daySimulazione() override;
    int dayLifeQuality() const override;
    BPM* clone(int nuovoID) const override;
    int sportAvg() const;

    // Metodi getter per BPM
    int getSportMin() const;
    int getSportMax() const;
};

#endif // BPM_H
