#include "Cl31_PersonExp2.h"
#include "Cl31_PersonImpl.h"

Cl31_PersonExp2::Cl31_PersonExp2(const std::string &Name)
{
	pImpl = std::make_shared<Cl31_PersonImpl>(Name);
}


Cl31_PersonExp2::~Cl31_PersonExp2()
{

}
std::string Cl31_PersonExp2::name() const
{
	return pImpl->name();
}