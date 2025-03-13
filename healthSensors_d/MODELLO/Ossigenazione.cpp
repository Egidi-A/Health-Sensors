#include "Ossigenazione.h"
#include <cstdlib>
#include <ctime>

Ossigenazione::Ossigenazione(int id, 
                            std::string nome, 
                            int frequenza, 
                            int alertMin, 
                            int validMin, 
                            int validMax)
    : Sensore(id, validMin, validMax, frequenza, nome), alertMin(alertMin) {
    // Corpo vuoto
}

Ossigenazione::~Ossigenazione(){}

void Ossigenazione::daySimulazione() {

    // Inizializza il generatore di numeri casuali
    //srand(static_cast<unsigned int>(time(nullptr)));
    eraseMisurazioni();
    // Calcola il numero totale di misurazioni per un giorno
    int misurazioniPerGiorno = (24 * 60) / getFrequenzaMisurazione();

    // Calcola il numero di misurazioni che devono essere > 90 (il 92% delle misurazioni totali)
    int misurazioniSopra90 = static_cast<int>(misurazioniPerGiorno * 0.95);

    for (int i = 0; i < misurazioniPerGiorno; ++i) {
        int valoreCasuale;

        if (i < misurazioniSopra90) {
            // Genera valori casuali sopra 90 per la maggior parte delle misurazioni
            valoreCasuale = 91 + rand() % 10; // Genera valori nell'intervallo [91, 100]
        } else {
            // Genera valori casuali per il restante 8% delle misurazioni
            valoreCasuale = rand() % 101; // Genera valori nell'intervallo [0, 90]
        }

        // Aggiunge il valore casuale al vettore di misurazioni
        addMisurazione(valoreCasuale);
    }
}

int Ossigenazione::dayLifeQuality() const {
    if (getMisurazioni().empty()) {
        return 100; // Se non ci sono misurazioni, assume qualità della vita massima
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
    int qualitaDellaVita = 100 - static_cast<int>(1.5 * percentualeFuoriRange);

    return qualitaDellaVita;
}

bool Ossigenazione::segnalazione() const {
    for (int misurazione : getMisurazioni()) {
        if (misurazione < getAlertMin()) {
            return true; // Trovata una misurazione critica, restituisce true
        }
    }
    return false; // Nessuna misurazione critica trovata, restituisce false
}

Ossigenazione* Ossigenazione::clone(int nuovoID) const{ 
    Ossigenazione* aux = new Ossigenazione(*this);
    aux->setSensoreID(nuovoID);
    return aux;
}

int Ossigenazione::getAlertMin() const {
    return alertMin;
}
