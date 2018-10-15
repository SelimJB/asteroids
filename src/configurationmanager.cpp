#include "configurationmanager.h"
#include <iostream>

using namespace std;
ConfigurationManager::ConfigurationManager(){
	config = YAML::LoadFile("config.yaml");
}
