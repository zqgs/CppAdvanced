#include "Cl31_PersonImpl.h"


Cl31_PersonImpl::Cl31_PersonImpl(const std::string &Name) 
	:theName(Name)
{
	theName = theName + ",this is Cl31_PersonImpl class";
}


Cl31_PersonImpl::~Cl31_PersonImpl()
{

}


std::string Cl31_PersonImpl::name() const
{
	return theName;
}