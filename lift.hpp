#ifndef LIFT_HPP
#define LIFT_HPP

enum GeneralState {
    STATE_IDLE,
    STATE_CALLED,
    STATE_MOVING
};

enum EngineState {
    ENGINE_OFF,
    ENGINE_UP,
    ENGINE_DOWN
};

enum DoorState {
    DOORS_OPEN,
    DOORS_CLOSED
}; // <--- Перевірте, що цей знак ";" є у вас!

class Lift {
private:
    GeneralState gState;
    EngineState eState;
    DoorState dState;
    int currentFloor;
    int targetFloor;
    double currentLoad;

    static const int MIN_FLOOR = 1;
    static const int MAX_FLOOR = 24;
    // static const double MAX_LOAD; // У старих версіях це краще винести

    void updateEngineState();
    bool isLoadValid();

public:
    static const double MAX_LOAD; // Винесемо константу сюди, щоб не сварився старий компілятор

    Lift();
    void Reset();

    void StartCall(int destinationFloor);
    void EndCall();
    void LoadCabin(double load);
    void Start(int destinationFloor);
    void Stop();

    // Геттери
    GeneralState GetGeneralState() const;
    EngineState GetEngineState() const;
    DoorState GetDoorState() const;
    int GetCurrentFloor() const;
    int GetTargetFloor() const;
    double GetCurrentLoad() const;

    const char* GetGeneralStateName() const;
    const char* GetEngineStateName() const;
    const char* GetDoorStateName() const;

    // Перевантажені оператори
    Lift& operator+=(double load);
    Lift& operator()(int floor);
    Lift& operator++();
    Lift& operator--();
};

#endif
