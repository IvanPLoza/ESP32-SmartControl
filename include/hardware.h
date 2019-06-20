#include <main.h>
#include "SPIFFS.h"
#include <ringDisplay.h>

class hardwareConfiguration{

    public:

    void init(void);
    void printStatus(void);
};

extern hardwareConfiguration hardware;