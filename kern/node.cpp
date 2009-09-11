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
 * \file Node.cpp
 * \brief Node Base Class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "node.h"
#include "generator.h"

#include "utils.h"

Node::Node(const size_t &_indice, const std::string &_type, const size_t &_machinesNumber)
{
  this->indice = _indice;
  this->nodeName = _type + utils::toString(_indice);
  this->ipInterfaceName = "iface_" + this->nodeName;
  this->nsc = "";	
  this->machinesNumber = _machinesNumber;
}

Node::~Node()
{
}

std::vector<std::string> Node::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/helper-module.h\"");

  return headers; 
}

std::vector<std::string> Node::GenerateNode()
{
  std::vector<std::string> nodes;
  nodes.push_back("NodeContainer " + this->getNodeName() + ";");
  nodes.push_back(this->getNodeName() + ".Create(" + utils::toString(this->machinesNumber) + ");");

  return nodes; 
}

std::vector<std::string> Node::GenerateIpStack()
{
  std::vector<std::string> stack;
  
  if(this->getNsc() != "")
  {
    stack.push_back("internetStackH.SetTcp (\"ns3::NscTcpL4Protocol\",\"Library\",StringValue(nscStack));");
  }
  stack.push_back("internetStackH.Install (" + this->getNodeName() + ");");

  return stack; 
}

void Node::setNodeName(const std::string &_nodeName)
{
  this->nodeName = _nodeName;
}

void Node::setIpInterfaceName(const std::string &_ipInterfaceName)
{
  this->ipInterfaceName = _ipInterfaceName;
}

std::string Node::getNodeName()
{
  return this->nodeName;
}

std::string Node::getNodeName(const size_t &number)
{
  return std::string("NodeContainer(" + this->nodeName + ".Get(" + utils::toString(number) + "))");
}

std::string Node::getIpInterfaceName()
{
  return this->ipInterfaceName;
}

std::string Node::getIndice()
{
  return utils::toString(this->indice);
}

std::string Node::getNsc()
{
  return this->nsc;
}

void Node::setNsc(const std::string &_nsc)
{
  this->nsc = _nsc;
}

size_t Node::getMachinesNumber()
{
  return this->machinesNumber;
}

void Node::setMachinesNumber(const size_t &_machinesNumber)
{
  this->machinesNumber = _machinesNumber;
}
