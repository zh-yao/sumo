/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2010-2017 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
/****************************************************************************/
/// @file    MSSOTLSensors.h
/// @author  Gianfilippo Slager
/// @author  Anna Chiara Bellini
/// @date    Feb 2010
/// @version $Id$
///
// The base abstract class for SOTL sensors
/****************************************************************************/
#ifndef MSSOTLSensors_h
#define MSSOTLSensors_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "MSSOTLDefinitions.h"
#include "MSTrafficLightLogic.h"
#include <string>
#include <microsim/MSLane.h>
#include <netload/NLDetectorBuilder.h>
//#include <microsim/MSEdgeContinuations.h>

class MSSOTLSensors {
protected:
    const MSTrafficLightLogic::Phases* myPhases;
    std::string tlLogicID;
    int currentStep;

protected :
    /**
    * \brief This function member has to be extended to properly build a sensor for a specific input lane
    * Sensors has to be constrained on lane dimension
    * Built sensors has to be collected and associated properly to the respective MSLane for retrieval using MSSOTLSensors::countVehicles(std::string)
    * See extension classes for further specifications on sensor building
    */
    virtual void buildSensorForLane(MSLane* lane, NLDetectorBuilder& nb) = 0;
    /**
    * \brief This function member has to be extended to properly build a sensor for a specific output lane
    * Sensors has to be constrained on lane dimension
    * Built sensors has to be collected and associated properly to the respective MSLane for retrieval using MSSOTLSensors::countVehicles(std::string)
    * See extension classes for further specifications on sensor building
    */
    virtual void buildSensorForOutLane(MSLane* lane, NLDetectorBuilder& nb) = 0;

public:
    /*
    *
    */
    MSSOTLSensors(std::string tlLogicID, const MSTrafficLightLogic::Phases* phases);

    /*
    *
    */
    virtual ~MSSOTLSensors();

    /**
    * \brief This function member has to be extended to properly build sensors for the input lanes
    * Sensors has to be constrained on lane dimension
    * Built sensors has to be collected and associated properly to theirs MSLane for retrieval using MSSOTLSensors::countVehicles(std::string)
    * See extension classes for further specifications on sensor building
    */
    virtual void buildSensors(MSTrafficLightLogic::LaneVectorVector controlledLanes, NLDetectorBuilder& nb) = 0;
    /**
    * \brief This function member has to be extended to properly build sensors for the output lanes
    * Sensors has to be constrained on lane dimension
    * Built sensors has to be collected and associated properly to theirs MSLane for retrieval using MSSOTLSensors::countVehicles(std::string)
    * See extension classes for further specifications on sensor building
    */
    virtual void buildOutSensors(MSTrafficLightLogic::LaneVectorVector controlledLanes, NLDetectorBuilder& nb) = 0;

    /*
     * Returns the number of vehicles currently approaching the
     * junction for the given lane.
     * Vehicles are effectively counted or guessed in the space from the sensor.
     * @param[in] lane The lane to count vehicles
     */
    virtual int countVehicles(MSLane* lane) = 0;

    /*
     * Returns the number of vehicles currently approaching the
     * junction for the given lane.
     * Vehicles are effectively counted or guessed in the space from the sensor.
     * @param[in] laneId The lane to count vehicles by ID
     */
    virtual int countVehicles(std::string laneId) = 0;

    /*
     * Returns the average speed of vehicles currently approaching the
     * junction for the given lane.
     * Vehicles speed is effectively sensed or guessed in the space from the sensor.
     * @param[in] lane The lane to count vehicles
     */
    virtual double meanVehiclesSpeed(MSLane* lane) = 0;

    /*
     * Returns the average speed of vehicles currently approaching the
     * junction for the given lane.
     * Vehicles speed is effectively sensed or guessed in the space from the sensor.
     * @param[in] laneId The lane to count vehicles by ID
     */
    virtual double meanVehiclesSpeed(std::string laneId) = 0;

    /*
    * @param[in] laneId The lane given by Id
    * @return The maximum speed allowed for the given laneId
    */
    virtual double getMaxSpeed(std::string laneId) = 0;

    /*
     * @brief Indicate which lane has given green
     * This member is useful to inform the sensor logic about changes in traffic lights,
     * s.t. the logic can better guess the state of lanes accoding to sensors info and
     * traffic lights state.
     * This member has to be specified only by sensor logics with a limited amount of knowledge coming
     * from sensors, like inductor loops. These logics need to know the current phase to guess the number
     * of vehicles waiting in front of a red light.
     */
    virtual void stepChanged(int newStep) {
        currentStep = newStep;
    }
};

#endif
/****************************************************************************/
