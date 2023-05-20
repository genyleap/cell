#if __has_include("tags.hpp")
#   include "tags.hpp"
#else
#   error "Cell's "tags.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief Constructs an abstract tags class.
 */
Tags::Tags()
{
    __cell_safe_instance(m_tagsData, TagsData);
    __cell_safe_instance(m_tagList, TagList);
}

/*!
 * \brief Destroys the tags class.
 */
Tags::~Tags()
{
    __cell_safe_delete(m_tagsData);
    __cell_safe_delete(m_tagList);
}

void Tags::registerTag(const TagsData& tag) __cell_const_noexcept
{
    {
        m_tagsData->id = tag.id;
        m_tagsData->title = tag.title;
    }
    //For tag list
    if(insertIntoDb(tag))
        m_tagList->push_back(tag);
    ///ToDo...
}

TagsData Tags::getTags() __cell_const_noexcept
{
    return *m_tagsData;
}

TagList Tags::getList() __cell_const_noexcept
{
    return *m_tagList;
}

bool Tags::removeTag(const u32 id) __cell_const_noexcept
{
    ///ToDo...
    return false;
}

bool Tags::updateTag(const u32 id, const TagsData &tag) __cell_const_noexcept
{
    ///ToDo...
    return false;
}

bool Tags::insertIntoDb(const TagsData& tag) __cell_const_noexcept
{
    ///ToDo...
    return true;
}

CELL_NAMESPACE_END
