#if __has_include("email.hpp")
#   include "email.hpp"
#else
#   error "Cell's email was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract Email item.
 */
Email::Email(const Types::Optional<Types::VectorString>& to,
             const Types::Optional<Types::VectorString>& cc,
             const Types::Optional<Types::VectorString>& bcc,
             const Types::OptionalString& from,
             const Types::OptionalString& subject,
             const Types::OptionalString& body,
             const Types::Optional<Types::VectorString>& attachments,
             const Types::OptionalString& htmlBody)
{
}

/*!
 * \brief Destroys the Email.
 */
Email::~Email()
{
}


CELL_NAMESPACE_END
