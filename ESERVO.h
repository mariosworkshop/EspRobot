#pragma once

class ESERVO{

  private:
    short _minPosition;
    short _maxPosition;
    short _defaultPosition;
    short _actualPosition;

    short _pin;

  public:
    ESERVO(short pin, short minPos, short maxPos, short defaultPos);

    void setActualPos(short pos){_actualPosition = pos;}

    short getPin(){return _pin;}
    short getActualPos(){return _actualPosition;}
    short getMinPos(){return _minPosition;}
    short getMaxPos(){return _maxPosition;}
    short getDefaultPos(){return _defaultPosition;}

    ~ESERVO();
};
