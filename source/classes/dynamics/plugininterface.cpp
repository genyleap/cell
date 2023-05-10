#include "plugininterface.hpp"

class PluginInterfaceImpl
{
public:
    PluginInterfaceData pInterfaceData;
};

PluginInterface::PluginInterface()
{
    __cell_smart_instance(pImplPtr, PluginInterfaceImpl);
}

PluginInterface::~PluginInterface()
{
  pImplPtr->pInterfaceData.nameList.clear();
}

CreateSingletonInstance(PluginInterface)

void PluginInterface::addDetail(const PluginList& plist)
{
  pImplPtr->pInterfaceData.pluginList = plist;
}

void PluginInterface::addName(const std::string& name)
{
  pImplPtr->pInterfaceData.nameList.push_back(name);
}

void PluginInterface::setError(const std::string &var)
{
  pImplPtr->pInterfaceData.errors.push_back(var);
}

const NameList& PluginInterface::getNames() const
{
  return pImplPtr->pInterfaceData.nameList;
}

const PluginList& PluginInterface::getDetail() const
{
  return pImplPtr->pInterfaceData.pluginList;
}

const ErrorString& PluginInterface::getErrors() const
{
  return pImplPtr->pInterfaceData.errors;
}
