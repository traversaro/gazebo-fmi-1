/*
 * Copyright (C) 2018 Fondazione Istituto Italiano di Tecnologia
 *
 * Licensed under either the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 * or the GNU Lesser General Public License v2.1 :
 * https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 * at your option.
 */

#include <gazebo_fmi/FMULogger.hh>

#include <gazebo/common/Console.hh>

#include <boost/bind.hpp>

namespace gazebo_fmi
{
    FMULoggerSingleton& FMULoggerSingleton::GetInstance()
    {
        static FMULoggerSingleton instance;
        return instance;
    }

    void FMULoggerSingleton::addFMU(const std::string instanceName, const FMUCoSimulation *fmu)
    {
        if (!m_connection)
        {
            m_connection = gazebo::event::Events::ConnectWorldUpdateEnd(boost::bind(&FMULoggerSingleton::WorldUpdateEndCallback, this));
        }

        m_logger.push_back(FMULog(instanceName, fmu));
    }

    void FMULoggerSingleton::removeFMU(const std::string instanceName)
    {
        for (size_t i=0; i  < m_logger.size(); i++)
        {
            if (m_logger[i].m_FMUInstanceName ==  instanceName)
            {
                m_logger[i].m_fmu = nullptr;
                break;
            }
        }
    }

    void FMULoggerSingleton::WorldUpdateEndCallback()
    {
        for (size_t i=0; i  < m_logger.size(); i++)
        {
            if (m_logger[i].m_fmu)
            {
                // Save variables of the fmu in m_logger[i].m_log (including timestamp)
            }
        }
    }

    FMULoggerSingleton::~FMULoggerSingleton()
    {
        // Save contents of m_logger in a .mat file
    }

}
