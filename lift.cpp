#include "lift.hpp"
#include <iostream>

const double Lift::MAX_LOAD = 250.0;

Lift::Lift() {
    Reset();
}

void Lift::Reset() {
    gState = STATE_IDLE;
    eState = ENGINE_OFF;
    dState = DOORS_OPEN;
    currentFloor = 1;
    targetFloor = 1;
    currentLoad = 0.0;
}

void Lift::updateEngineState() {
    if (targetFloor > currentFloor) {
        eState = ENGINE_UP;
    } else if (targetFloor < currentFloor) {
        eState = ENGINE_DOWN;
    } else {
        eState = ENGINE_OFF;
    }
}

bool Lift::isLoadValid() {
    return (currentLoad > 0 && currentLoad <= MAX_LOAD);
}

void Lift::StartCall(int destinationFloor) {
    if (destinationFloor < MIN_FLOOR || destinationFloor > MAX_FLOOR) {
        return;
    }
    dState = DOORS_CLOSED;
    targetFloor = destinationFloor;
    updateEngineState();
    gState = STATE_CALLED;
}

void Lift::EndCall() {
    eState = ENGINE_OFF;
    currentFloor = targetFloor;
    dState = DOORS_OPEN;
    gState = STATE_IDLE;
}

void Lift::LoadCabin(double load) {
    if (load < 0) {
        currentLoad = 0;
    } else if (load > MAX_LOAD) {
        currentLoad = MAX_LOAD;
    } else {
        currentLoad = load;
    }
}

void Lift::Start(int destinationFloor) {
    if (isLoadValid()) {
        if (destinationFloor < MIN_FLOOR || destinationFloor > MAX_FLOOR) {
            return;
        }
        dState = DOORS_CLOSED;
        targetFloor = destinationFloor;
        updateEngineState();
        gState = STATE_MOVING;
    }
}

void Lift::Stop() {
    eState = ENGINE_OFF;
    currentFloor = targetFloor;
    dState = DOORS_OPEN;
    gState = STATE_IDLE;
}

Lift& Lift::operator+=(double load) {
    LoadCabin(load);
    return *this;
}

Lift& Lift::operator()(int floor) {
    if (floor >= MIN_FLOOR && floor <= MAX_FLOOR) {
        targetFloor = floor;
    }
    return *this;
}

Lift& Lift::operator++() {           // префіксний ++
    StartCall(targetFloor);
    return *this;
}

Lift& Lift::operator--() {           // префіксний --
    EndCall();
    return *this;
}

GeneralState Lift::GetGeneralState() const { return gState; }
EngineState Lift::GetEngineState() const { return eState; }
DoorState Lift::GetDoorState() const { return dState; }
int Lift::GetCurrentFloor() const { return currentFloor; }
int Lift::GetTargetFloor() const { return targetFloor; }
double Lift::GetCurrentLoad() const { return currentLoad; }

const char* Lift::GetGeneralStateName() const {
    switch (gState) {
        case STATE_IDLE:     return "Простій";
        case STATE_CALLED:   return "Виклик";
        case STATE_MOVING:   return "Перевезення";
        default:             return "N/A";
    }
}

const char* Lift::GetEngineStateName() const {
    switch (eState) {
        case ENGINE_OFF:     return "Вимкнено";
        case ENGINE_UP:      return "Підйом";
        case ENGINE_DOWN:    return "Спуск";
        default:             return "N/A";
    }
}

const char* Lift::GetDoorStateName() const {
    switch (dState) {
        case DOORS_OPEN:     return "Відчинені";
        case DOORS_CLOSED:   return "Зачинені";
        default:             return "N/A";
    }
}
