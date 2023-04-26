#include "message.hpp"
#include "core/core.hpp"
#include "core/logger.hpp"

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief Constructs message class.
 */
Message::Message()
{
    __cell_safe_instance(m_messageData, MessageData);
}

/*!
 * \brief Destroys the message class.
 */
Message::~Message()
{
    __cell_safe_delete(m_messageData);
}

bool Message::create(const MessageData& messageData) __cell_const_noexcept
{
    if(DeveloperMode::IsEnable)
    {
        Log("Post ID:" + std::to_string(messageData.postId.value()), eLogger::LoggerType::Info);
        Log("Message:" + messageData.message.value(), eLogger::LoggerType::Info);
        Log("Author:" + messageData.author.value(), eLogger::LoggerType::Info);
        switch (messageData.style) {
        case MessageStyle::Information:
            ///ToDo...
            break;
        default:
            break;
        }
    }
    ///ToDo...
    return true;
}

bool Message::edit(const u32 id, const MessageData& messageData) __cell_const_noexcept
{
    ///ToDo...
    return true;
}

bool Message::remove(const u32 id, const MessageData& messageData) __cell_const_noexcept
{
    ///ToDo...
    return true;
}

CELL_NAMESPACE_END

