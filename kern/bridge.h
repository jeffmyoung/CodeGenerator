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
 * \file bridge.h
 * \brief bridge link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief bridge link subclass.
 *
 *  The bridge class is a subclass of link.
 *
 *  This class represent a bridge.
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an bridge with generator object.
 *    - Install nodes with install method.
 */
class Bridge : public Link
{
  public:
    /**
     * \brief constructor.
     * \param _indice is the Bridge number
     * \param _nodeBridge is the node name.
     */
    Bridge(const size_t &_indice, const std::string &_nodeBridge);

    /**
     * \brief destructor.
     */
    virtual ~Bridge();

  private:
    /**
     * \brief this attribute represent the bridge node name.
     */
    std::string nodeBridge;

    /**
     * \brief function used to get the bridge node name.
     * \return the node name.
     */
    std::string getNodeBridge();

    /**
     * \brief function which generate the headers.
     * \return the headers.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief function which generate the build link code.
     * \return the build link code.
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief function which return the build of the net device container.
     * \return the net device container.
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief function to generate the trace line.
     * \return the trace line.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* BRIDGE_H */
