#ifndef DECODERFACTORY_H 
#define DECODERFACTORY_H
#include <string>

class DecoderInterface;
class DecoderFactory
{
public:
	static DecoderInterface* CreateDecoder(const std::string& strStreamFile);

};
#endif //DECODERFACTORY_H

