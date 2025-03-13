#include "dashboarddettagliwidget.h"

dashboardDettagliWidget::dashboardDettagliWidget(Modello* model, int idSensore, QWidget *parent)
    : QWidget{parent}
{
    modello = model;
    labelDetails->setStyleSheet("QLabel { color : red; font-weight : bold; }");
    dashDetailsLayout->addWidget(labelDetails);
    labelDetails->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    if(idSensore!=-1){
        QString idSensoreDetails = QString::number(modello->getSensore(idSensore)->getSensoreID());
        idLabel->setText(idSensoreDetails);
    }
    detailsIDLayout->addWidget(idDetails);
    detailsIDLayout->addWidget(idLabel);
    dashDetailsLayout->addLayout(detailsIDLayout);

    if(idSensore!=-1){
        QString nomeSensoreDetails = QString::fromStdString(modello->getSensore(idSensore)->getSensoreNome());
        nomeLabel->setText(nomeSensoreDetails);
    }
    detailsNomeLayout->addWidget(nomeDetails);
    detailsNomeLayout->addWidget(nomeLabel);
    dashDetailsLayout->addLayout(detailsNomeLayout);

    if(idSensore!=-1){
        QString VMinSensoreDetails = QString::number(modello->getSensore(idSensore)->getValidMin());
        VMinLabel->setText(VMinSensoreDetails);
    }
    detailsVMinLayout->addWidget(VMinDetails);
    detailsVMinLayout->addWidget(VMinLabel);
    dashDetailsLayout->addLayout(detailsVMinLayout);

    if(idSensore!=-1){
        QString VMaxSensoreDetails = QString::number(modello->getSensore(idSensore)->getValidMax());
        VMaxLabel->setText(VMaxSensoreDetails);
    }
    detailsVMaxLayout->addWidget(VMaxDetails);
    detailsVMaxLayout->addWidget(VMaxLabel);
    dashDetailsLayout->addLayout(detailsVMaxLayout);

    if(idSensore!=-1){
        QString FrequenzaSensoreDetails = "ogni "+QString::number(modello->getSensore(idSensore)->getFrequenzaMisurazione())+" minuti";
        FrequenzaLabel->setText(FrequenzaSensoreDetails);
    }
    detailsFrequenzaLayout->addWidget(FrequenzaDetails);
    detailsFrequenzaLayout->addWidget(FrequenzaLabel);
    dashDetailsLayout->addLayout(detailsFrequenzaLayout);

    detailsSportMinLayout->addWidget(sportMinDetails);
    detailsSportMinLayout->addWidget(SportMinLabel);
    detailsSportMaxLayout->addWidget(sportMaxDetails);
    detailsSportMaxLayout->addWidget(SportMaxLabel);
    detailsAlertMinLayout->addWidget(alertDetails);
    detailsAlertMinLayout->addWidget(alertLabel);
    dashDetailsLayout->addLayout(detailsSportMinLayout);
    dashDetailsLayout->addLayout(detailsSportMaxLayout);
    dashDetailsLayout->addLayout(detailsAlertMinLayout);

    if(idSensore!=-1){
        BPM* sensoreBPMDetails = dynamic_cast<BPM*>(modello->getSensore(idSensore));
        if (sensoreBPMDetails != nullptr) {
            QString sportMinSensoreDetails = QString::number(sensoreBPMDetails->getSportMin());
            SportMinLabel->setText(sportMinSensoreDetails);
            QString sportMaxSensoreDetails = QString::number(sensoreBPMDetails->getSportMax());
            SportMaxLabel->setText(sportMaxSensoreDetails);
            alertDetails->hide();
            alertLabel->hide();
            sportMaxDetails->show();
            SportMaxLabel->show();
            sportMinDetails->show();
            SportMinLabel->show();
        }

        Ossigenazione* sensoreOssigenazioneDetails = dynamic_cast<Ossigenazione*>(modello->getSensore(idSensore));
        if (sensoreOssigenazioneDetails != nullptr) {
            QString alertSensoreDetails = QString::number(sensoreOssigenazioneDetails->getAlertMin());
            alertLabel->setText(alertSensoreDetails);
            sportMaxDetails->hide();
            SportMaxLabel->hide();
            sportMinDetails->hide();
            SportMinLabel->hide();
            alertDetails->show();
            alertLabel->show();
        }
        Temperatura* sensoreTemperaturaDetails = dynamic_cast<Temperatura*>(modello->getSensore(idSensore));
        if (sensoreTemperaturaDetails != nullptr) {
            sportMaxDetails->hide();
            SportMaxLabel->hide();
            sportMinDetails->hide();
            SportMinLabel->hide();
            alertDetails->hide();
            alertLabel->hide();
        }
    }

    dashDetailsLayout->addWidget(modificaNomeButton);

    dashDetailsLayout->addStretch(1);

    setLayout(dashDetailsLayout);
}

QString dashboardDettagliWidget::showEditNameDialog()
{
    bool ok = false;
    QString nomeString = QInputDialog::getText(this, tr("Modifica Nome Sensore"), tr("Imposta il nome del tuo sensore esistente:"), QLineEdit::Normal, tr("Nuovo nome sensore"), &ok);
    if(!ok) throw std::runtime_error("Operazione di Modifica Nome annullata");
    return nomeString;
}

void dashboardDettagliWidget::setNameLabel(QString nome)
{
    nomeLabel->setText(nome);
}

void dashboardDettagliWidget::refreshDettagli(int idSensore)
{
    if(idSensore!=-1){
    idLabel->setText(QString::number(modello->getSensore(idSensore)->getSensoreID()));
    nomeLabel->setText(QString::fromStdString(modello->getSensore(idSensore)->getSensoreNome()));
    VMinLabel->setText(QString::number(modello->getSensore(idSensore)->getValidMin()));
    VMaxLabel->setText(QString::number(modello->getSensore(idSensore)->getValidMax()));
    FrequenzaLabel->setText(QString::number(modello->getSensore(idSensore)->getFrequenzaMisurazione()));
    BPM* sensoreBPMDetails = dynamic_cast<BPM*>(modello->getSensore(idSensore));
    if (sensoreBPMDetails != nullptr) {SportMinLabel->setText(QString::number(sensoreBPMDetails->getSportMin()));}
    }

}

dashboardDettagliWidget::~dashboardDettagliWidget(){
    delete modello;
}
