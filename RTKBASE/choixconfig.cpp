// RTKBASE is a GUI interface for RTKLIB made for the Raspberry pî and a touchscreen
//   Copyright (C) 2016
//   David ENSG PPMD-2016 (first rtkbase release)
//   Francklin N'guyen van <francklin2@wanadoo.fr>
//   Sylvain Poulain <sylvain.poulain@giscan.com>
//   Vladimir ENSG PPMD-2017 (editable configuration)
//   Saif Aati ENSG PPMD-2018 (post processing)
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "choixconfig.h"
#include "ui_choixconfig.h"
#include "affichesolutions.h"
#include "choixedite.h"
#include "gestionconfig.h"
#include <iostream>

ChoixConfig::ChoixConfig(int _rover_edit, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ChoixConfig)
{
    ui->setupUi(this);
    rover_edit=_rover_edit;

    this->setWindowFlags(Qt::Window);
    this->showFullScreen();

    if(rover_edit==0) ui->WindowTitleEdit->setText(QString("CONFIGURATION CHOICE"));
    else ui->WindowTitleEdit->setText(QString("MODELE CHOICE"));

    QObject::connect(ui->SingleButton,SIGNAL(clicked()),this,SLOT(ouvreSingle()));
    QObject::connect(ui->SBASButton,SIGNAL(clicked()),this,SLOT(ouvreSBAS()));
    QObject::connect(ui->DGPSButton,SIGNAL(clicked()),this,SLOT(ouvreDGPS()));
    QObject::connect(ui->PPPButton,SIGNAL(clicked()),this,SLOT(ouvrePPP()));
    QObject::connect(ui->RTKButton,SIGNAL(clicked()),this,SLOT(ouvreRTKstatic()));
    QObject::connect(ui->RTKButton_2,SIGNAL(clicked()),this,SLOT(ouvreRTKkinematic()));

    QObject::connect(ui->Custom1Button,SIGNAL(clicked()),this,SLOT(OuvreConfig1()));
    QObject::connect(ui->Custom2Button,SIGNAL(clicked()),this,SLOT(OuvreConfig2()));
    QObject::connect(ui->Custom3Button,SIGNAL(clicked()),this,SLOT(OuvreConfig3()));
    QObject::connect(ui->Custom4Button,SIGNAL(clicked()),this,SLOT(OuvreConfig4()));
    QObject::connect(ui->Custom5Button,SIGNAL(clicked()),this,SLOT(OuvreConfig5()));
    QObject::connect(ui->Custom6Button,SIGNAL(clicked()),this,SLOT(OuvreConfig6()));
    QObject::connect(ui->Custom7Button,SIGNAL(clicked()),this,SLOT(OuvreConfig7()));
    QObject::connect(ui->Custom8Button,SIGNAL(clicked()),this,SLOT(OuvreConfig8()));
    QObject::connect(ui->Custom9Button,SIGNAL(clicked()),this,SLOT(OuvreConfig9()));
    QObject::connect(ui->Custom10Button,SIGNAL(clicked()),this,SLOT(OuvreConfig10()));
    QObject::connect(ui->Custom11Button,SIGNAL(clicked()),this,SLOT(OuvreConfig11()));
    QObject::connect(ui->Custom12Button,SIGNAL(clicked()),this,SLOT(OuvreConfig12()));

    QObject::connect(ui->ReturnButton,SIGNAL(clicked()),this,SLOT(Retour()));

    if(rover_edit==0)
    {
        ui->EditeButton->show();
        QObject::connect(ui->EditeButton,SIGNAL(clicked()),this,SLOT(OuvreEdit()));
    }
    else
    {
        ui->EditeButton->hide();
    }

    QFile configName(QString("../RTKBASE/data/ConfigNames"));
    configName.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line;
    QStringList list;
    QTextStream flux(&configName);
    while(! flux.atEnd())
    {
        line = flux.readLine();
        qDebug()<<line;
        list<<line;
    }
    configName.close();

    ui->Custom1Button->setText(list[0].simplified());
    ui->Custom2Button->setText(list[1].simplified());
    ui->Custom3Button->setText(list[2].simplified());
    ui->Custom4Button->setText(list[3].simplified());
    ui->Custom5Button->setText(list[4].simplified());
    ui->Custom6Button->setText(list[5].simplified());
    ui->Custom7Button->setText(list[6].simplified());
    ui->Custom8Button->setText(list[7].simplified());
    ui->Custom9Button->setText(list[8].simplified());
    ui->Custom10Button->setText(list[9].simplified());
    ui->Custom11Button->setText(list[10].simplified());
    ui->Custom12Button->setText(list[11].simplified());
}

ChoixConfig::~ChoixConfig()
{
    delete ui;
}

void ChoixConfig::OuvreAfficheSolutions(QString configFile)
{
    AfficheSolutions SingleRoverSolutions(configFile);
    this->close();
    SingleRoverSolutions.showFullScreen();// NE FONCTIONNE PAS, NE CHANGE RIEN...
    SingleRoverSolutions.exec();
}

void ChoixConfig::OuvreChoixEdit(QString modeleFile)
{
    ChoixEdite *FenetreChoixEdit = new ChoixEdite(modeleFile);
    QObject::connect(FenetreChoixEdit,SIGNAL(DemandeRetour()),this,SLOT(Affiche()));
    QObject::connect(FenetreChoixEdit,SIGNAL(DemandeFerme()),this,SLOT(FermeTout()));
    this->hide();
    FenetreChoixEdit->setWindowFlags(Qt::FramelessWindowHint);
    FenetreChoixEdit->exec();
}

void ChoixConfig::ouvreSingle()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Single.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Single.conf"));
}

void ChoixConfig::ouvreSBAS()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/SBAS.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/SBAS.conf"));
}

void ChoixConfig::ouvreDGPS()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/DGPS.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/DGPS.conf"));
}

void ChoixConfig::ouvrePPP()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/PPP-Static.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/PPP-Static.conf"));
}

void ChoixConfig::ouvreRTKstatic()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/RTK-Static.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/RTK-Static.conf"));
}

void ChoixConfig::ouvreRTKkinematic()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/RTK-Kinematic.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/RTK-Kinematic.conf"));
}

void ChoixConfig::OuvreConfig1()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom1.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom1.conf"));
}

void ChoixConfig::OuvreConfig2()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom2.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom2.conf"));
}

void ChoixConfig::OuvreConfig3()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom3.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom3.conf"));
}

void ChoixConfig::OuvreConfig4()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom4.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom4.conf"));
}

void ChoixConfig::OuvreConfig5()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom5.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom5.conf"));
}

void ChoixConfig::OuvreConfig6()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom6.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom6.conf"));
}

void ChoixConfig::OuvreConfig7()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom7.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom7.conf"));
}

void ChoixConfig::OuvreConfig8()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom8.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom8.conf"));
}

void ChoixConfig::OuvreConfig9()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom9.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom9.conf"));
}

void ChoixConfig::OuvreConfig10()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom10.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom10.conf"));
}

void ChoixConfig::OuvreConfig11()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom11.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom11.conf"));
}

void ChoixConfig::OuvreConfig12()
{
    if(rover_edit==0) OuvreAfficheSolutions(QString("../RTKBASE/ConfFiles/Custom12.conf"));
    else OuvreChoixEdit(QString("../RTKBASE/ConfFiles/Custom12.conf"));
}

void ChoixConfig::OuvreEdit()
{
    GestionConfig *FenetreGestionConfig=new GestionConfig();
    QObject::connect(FenetreGestionConfig,SIGNAL(DemandeMAJ()),this,SLOT(FermeTout()));
    FenetreGestionConfig->setModal(true);
    FenetreGestionConfig->setWindowFlags(Qt::FramelessWindowHint);
    FenetreGestionConfig->exec();
}

void ChoixConfig::Retour()
{
    if(rover_edit!=0)
    {
        /*GestionConfig *FenetreGestionConfig=new GestionConfig();
        FenetreGestionConfig->setModal(true);
        FenetreGestionConfig->setWindowFlags(Qt::FramelessWindowHint);
        FenetreGestionConfig->exec();*/
        emit DemandeRetour();
    }
    this->close();
}

void ChoixConfig::MAJNoms()
{
    QFile configName(QString("../RTKBASE/data/ConfigNames"));
    configName.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line;
    QStringList list;
    QTextStream flux(&configName);
    while(! flux.atEnd())
    {
        line = flux.readLine();
        qDebug()<<line;
        list<<line;
    }
    configName.close();

    ui->Custom1Button->setText(list[0].simplified());
    ui->Custom2Button->setText(list[1].simplified());
    ui->Custom3Button->setText(list[2].simplified());
    ui->Custom4Button->setText(list[3].simplified());
    ui->Custom5Button->setText(list[4].simplified());
    ui->Custom6Button->setText(list[5].simplified());
    ui->Custom7Button->setText(list[6].simplified());
    ui->Custom8Button->setText(list[7].simplified());
    ui->Custom9Button->setText(list[8].simplified());
    ui->Custom10Button->setText(list[9].simplified());
    ui->Custom11Button->setText(list[10].simplified());
    ui->Custom12Button->setText(list[11].simplified());
}

void ChoixConfig::Affiche()
{
    this->show();
    MAJNoms();
}

void ChoixConfig::FermeTout()
{
    if(rover_edit==0) MAJNoms();
    else
    {
        emit DemandeFerme();
        this->close();
    }
}
