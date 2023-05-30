//! Cell's Usermanager.
#if __has_include(<abstracts/usermanager>)
#   include <abstracts/usermanager>
#else
#   error "Cell's usermanager was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

/*!
 * \brief Constructs an abstract user manager.
 */
AbstractUserManager::AbstractUserManager()
{
    __cell_safe_instance(dataTransferPtr, DataTransfer);
    __cell_safe_instance(dataTransferPtr->userDataPtr, UserData);
}

/*!
 * \brief Constructs an abstract user manager.
 */
AbstractUserManager::AbstractUserManager(const UserData& userData)
{
    __cell_safe_instance(dataTransferPtr, DataTransfer);
    __cell_safe_instance_rhs(dataTransferPtr->userDataPtr, UserData, userData);
}

/*!
 * \brief Destroys the usermanager.
 */
AbstractUserManager::~AbstractUserManager()
{
    __cell_safe_delete(dataTransferPtr);
    __cell_safe_delete(dataTransferPtr->userDataPtr);
}

CELL_NAMESPACE_END
