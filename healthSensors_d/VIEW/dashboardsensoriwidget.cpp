#include "dashboardsensoriwidget.h"

dashBoardSensoriWidget::dashBoardSensoriWidget(QWidget *parent)
    : QWidget{parent}
{
    labelSensori->setStyleSheet("QLabel { color : red; font-weight : bold; }");
    dashSensoriLayout->addWidget(labelSensori);
    labelSensori->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    // bottoni aggiunta e rimozione sensori
    addSensoreBPMButton = new QPushButton("Aggiungi Sensore BPM");
    addSensoreOssigenazioneButton = new QPushButton("Aggiungi Sensore Ossigenazione");
    addSensoreTemperaturaButton = new QPushButton("Aggiungi Sensore Temperatura");
    removeSensoreButton = new QPushButton("Rimuovi Sensore");
    dashSensoriLayout->addWidget(addSensoreBPMButton);
    dashSensoriLayout->addWidget(addSensoreOssigenazioneButton);
    dashSensoriLayout->addWidget(addSensoreTemperaturaButton);
    dashSensoriLayout->addWidget(removeSensoreButton);

    dashSensoriLayout->addWidget(listaSensori);

    //aggiunta search bar
    searchBar->setPlaceholderText("Cerca il sensore per id...");
    dashSensoriLayout->addWidget(searchBar);

    setLayout(dashSensoriLayout);
}

int dashBoardSensoriWidget::showRemoveDialog()
{
    bool ok = false;
    int idInt = QInputDialog::getInt(this, tr("Rimozione Sensore"), tr("Inserisci l'id del sensore che vuoi rimuovere:"), 0, 0, 2147483647, 1, &ok);
    if(!ok) throw std::runtime_error("Operazione di Rimozione Sensore annullata");
    return idInt;
}

QString dashBoardSensoriWidget::showAddBPMDialog()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Aggiunta Sensore BPM", "Vuoi procedere con la creazione e aggiunta di un sensore BPM?", QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        return "BPM";
    } else {
        throw std::runtime_error("Operazione di creazione e aggiunta sensore BPM annullata");
    }
}

QString dashBoardSensoriWidget::showAddOssigenazioneDialog()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Aggiunta Sensore Ossigenazione", "Vuoi procedere con la creazione e aggiunta di un sensore Ossigenazione?", QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        return "Ossigenazione";
    } else {
        throw std::runtime_error("Operazione di creazione e aggiunta sensore Ossigenazione annullata");
    }
}

QString dashBoardSensoriWidget::showAddTemperaturaDialog()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Aggiunta Sensore Temperatura", "Vuoi procedere con la creazione e aggiunta di un sensore Temperatura?", QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        return "Temperatura";
    } else {
        throw std::runtime_error("Operazione di creazione e aggiunta sensore Temperatura annullata");
    }
}

void dashBoardSensoriWidget::updateListaWidget(std::vector<QString> newWidgets)
{    
    listaSensori->clear();
    for(auto widget : newWidgets){
        listaSensori->addItem(widget);
    }
}


