/*!
 * @file        tags.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Tags structure for contents.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_TAGS_HPP
#define CELL_TAGS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

struct TagsData __cell_final
{
    Types::OptionalNumeric id     {};
    Types::OptionalString  title  {};
};

using TagList = std::vector<TagsData>;

/*!
 * \brief The AbstractTags class
 */
class __cell_export Tags
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Tags)

    /*!
     * \brief registerTag function will sets data in tag list.
     * \param tag is a type of tag.
     */
    void registerTag(const TagsData& tag) __cell_const_noexcept;

    /*!
     * \brief getTags function will gets tag data.
     * \returns tags by detail.
     */
    __cell_no_discard TagsData getTags() __cell_const_noexcept;

    /*!
     * \brief getList function will gets all tags in list type.
     * \returns list of tags.
     */
    __cell_no_discard TagList getList() __cell_const_noexcept;

    /*!
     * \brief removeTag function will removes a tag.
     * \param tag as id as u32.
     * \returns as boolean.
     */
    __cell_no_discard bool removeTag(const Types::u32 id) __cell_const_noexcept;

    /*!
     * \brief updateTag function will updates (edit) current tag by id or name.
     * \param id
     * \param tag
     * \returns boolean.
     */
    __cell_no_discard bool updateTag(const Types::u32 id, const TagsData& tag) __cell_const_noexcept;

protected:
    /*!
     * \brief insertIntoDb function will inserts all data into database.
     * \param tag as Tags data.
     */
    __cell_no_discard bool insertIntoDb(const TagsData& tag) __cell_const_noexcept;

private:
    CELL_DISABLE_COPY(Tags)
    TagsData* m_tagsData;
    TagList* m_tagList;
};

CELL_NAMESPACE_END

#endif  // CELL_TAGS_HPP
