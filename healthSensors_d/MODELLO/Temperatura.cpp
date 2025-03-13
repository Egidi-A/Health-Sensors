#include "Temperatura.h"
#include <cstdlib>
#include <ctime>

Temperatura::Temperatura(int id, 
                std::string nome, 
                int frequenza, 
                int validMin, 
                int validMax)
    : Sensore(id, validMin, validMax, frequenza, nome) {}

Temperatura::~Temperatura(){}

void Temperatura::daySimulazione() {
    eraseMisurazioni();
    // Calcola il numero totale di misurazioni per un giorno
    int misurazioniPerGiorno = (24 * 60) / getFrequenzaMisurazione();

    // Calcola il numero di misurazioni che devono essere nel range [97, 100] (il 70% delle misurazioni totali)
    int misurazioniNelRange = static_cast<int>(misurazioniPerGiorno * 0.70);

    for (int i = 0; i < misurazioniPerGiorno; ++i) {
        int valoreCasuale;

        if (i < misurazioniNelRange) {
            // Per il 90% delle misurazioni, genera valori casuali tra 97 e 100
            valoreCasuale = 97 + rand() % (100 - 97 + 1);
        } else {
            // Per il restante 10% delle misurazioni, genera valori casuali tra 96 e 103
            valoreCasuale = 96 + rand() % (103 - 96 + 1);
        }

        // Aggiunge il valore casuale al vettore di misurazioni
        addMisurazione(valoreCasuale);
    }
}

int Temperatura::dayLifeQuality() const {
    if (getMisurazioni().empty()) {
        return 100; // Massima qualità della vita se non ci sono misurazioni
    }

    int conteggioFuoriRange = 0;
    for (int misurazione : getMisurazioni()) {
        if (misurazione < getValidMin() || misurazione > getValidMax()) {
            ++conteggioFuoriRange; // Conta le misurazioni fuori dall'intervallo valido
        }
    }

    // Calcola la percentuale di valori fuori range rispetto al totale delle misurazioni
    double percentualeFuoriRange = static_cast<double>(conteggioFuoriRange) / getMisurazioni().size() * 100;

    // Applica la formula specificata per la qualità della vita
    int qualitaDellaVita = 100 - static_cast<int>(0.3 * percentualeFuoriRange);

    return qualitaDellaVita;
}

Temperatura* Temperatura::clone(int nuovoID) const{
    Temperatura* aux = new Temperatura(*this);
    aux->setSensoreID(nuovoID);
    return aux;
}

bool Temperatura::febbre() const {
    std::vector<int> misure = getMisurazioni(); // Ottiene una copia del vettore delle misurazioni

    if (misure.size() < 2) {
        return false; // Non ci sono abbastanza misurazioni per determinare la febbre
    }

    for (size_t i = 0; i < misure.size() - 1; ++i) {
        if (misure[i] >= 100 && misure[i + 1] >= 100) {
            return true; // Trovati due valori consecutivi >= 100
        }
    }

    return false; // Nessuna coppia di valori consecutivi >= 100 trovata
}
