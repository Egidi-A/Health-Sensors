#include <cstdlib> // Per rand(), srand()
#include <ctime>   // Per time()
#include "BPM.h"

BPM::BPM(int id, 
         std::string nome, 
         int frequenza, 
         int sportMin, 
         int sportMax, 
         int validMin, 
         int validMax)
    : Sensore(id, validMin, validMax, frequenza, nome), sportMin(sportMin), sportMax(sportMax) {}

BPM::~BPM(){}

void BPM::daySimulazione() {

    eraseMisurazioni();
    // Calcola il numero totale di misurazioni per un giorno
    int misurazioniPerGiorno = (24 * 60) / getFrequenzaMisurazione(); // 1440 minuti in un giorno

    if (misurazioniPerGiorno <= 0) return;

    // Genera il primo valore casuale tra 40 e 180
    int valorePrecedente = 40 + rand() % (180 - 40 + 1);
    addMisurazione(valorePrecedente);

    for (int i = 1; i < misurazioniPerGiorno; ++i) {
        // Calcola i limiti per il nuovo valore, assicurandosi che rimangano nell'intervallo [40, 180]
        int minVal = std::max(40, valorePrecedente - 20);
        int maxVal = std::min(180, valorePrecedente + 20);

        int valoreCasuale = minVal + rand() % (maxVal - minVal + 1);

        addMisurazione(valoreCasuale);

        // Aggiorna il valore precedente per il prossimo ciclo
        valorePrecedente = valoreCasuale;
    }
}

int BPM::dayLifeQuality() const{
    if (getMisurazioni().empty()) {
        return 100;
    }

    int conteggioFuoriRange = 0;
    for (int misurazione : getMisurazioni()) {
        if (misurazione < getValidMin() || misurazione > getValidMax()) {
            ++conteggioFuoriRange;
        }
    }

    // Calcola la percentuale di valori fuori range rispetto al totale delle misurazioni
    double percentualeFuoriRange = static_cast<double>(conteggioFuoriRange) / getMisurazioni().size() * 100;

    // Calcola la qualità della vita come 100 meno la percentuale di valori fuori range
    int qualitaDellaVita = 100 - static_cast<int>(percentualeFuoriRange);

    return qualitaDellaVita;
}

BPM* BPM::clone(int nuovoID) const{ 
    BPM* aux = new BPM(*this);
    aux->setSensoreID(nuovoID);
    return aux;
}

int BPM::sportAvg() const {
    if (getMisurazioni().empty()) {
        return 0; // Ritorna 0 se non ci sono misurazioni
    }

    int somma = 0;
    int conteggio = 0;
    for (int misurazione : getMisurazioni()) {
        if (misurazione >= getSportMin() && misurazione <= getSportMax()) {
            somma += misurazione;
            ++conteggio;
        }
    }

    if (conteggio == 0) {
        return 0; // Nessuna misurazione nel range specificato
    }

    // Calcola la media e arrotonda al valore intero più vicino
    // Oppure tronca semplicemente il risultato convertendolo in int
    return somma / conteggio;
}

int BPM::getSportMin() const {
    return sportMin;
}

int BPM::getSportMax() const {
    return sportMax;
}
