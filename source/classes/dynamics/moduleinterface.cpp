#include "moduleinterface.hpp"

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

class ModuleInterfaceImpl
{
public:
    ModuleInterfaceData pInterfaceData;
};

ModuleInterface::ModuleInterface()
{
    __cell_smart_instance(pImplPtr, ModuleInterfaceImpl);
}

ModuleInterface::~ModuleInterface()
{
  pImplPtr->pInterfaceData.nameList.clear();
}

CreateSingletonInstance(ModuleInterface)

void ModuleInterface::addDetail(const ModuleList& plist)
{
  pImplPtr->pInterfaceData.moduleList = plist;
}

void ModuleInterface::addName(const std::string& name)
{
  pImplPtr->pInterfaceData.nameList.push_back(name);
}

void ModuleInterface::setError(const std::string &var)
{
  pImplPtr->pInterfaceData.errors.push_back(var);
}

const NameList& ModuleInterface::getNames() const
{
  return pImplPtr->pInterfaceData.nameList;
}

const ModuleList& ModuleInterface::getDetail() const
{
  return pImplPtr->pInterfaceData.moduleList;
}

const ErrorString& ModuleInterface::getErrors() const
{
  return pImplPtr->pInterfaceData.errors;
}

CELL_NAMESPACE_END
