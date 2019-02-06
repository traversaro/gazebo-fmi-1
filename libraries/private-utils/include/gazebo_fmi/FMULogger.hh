/*
 * Copyright (C) 2019 Fondazione Istituto Italiano di Tecnologia
 *
 * Licensed under either the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 * or the GNU Lesser General Public License v2.1 :
 * https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 * at your option.
 */

#ifndef GAZEBO_FMI_FMU_LOGGER
#define GAZEBO_FMI_FMU_LOGGER

#include "FMUCoSimulation.hh"

#include <map>
#include <vector>

#include <gazebo/common/Events.hh>

namespace gazebo_fmi
{
    struct FMULog
    {
        std::string m_FMUInstanceName;
        const FMUCoSimulation* m_fmu{nullptr};
        std::map<std::string, std::vector<double> >  m_log;

        FMULog(std::string instanceName, const FMUCoSimulation* pointer) :
            m_FMUInstanceName(instanceName), m_fmu{pointer}
            {}
    };

    class FMULoggerSingleton final
    {
    public:
        static FMULoggerSingleton& GetInstance();

        /**
         * Add an FMU to the logger.
         */
        void addFMU(const std::string instanceName, const FMUCoSimulation *fmu);

        /**
         * Remove the fmu
         */
        void removeFMU(const std::string instanceName);

        /// \brief Callback on world update end event
        private: void WorldUpdateEndCallback();


    private:
        FMULoggerSingleton() = default;
        ~FMULoggerSingleton();

        FMULoggerSingleton(const FMULoggerSingleton&) = delete;
        FMULoggerSingleton& operator=(const FMULoggerSingleton&) = delete;
        FMULoggerSingleton(FMULoggerSingleton&&) = delete;
        FMULoggerSingleton& operator=(FMULoggerSingleton&&) = delete;

        gazebo::event::ConnectionPtr m_connection;
        std::vector<FMULog> m_logger;

        void writeToFile();
    };
}

#endif
