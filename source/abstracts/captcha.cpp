#ifdef __has_include
# if __has_include("captcha.hpp")
#   include "captcha.hpp"
#else
#   error "Cell's captcha was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract captcha.
 */
AbstractCaptcha::AbstractCaptcha()
{
}

/*!
 * \brief Destroys the captcha.
 */
AbstractCaptcha::~AbstractCaptcha()
{
}

CELL_NAMESPACE_END
