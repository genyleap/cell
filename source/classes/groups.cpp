//! Cell's Groups.
#ifdef __has_include
# if __has_include("groups.hpp")
#   include "groups.hpp"
#else
#   error "Cell's groups was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Abstracts;
CELL_USING_NAMESPACE Cell::Abstracts::Account;

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief Constructs an abstract groups class.
 */
Groups::Groups()
{
    __cell_safe_instance(m_groupData, GroupData);
}

/*!
 * \brief Destroys the groups class.
 */
Groups::~Groups()
{
    __cell_safe_delete(m_groupData);
}


bool Groups::add(const GroupData& groupData) __cell_const_noexcept
{
  ///ToDo...
}

bool Groups::edit(const u32 id, const GroupData& groupData) __cell_const_noexcept
{
  ///ToDo...
}

bool Groups::remove(const u32 id) __cell_const_noexcept
{
  ///ToDo...
}

GroupData Groups::get(const u32 id) __cell_const_noexcept
{
    //m_groupData->....;
    ///ToDo...
    return *m_groupData;
}

CELL_NAMESPACE_END
