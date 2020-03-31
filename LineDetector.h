#include <Arduino.h>

class LineDetector
{
  public : 
//constructeur :
    LineDetector(const unsigned int PINRightSensor, const unsigned int PINCenterSensor, const unsigned int PINLeftSensor)
    {
      m_nRightSensor_PIN = PINRightSensor;
      m_nCenterSensor_PIN = PINCenterSensor;
      m_nLeftSensor_PIN = PINLeftSensor;

      pinMode(m_nRightSensor_PIN, INPUT); 
      pinMode(m_nCenterSensor_PIN, INPUT);
      pinMode(m_nLeftSensor_PIN, INPUT);
  
      m_bRightSensor_Value = false;
      m_bCenterSensor_Value = false;
      m_bLeftSensor_Value = false;
    };
    
// Destructeur :
    ~LineDetector(void){};

//Fonctions :
  void ReadSensors(void)
  {
    m_bRightSensor_Value = digitalRead(m_nRightSensor_PIN);
    m_bCenterSensor_Value = digitalRead(m_nCenterSensor_PIN);
    m_bLeftSensor_Value = digitalRead(m_nLeftSensor_PIN);
  };
    
    bool getRightSensorValue(void)
    {
      return m_bRightSensor_Value;
    };

    bool getCenterSensorValue(void)
    {
      return m_bCenterSensor_Value;
    };

    bool getLeftSensorValue(void)
    {
      return m_bLeftSensor_Value;
    };


  private :
    int m_nRightSensor_PIN;
    int m_nCenterSensor_PIN;
    int m_nLeftSensor_PIN;
    bool m_bRightSensor_Value;
    bool m_bCenterSensor_Value;
    bool m_bLeftSensor_Value;
};
