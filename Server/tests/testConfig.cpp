#include "config.h"
#include "log.h"

Tao::ConfigVar<int>::ptr gIntValueConfig = Tao::Config::Lookup("system.port", (int)8080, "systemport");

int main(int argc, char** argv){
    TAO_LOG_INFO(TAO_LOG_ROOT() ) << gIntValueConfig->getValue();
    TAO_LOG_INFO(TAO_LOG_ROOT() ) << gIntValueConfig->toString();
    return 0;
}