/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

/**
 * \file main-window.cpp
 * \brief The main windows file.
 * \author Pierre Weiss
 * \date 2009
 */

#include <iostream>
#include <stdexcept>

#include "main-window.h"
#include "drag-widget.h"
#include "drag-object.h"

#include "tap.h"
#include "emu.h"

MainWindow::MainWindow(const std::string &simulationName)
{
  this->m_dw = NULL;
  this->m_gen = new Generator(simulationName);

  //
  // Menu
  //
  QMenu *menuFichier = menuBar()->addMenu("&File");
  QAction *menuOpen = menuFichier->addAction("Open");
  menuOpen->setDisabled(true);
  QAction *menuNew = menuFichier->addAction("New");
  menuNew->setDisabled(true);
  QAction *menuSave = menuFichier->addAction("Save");
  menuSave->setDisabled(true);
  QAction *menuSaveAs = menuFichier->addAction("Save as");
  menuSaveAs->setDisabled(true);
  QAction *menuSavePix = menuFichier->addAction("Save as picture");
  connect(menuSavePix, SIGNAL(triggered()), this, SLOT(SavePicture()));
  /* menuSavePix->setDisabled(true); */

  QAction *actionQuit = menuFichier->addAction("Quit");
  connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdit = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdit->addAction("Configuration");
  actionConfig->setDisabled(true);
  connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 

  QMenu *menuView = menuBar()->addMenu("&Generate");
  QAction *actionCpp = menuView->addAction("&C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  QAction *actionPython = menuView->addAction("&Python");
  connect(actionPython, SIGNAL(triggered()), this, SLOT(GeneratePython()));

  QMenu *menuHelp = menuBar()->addMenu("&Help");
  QAction *menuOnlineHelp = menuHelp->addAction("Online Help");
  menuOnlineHelp->setDisabled(true);
  connect(menuOnlineHelp, SIGNAL(triggered()), this, SLOT(Help()));
  QAction *menuAbout = menuHelp->addAction("About");
  connect(menuAbout, SIGNAL(triggered()), this, SLOT(About())); 

  menuAbout = menuAbout;
  menuHelp = menuHelp;

  //
  // toolbar for add equipements.
  //
  QToolBar *toolBarFichier = addToolBar("");
  //PC
  QIcon pcIcon(":/Ico/Pc.png");
  QString pcString("Terminal");  
  QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
  connect(pcAction, SIGNAL(triggered()), this, SLOT(CreatePc()));
  //Pc-group
  QIcon pcgIcon(":/Ico/Pc-group.png");
  QString pcgString("Terminal Group");  
  QAction *pcgAction = toolBarFichier->addAction(pcgIcon, pcgString);
  connect(pcgAction, SIGNAL(triggered()), this, SLOT(CreatePcGroup()));
  //PC-Emu
  QIcon emuIcon(":/Ico/Emu.png");
  QString emuString("PC with emu");  
  QAction *emuAction = toolBarFichier->addAction(emuIcon, emuString);
  connect(emuAction, SIGNAL(triggered()), this, SLOT(CreateEmu()));
  //PC-Tap
  QIcon tapIcon(":/Ico/Tap.png");
  QString tapString("PC with tap");  
  QAction *tapAction = toolBarFichier->addAction(tapIcon, tapString);
  connect(tapAction, SIGNAL(triggered()), this, SLOT(CreateTap()));
  //AP-Wifi
  QIcon apIcon(":/Ico/Ap-Wifi.png");
  QString apString("AP Wifi");  
  QAction *apAction = toolBarFichier->addAction(apIcon, apString);
  connect(apAction, SIGNAL(triggered()), this, SLOT(CreateAp()));
  //StationWifi
  QIcon stasIcon(":/Ico/StationWifi.png");
  QString stasString("Station Wifi");  
  QAction *stasAction = toolBarFichier->addAction(stasIcon, stasString);
  connect(stasAction, SIGNAL(triggered()), this, SLOT(CreateStation()));
  //Hub
  QIcon hubIcon(":/Ico/Hub.png");
  QString hubString("Hub");  
  QAction *hubAction = toolBarFichier->addAction(hubIcon, hubString);
  connect(hubAction, SIGNAL(triggered()), this, SLOT(CreateHub()));
  //Switch
  QIcon switchIcon(":/Ico/Switch.png");
  QString switchString("Switch");  
  QAction *switchAction = toolBarFichier->addAction(switchIcon, switchString);
  connect(switchAction, SIGNAL(triggered()), this, SLOT(CreateSwitch()));
  //Router
  QIcon routerIcon(":/Ico/Router.png");
  QString routerString("Router");  
  QAction *routerAction = toolBarFichier->addAction(routerIcon, routerString);
  connect(routerAction, SIGNAL(triggered()), this, SLOT(CreateRouter()));
  //separator
  toolBarFichier->addSeparator();
  // Wired Link
  QIcon linkIcon(":/Ico/WiredLink.png");
  QString linkString("Wired Link");  
  QAction *linkAction = toolBarFichier->addAction(linkIcon, linkString);
  connect(linkAction, SIGNAL(triggered()), this, SLOT(CreateWiredLink()));
  // Station link
  QIcon stasLinkIcon(":/Ico/Link.png");
  QString stasLinkString("Station Link");  
  QAction *stasLinkAction = toolBarFichier->addAction(stasLinkIcon, stasLinkString);
  connect(stasLinkAction, SIGNAL(triggered()), this, SLOT(CreateStationLink()));
  //P2P link
  QIcon p2pLinkIcon(":/Ico/P2pLink.png");
  QString p2pLinkString("P2P Link");  
  QAction *p2pLinkAction = toolBarFichier->addAction(p2pLinkIcon, p2pLinkString);
  connect(p2pLinkAction, SIGNAL(triggered()), this, SLOT(CreateP2pLink()));
  //separator
  toolBarFichier->addSeparator();
  QIcon appsLinkIcon("");
  QString appsLinkString("Application");  
  QAction *appsLinkAction = toolBarFichier->addAction(appsLinkIcon, appsLinkString);
  connect(appsLinkAction, SIGNAL(triggered()), this, SLOT(CreateApps()));
  //separator
  toolBarFichier->addSeparator();
  //Delete button
  QIcon delIcon(":/Ico/Del.png");
  QString delString("Delete");
  this->m_delAction = toolBarFichier->addAction(delIcon, delString);
  this->m_delAction->setDisabled (true);  
  connect(this->m_delAction, SIGNAL(triggered()), this, SLOT(DeleteObject()));

  //
  // Creation of Drag N Drop Area.
  //
  QHBoxLayout *dragLayout = new QHBoxLayout;
  this->m_dw = new DragWidget();

  dragLayout->addWidget(this->m_dw);

  QWidget *zoneCentral = new QWidget; 
  zoneCentral->setLayout(dragLayout);

  this->setCentralWidget(zoneCentral);

  //
  // 
  //
  this->m_dw->SetMainWindow(this);
}

MainWindow::~MainWindow()
{
  delete this->m_gen;
}

void MainWindow::CreatePc()
{
  this->m_gen->AddNode("Pc");
  this->m_dw->CreateObject("Pc", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreatePcGroup()
{
  bool ok;
  size_t number = 0;
  QString text = QInputDialog::getText(this, "Terminal Group",
      tr("Enter the number of machines to create :"), QLineEdit::Normal,
      "", &ok);
  if (ok && !text.isEmpty())
  {
    /* number ok ! */
    number = text.toUInt();
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  if(number <= (size_t) 0 )
  {
    QMessageBox::about(this, "Error", "The pc number can't be negative ...");
    return;
  }

  this->m_gen->AddNode("Pc",number);
  this->m_dw->CreateObject("Pc-group", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateEmu()
{
  this->CleanIface();

  bool ok;
  QString text = QInputDialog::getText(this, "Emu",
      tr("Enter the real host interface to use:"), QLineEdit::Normal,
      "eth0", &ok);
  if (ok && !text.isEmpty())
  {
    /* test if the iface is already used. */
    for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->m_gen->AddNode("Pc");
  this->m_gen->AddLink("Emu", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  this->m_dw->CreateObject("Emu",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateTap()
{
  this->CleanIface();

  bool ok;
  QString text = QInputDialog::getText(this, "Tap",
      tr("Enter the new interface to use :"), QLineEdit::Normal,
      "tap0", &ok);
  if (ok && !text.isEmpty())
  {
    for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->m_gen->AddNode("Tap");
  this->m_gen->AddLink("Tap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  this->m_dw->CreateObject("Tap",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CleanIface()
{
  /* remove from list the unused iface. */
  bool used = false;
  for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
  {
    used = false;
    for(size_t j = 0; j < this->m_gen->GetNLinks(); j++)
    {
      if( (this->m_gen->GetLink(j)->GetLinkName()).find("tap_") == 0)
      {
        if( this->m_listIface.at(i) == static_cast<Tap*>(this->m_gen->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
      if( (this->m_gen->GetLink(j)->GetLinkName()).find("emu_") == 0 ) 
      {
        if( this->m_listIface.at(i) == static_cast<Emu*>(this->m_gen->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
    }
    if(!used)
    {
      this->m_listIface.erase(this->m_listIface.begin() + i);
    }
  }
}

void MainWindow::CreateAp()
{  
  this->m_gen->AddNode("Ap");
  this->m_gen->AddLink("Ap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  this->m_dw->CreateObject("Ap", this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName() );
}

void MainWindow::CreateStation()
{
  this->m_gen->AddNode("Station");
  this->m_dw->CreateObject("Station", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateHub()
{
  this->m_gen->AddLink("Hub");
  this->m_dw->CreateObject("Hub", this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateSwitch()
{
  this->m_gen->AddNode("Bridge");
  this->m_gen->AddLink("Bridge", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  this->m_dw->CreateObject("Switch",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateRouter()
{
  this->m_gen->AddNode("Router");
  this->m_dw->CreateObject("Router", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateWiredLink()
{
  /*
   * The differents link :
   *  - Pc to Pc (create a hide hub)
   *  - Pc to Hub
   *  - Pc to Bridge
   *  - Pc to Router (create a hide hub)
   *  - Pc to Ap
   *  - Ap to Router
   *  - Hub to Router
   *  - Switch to Router
   *  - Pc to emu
   *  - Pc to Tap
   */
  if(this->m_dw->GetTraceLink())
  {
    this->m_dw->SetTraceLink(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceLink(true);
  this->m_dw->SetLinkType("WiredLink");
}

void MainWindow::ValidLink()
{
  /* function called when the two equipement are selected. */
  /* get the selected equipement. */
  this->m_dw->SetTraceLink(false);

  std::vector<std::string> equi = this->m_dw->GetLastSelected();
  size_t indic = 0;

  if(equi.at(0) == "" || equi.at(1) == "" || equi.at(0) == "deleted" || equi.at(1) == "deleted")
  {
    QMessageBox::about(this, "Error", "You don't have selected two equipement.");
    for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(1) == this->m_dw->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(0) == this->m_dw->GetNDrawLines(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLines(i);
      }
    }
    this->m_dw->ResetSelected();
    return;
  }

  if(equi.at(0) == equi.at(1))
  {
    QMessageBox::about(this, "Error", "You can't connect object to itself.");
    for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(1) == this->m_dw->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(0) == this->m_dw->GetNDrawLines(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLines(i);
      }
    }
    this->m_dw->ResetSelected();
    return;
  }

  //
  // LINK to LINK
  //

  if( (equi.at(0).find("wifi_") == 0 || equi.at(0).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
        (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 )) && 
      (equi.at(1).find("wifi_") == 0 || equi.at(1).find("hub_") == 0 || (equi.at(1)).find("bridge_") == 0 || 
       (equi.at(1)).find("emu_") == 0 || (equi.at(1).find("tap_") == 0)) )
  {
    QMessageBox::about(this, "Error", "This link can't be etablished. Please use a Pc or a Router.");
    for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(1) == this->m_dw->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->GetNDrawLines(i).GetFirst() && equi.at(0) == this->m_dw->GetNDrawLines(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLines(i);
      }
    }
    this->m_dw->ResetSelected();
    return;
  }
  //
  // OTHERS
  //
  else if( (equi.at(0)).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
      (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    { 
      if( this->m_gen->GetLink(i)->GetLinkName() == equi.at(0))
      {
        indic = i;
      }
    }
    this->ConnectNode(indic, equi.at(1));
  }
  else if ((equi.at(1)).find("hub_") == 0 || (equi.at(1)).find("bridge_") == 0 || 
      (equi.at(1)).find("emu_") == 0 || (equi.at(1).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    { 
      if( this->m_gen->GetLink(i)->GetLinkName() == equi.at(1))
      {
        indic = i;
      }
    }
    this->ConnectNode(indic, equi.at(0));
  }
  else
  {
    size_t number = -1;
    size_t number2 = -1;

    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    {
      if(equi.at(0) == this->m_gen->GetLink(i)->GetLinkName())
      {
        number = i;
        break;
      }
      if(equi.at(1) == this->m_gen->GetLink(i)->GetLinkName())
      {
        number2 = i;
        break;
      }
    }
    if(number != (size_t) - 1)
    {
      this->ConnectNode(number, equi.at(1));
    }
    else if(number2 != (size_t) - 1)
    {
      this->ConnectNode(number2, equi.at(0));
    }
    else
    {
      /* you can't connect for example two terminals without an csma network so ... */
      if(equi.at(2) == "WiredLink")
      {
        this->m_gen->AddLink("Hub");
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(1));
      }
      else if(equi.at(2) == "P2pLink")
      {
        this->m_gen->AddLink("PointToPoint");
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(1));
      }
      else
      {
        QMessageBox::about(this, "Error", "An error occured.");
        /* delete the two equi .... */
        for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
        {
          if(equi.at(0) == this->m_dw->GetNDrawLines(i).GetFirst() || equi.at(1) == this->m_dw->GetNDrawLines(i).GetFirst() )
          {
            this->m_dw->EraseDrawLines(i);
          }
        }
      }
    } 
  }

  /* Draw the connection. */
  this->m_dw->DrawLine();
  this->m_dw->ResetSelected();
}

void MainWindow::CreateStationLink()
{
  if(this->m_dw->GetTraceLink())
  {
    this->m_dw->SetTraceLink(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceLink(true);
  this->m_dw->SetLinkType("WifiLink");
}

void MainWindow::CreateP2pLink()
{
  if(this->m_dw->GetTraceLink())
  {
    this->m_dw->SetTraceLink(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceLink(true);
  this->m_dw->SetLinkType("P2pLink");
}

void MainWindow::ConfigurationMenu()
{
}

void MainWindow::DeleteObject()
{
  this->m_dw->DeleteSelected();
}

void MainWindow::About()
{
  QMessageBox::about(this, "About",
      tr("<p align=\"center\">"
        "<h2>The ns-3 topology generator"
        "</h2>"
        "</p><br />"
        "Copyright (c) 2009 University of Strasbourg<br /><br />"
        "This program is free software; you can redistribute it and/or<br />"
        "modify it under the terms of the GNU General Public License<br />"
        "as published by the Free Software Foundation; either version 2<br />"
        "of the License, or (at your option) any later version.<br />"
        "<br />"
        "<strong>Authors:</strong><br />"
        "Pierre Weiss &lt;3weissp@gmail.com&gt;<br />"
        "Sebastien Vincent &lt;vincent@clarinet.u-strasbg.fr&gt;"
        ));
}

void MainWindow::Help()
{

}

void MainWindow::ConnectNode(const size_t &linkNumber, const std::string &nodeName)
{
  /* test if the link exist. */
  try
  {
    this->m_gen->GetLink(linkNumber);
  }
  catch(const std::out_of_range &e)
  {
    QMessageBox::about(this, "Error", "This link doesn't exist.");
    for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
    {
      if( (nodeName == this->m_dw->GetNDrawLines(i).GetFirst() && this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->GetNDrawLines(i).GetSecond()) ||
          (this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->GetNDrawLines(i).GetFirst() && nodeName == this->m_dw->GetNDrawLines(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLines(i);
      }
    }
    return;
  }

  size_t numberOfConnectedMachines = 0;
  /* get the number of machines to add */
  if(nodeName.find("Get") == 0)
  {
    numberOfConnectedMachines += 1;
  }
  else
  {
    for(size_t i = 0; i < (size_t) this->m_gen->GetNNodes(); i++)
    {
      if(nodeName == this->m_gen->GetNode(i)->GetNodeName())
      {
        numberOfConnectedMachines += MainWindow::m_gen->GetNode(i)->GetMachinesNumber();
      }
    }
  }

  /* get the number of machines also connected. */
  std::vector<std::string> nodes = this->m_gen->GetLink(linkNumber)->GetInstalledNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->m_gen->GetNNodes(); j++)
    {
      if(nodes.at(i) == this->m_gen->GetNode(j)->GetNodeName())
      {
        numberOfConnectedMachines += this->m_gen->GetNode(j)->GetMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    for(size_t i = 0; i < (size_t) this->m_dw->GetDrawLines().size(); i++)
    {
      if( (nodeName == this->m_dw->GetNDrawLines(i).GetFirst() && this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->GetNDrawLines(i).GetSecond()) ||
          (this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->GetNDrawLines(i).GetFirst() && nodeName == this->m_dw->GetNDrawLines(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLines(i);
      }
    }
    return;
  }
  this->m_gen->GetLink(linkNumber)->Install(nodeName);
}

void MainWindow::GenerateCpp()
{
  this->m_gen->GenerateCodeCpp();
}

void MainWindow::GeneratePython()
{
  this->m_gen->GenerateCodePython();
}

void MainWindow::CreateApps()
{
  QDialog *dialog = new QDialog(this);
  dialog->setWindowTitle("Application");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  QLabel *title = new QLabel("<h2>Select the application you want to install :</h2>", dialog);
  layout->addWidget(title, 0, 3);

  /* PING */
  QLabel *appsPing;
  appsPing = new QLabel("Ping", dialog);
  layout->addWidget(appsPing, 2, 0);

  QCheckBox *box_appsPing = new QCheckBox(dialog);
  layout->addWidget(box_appsPing, 2, 1);

  /* UDP ECHO */
  QLabel *appsUdpEcho;
  appsUdpEcho = new QLabel("Udp Echo", dialog);
  layout->addWidget(appsUdpEcho, 3, 0);

  QCheckBox *box_appsUdpEcho = new QCheckBox(dialog);
  layout->addWidget(box_appsUdpEcho, 3, 1);

  /* TCP LARGE TRANSFER */
  QLabel *appsTcp;
  appsTcp = new QLabel("Tcp Large Transfer", dialog);
  layout->addWidget(appsTcp, 4, 0);

  QCheckBox *box_appsTcp = new QCheckBox(dialog);
  layout->addWidget(box_appsTcp, 4, 1);

  layout->addWidget(buttonBox, 15, 3);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    if(box_appsPing->isChecked())
    {
      this->m_dw->SetAppsPing(true);
      this->m_dw->ShowGuiPing();
    }
    else if(box_appsUdpEcho->isChecked())
    {
      this->m_dw->SetAppsUdpEcho(true);
      this->m_dw->ShowGuiUdpEcho();
    }
    else if(box_appsTcp->isChecked())
    {
      this->m_dw->SetAppsTcp(true);
      this->m_dw->ShowGuiTcp();
    }
  }
}

void MainWindow::ValidApps()
{
  if(this->m_dw->GetAppsPing())
  {
    this->m_gen->AddApplication("Ping", this->m_dw->GetAppsServer(), this->m_dw->GetAppsClient(), this->m_dw->GetStartTime(), this->m_dw->GetEndTime());
    QMessageBox::about(this, "Ping", "Ping successfull installed.");
  }

  if(this->m_dw->GetAppsUdpEcho())
  {
    this->m_gen->AddApplication("UdpEcho", this->m_dw->GetAppsServer(), this->m_dw->GetAppsClient(), this->m_dw->GetStartTime(), this->m_dw->GetEndTime(), this->m_dw->GetPort());
    QMessageBox::about(this, "Udp Echo", "Udp echo successfull installed.");
  }

  if(this->m_dw->GetAppsTcp())
  {
    this->m_gen->AddApplication("TcpLargeTransfer", this->m_dw->GetAppsServer(), this->m_dw->GetAppsClient(), this->m_dw->GetStartTime(), this->m_dw->GetEndTime(), this->m_dw->GetPort());
    QMessageBox::about(this, "Tcp Large Transfer", "Tcp large transfer successfull installed.");
  }

  this->m_dw->SetAppsPing(false);
  this->m_dw->SetAppsUdpEcho(false);
  this->m_dw->SetAppsTcp(false);
  this->m_dw->SetAppsServer("");
  this->m_dw->SetAppsClient("");
  this->m_dw->SetStartTime(0);
  this->m_dw->SetEndTime(0);
  this->m_dw->SetPort(0);
}

void MainWindow::SavePicture()
{
  QFileDialog dlg(this, tr("Save image"));

  dlg.setFileMode(QFileDialog::AnyFile);
 
  if(dlg.exec())
  {
    QImage img = QPixmap::grabWidget(this->m_dw).toImage();
    QString fileName = dlg.selectedFiles().at(0);

    /* check if file exists and notificate the user */
    if(QFile(fileName).exists())
    {
      if(QMessageBox(QMessageBox::Question, "File exists", "File already exists. Overwrite ?", 
            QMessageBox::Ok | QMessageBox::No).exec() != QMessageBox::Ok)
      {
        return;
      }
    }

    if(img.save(fileName))
    {
      QMessageBox(QMessageBox::Information, "Save picture", "Picture saved at " + fileName).exec();
    }
    else
    {
      QMessageBox(QMessageBox::Warning, "Save picture", "Picture saving failed!").exec();
    }
  }
}

void MainWindow::SetGenerator(Generator *gen)
{
  this->m_gen = gen;
}

Generator* MainWindow::GetGenerator()
{
  return this->m_gen;
}

void MainWindow::SetDelQAction(QAction *delAction)
{
  this->m_delAction = delAction;
}

QAction* MainWindow::GetDelQAction()
{
  return this->m_delAction;
}

void MainWindow::SetDragWidget(DragWidget *dw)
{
  this->m_dw = dw;
}

DragWidget* MainWindow::GetDragWidget()
{
  return this->m_dw;
}

void MainWindow::AddIfaceList(const std::string &str)
{
  this->m_listIface.push_back(str);
}

std::vector<std::string> MainWindow::GetIfaceList()
{
  return this->m_listIface;
}

std::string MainWindow::GetNIfaceList(const size_t &index)
{
  return this->m_listIface.at(index);
}

void MainWindow::EraseIfaceList(const size_t &index)
{
  this->m_listIface.erase(this->m_listIface.begin() + index);
}

