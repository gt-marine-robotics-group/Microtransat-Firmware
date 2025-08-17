#ifindef MAG_ENCODER_H
#define MAG_ENCODER_H

#include <Arduino.h>
#include <AS5600.h>

class MagEncoder {
    private:
        AS5600 as5600; 
    
    public:
        void begin();
        

}