#include "dashboardsimulazionewidget.h"

dashboardSimulazioneWidget::dashboardSimulazioneWidget(Modello* model, int idSensore, QWidget *parent)
    : QWidget{parent}
{
    modello = model;
    labelSimulazione->setStyleSheet("QLabel { color : red; font-weight : bold; }");
    dashSimulazioneLayout->addWidget(labelSimulazione);
    labelSimulazione->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    //label per il dayquality

    if(idSensore!=-1){
        QString dayQualityValue = QString::number(modello->getSensore(idSensore)->dayLifeQuality())+"%";
        valueLabel->setText(dayQualityValue);
    }
    qualityLayout->addWidget(qualityLabel);
    qualityLayout->addWidget(valueLabel);
    dashSimulazioneLayout->addLayout(qualityLayout);

    funzioneBPMLayout->addWidget(sportAvgLabel);
    funzioneBPMLayout->addWidget(valueSportLabel);
    dashSimulazioneLayout->addLayout(funzioneBPMLayout);
    funzioneOssigenazioneLayout->addWidget(ossigenazioneLabel);
    funzioneOssigenazioneLayout->addWidget(criticitaLabel);
    dashSimulazioneLayout->addLayout(funzioneOssigenazioneLayout);
    funzioneTemperaturaLayout->addWidget(temperaturaLabel);
    funzioneTemperaturaLayout->addWidget(febbreLabel);
    dashSimulazioneLayout->addLayout(funzioneTemperaturaLayout);

    //funzioni specifiche
    if(idSensore!=-1){
        BPM* sensoreBPM = dynamic_cast<BPM*>(modello->getSensore(idSensore));
        if (sensoreBPM != nullptr) {
            QString sportAvgValue = QString::number(sensoreBPM->sportAvg());
            valueSportLabel->setText(sportAvgValue);
            frameGrafico->show();
            sportAvgLabel->show();
            valueSportLabel->show();
            ossigenazioneLabel->hide();
            criticitaLabel->hide();
            temperaturaLabel->hide();
            febbreLabel->hide();
        }
        Ossigenazione* sensoreOssigenazione = dynamic_cast<Ossigenazione*>(modello->getSensore(idSensore));
        if (sensoreOssigenazione != nullptr) {
            if(sensoreOssigenazione->segnalazione()) criticitaLabel->setText("Si") ;
            else criticitaLabel->setText("No");
            frameGrafico->show();
            sportAvgLabel->hide();
            valueSportLabel->hide();
            ossigenazioneLabel->hide();
            criticitaLabel->show();
            temperaturaLabel->show();
            febbreLabel->hide();
        }
        Temperatura* sensoreTemperatura = dynamic_cast<Temperatura*>(modello->getSensore(idSensore));
        if (sensoreTemperatura != nullptr) {
            if(sensoreTemperatura->febbre()) febbreLabel->setText("Si") ;
            else febbreLabel->setText("No");
            frameGrafico->show();
            sportAvgLabel->hide();
            valueSportLabel->hide();
            ossigenazioneLabel->hide();
            criticitaLabel->hide();
            temperaturaLabel->hide();
            febbreLabel->show();
        }
    }

    //char dei dati
    frameGrafico->setLayout(layoutGrafico);
    dashSimulazioneLayout->addWidget(frameGrafico);

    if(idSensore!=-1){
        int index=0;
        for (const auto& dato : modello->getSensore(idSensore)->getMisurazioni()) { //bisogna che rispecchi il sensore cliccato nella lista
            serieDati->append(index, dato);
            ++index;
        }
    }

    chartDati->legend()->hide();
    chartDati->addSeries(serieDati);
    chartDati->createDefaultAxes();
    chartDati->setTitle("Visualizzazione Dati Simulazione");
    chartView->setRenderHint(QPainter::Antialiasing);
    layoutGrafico->addWidget(chartView);

    //bottoni del chart
    bottoniSimulazioneLayout->addWidget(caricaSimulazione);
    bottoniSimulazioneLayout->addWidget(salvaSimulazione);

    dashSimulazioneLayout->addLayout(bottoniSimulazioneLayout);
    dashSimulazioneLayout->addWidget(nuovaSimulazione);

    setLayout(dashSimulazioneLayout);
}

QString dashboardSimulazioneWidget::showLoadFileDialog(){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Apri il file"), QDir::currentPath(), tr("Testo (*.txt)"));
        if(fileName.isEmpty()) throw std::runtime_error("Nessun file scelto in Load Mode: operazione annullata");
        return fileName;
}

QString dashboardSimulazioneWidget::showSaveFileDialog() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva il file"), QDir::currentPath(), tr("Testo (*.txt)"));
    if(fileName.isEmpty()) throw std::runtime_error("Nessun file scelto in Save Mode: operazione annullata");
    return fileName;
}

void dashboardSimulazioneWidget::refreshSimulazione(int idSensore){

    valueLabel->setText(QString::number(modello->getSensore(idSensore)->dayLifeQuality()));

    BPM* sensoreBPM = dynamic_cast<BPM*>(modello->getSensore(idSensore));
    if (sensoreBPM != nullptr) {
        QString sportAvgValue = QString::number(sensoreBPM->sportAvg());
        valueSportLabel->setText(sportAvgValue);

        frameGrafico->show();
        sportAvgLabel->show();
        valueSportLabel->show();
        ossigenazioneLabel->hide();
        criticitaLabel->hide();
        temperaturaLabel->hide();
        febbreLabel->hide();
    }
    Ossigenazione* sensoreOssigenazione = dynamic_cast<Ossigenazione*>(modello->getSensore(idSensore));
    if (sensoreOssigenazione != nullptr) {
        if(sensoreOssigenazione->segnalazione()) criticitaLabel->setText("Si") ;
        else criticitaLabel->setText("No");
        frameGrafico->show();
        sportAvgLabel->hide();
        valueSportLabel->hide();
        ossigenazioneLabel->show();
        criticitaLabel->show();
        temperaturaLabel->hide();
        febbreLabel->hide();
    }
    Temperatura* sensoreTemperatura = dynamic_cast<Temperatura*>(modello->getSensore(idSensore));
    if (sensoreTemperatura != nullptr) {
        if(sensoreTemperatura->febbre()) febbreLabel->setText("Si") ;
        else febbreLabel->setText("No");
        frameGrafico->show();
        sportAvgLabel->hide();
        valueSportLabel->hide();
        ossigenazioneLabel->hide();
        criticitaLabel->hide();
        temperaturaLabel->show();
        febbreLabel->show();
    }
    serieDati->clear();
    int index=0;
    for (const auto& dato : modello->getSensore(idSensore)->getMisurazioni()) {
        serieDati->append(index, dato);
        ++index;
    }

    qreal maxValue = std::numeric_limits<qreal>::lowest();
    foreach(const QPointF &point, serieDati->points()) {
        if(point.y() > maxValue) { // Confronta il valore y di ogni punto
            maxValue = point.y(); // Aggiorna il massimo se il punto corrente è maggiore
        }
    }

    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;

    foreach(QAbstractAxis *axis, chartDati->axes()) {
        if(axis->orientation() == Qt::Horizontal) { // Asse X
            axisX = qobject_cast<QValueAxis *>(axis);
            if(axisX) { // Se l'asse è un QValueAxis, resetta i limiti
                axisX->setMin(0);
                axisX->setMax(serieDati->points().size()); // Resetta il massimo
                axisX->setLabelFormat("%d");
            }
        } else if(axis->orientation() == Qt::Vertical) { // Asse Y
            axisY = qobject_cast<QValueAxis *>(axis);
            if(axisY) {
                axisY->setMin(0);
                axisY->setMax(maxValue+50);
            }
        }
    }

    if(!axisX) {
        axisX = new QValueAxis;
        chartDati->addAxis(axisX, Qt::AlignBottom);
    }
    if(!axisY) {
        axisY = new QValueAxis;
        chartDati->addAxis(axisY, Qt::AlignLeft);
    }
}
