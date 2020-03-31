#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <Arduino.h>

class Motors
{
  public:
    Motors(const unsigned int PinMotorA_Value, const unsigned int PinMotorA_in1, const unsigned int PinMotorA_in2,
    const unsigned int PinMotorB_Value, const unsigned int PinMotorB_in1, const unsigned int PinMotorB_in2,
    const unsigned int Pin_STBY)
    {      
      m_PinMotorA_Value = PinMotorA_Value;
      m_PinMotorB_Value = PinMotorB_Value;
      m_PinMotorA_in1 = PinMotorA_in1;
      m_PinMotorA_in2 = PinMotorA_in2;
      m_PinMotorB_in1 = PinMotorB_in1;
      m_PinMotorB_in2 = PinMotorB_in2;
      m_Pin_STBY = Pin_STBY;
    
      pinMode( m_PinMotorA_Value, OUTPUT);
      pinMode( m_PinMotorB_Value, OUTPUT);
      pinMode( m_PinMotorA_in1, OUTPUT);
      pinMode( m_PinMotorA_in2, OUTPUT);
      pinMode( m_PinMotorB_in1, OUTPUT);
      pinMode( m_PinMotorB_in2, OUTPUT);
      pinMode( m_Pin_STBY, OUTPUT);

      //init en mode standby      
      Stop();
      CurenteSpeed_A = 0;
      CurenteSpeed_B = 0;
    }
    
    ~Motors(void){};

    void Start(void) { digitalWrite(m_Pin_STBY, HIGH);};
    void Stop(void) { digitalWrite(m_Pin_STBY, LOW);};

    void Vitess(const int VitessA, const int VitessB)
    {     
        if(CurenteSpeed_A != VitessA)
        {
            if(VitessA>0)
            {
                digitalWrite(m_PinMotorA_in1, LOW);
                digitalWrite(m_PinMotorA_in2, HIGH);
            }
            else
            {
                digitalWrite(m_PinMotorA_in1, HIGH);
                digitalWrite(m_PinMotorA_in2, LOW);
            }
            analogWrite(m_PinMotorA_Value, min(abs(VitessA),255));
            CurenteSpeed_A = VitessA;
        }
        if(CurenteSpeed_B != VitessB)
        {
            if(VitessB>0)
            {
                digitalWrite(m_PinMotorB_in1, LOW);
                digitalWrite(m_PinMotorB_in2, HIGH);
            }
            else
            {
                digitalWrite(m_PinMotorB_in1, HIGH);
                digitalWrite(m_PinMotorB_in2, LOW);
            }  
            analogWrite(m_PinMotorB_Value, min(abs(VitessB),255));    
            CurenteSpeed_B = VitessB;
        }  
    }    
       
  private:

    unsigned int m_PinMotorA_Value, m_PinMotorB_Value;
    unsigned int m_PinMotorA_in1, m_PinMotorA_in2;
    unsigned int m_PinMotorB_in1, m_PinMotorB_in2;
    unsigned int m_Pin_STBY;

    int CurenteSpeed_A, CurenteSpeed_B;
};

#endif
