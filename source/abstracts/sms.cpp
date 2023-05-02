#ifdef __has_include
# if __has_include("sms.hpp")
#   include "sms.hpp"
#else
#   error "Cell's Sms was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

Sms::Sms(const Types::Optional<Types::VectorString>& to,
    const Types::Optional<Types::VectorString>& cc,
    const Types::Optional<Types::VectorString>& bcc,
    const Types::OptionalString& from,
    const Types::OptionalString& body)
{
}

Sms::~Sms()
{
}

CELL_NAMESPACE_END
