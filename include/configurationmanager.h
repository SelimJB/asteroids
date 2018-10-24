#include "yaml-cpp/yaml.h"


class ConfigurationManager{
	private:
	YAML::Node config;
	public:
	ConfigurationManager();
	template<typename T>
	T GetFirstNodeValue(const char *str){
		return config[str].as<T>();
	}
};