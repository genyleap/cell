#if __has_include("share.hpp")
#   include "share.hpp"
#else
#   error "Cell's "share.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief Constructs an abstract share class.
 */
Share::Share()
{
    __cell_safe_instance(m_shareData, ShareData);
}

/*!
 * \brief Destroys the share class.
 */
Share::~Share()
{
    __cell_safe_delete(m_shareData);
}

void Share::registerToShare(const ShareData &shareData) const noexcept
{
    //Test link...
    std::cout << shareData.link.value() << std::endl;

    switch (shareData.method) {
    case ShareMethod::InSelf:
        ///ToDo...
        break;
    case ShareMethod::SocialNetwork:
        ///ToDo...
        break;
    case ShareMethod::ByEmail:
        ///ToDo...
        break;
    case ShareMethod::BySms:
        ///ToDo...
        break;
    case ShareMethod::ForApi:
        ///ToDo...
        break;
    case ShareMethod::Custom:
        ///ToDo...
        break;
    default:
        break;
    }
}

CELL_NAMESPACE_END

