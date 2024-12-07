#include "unit.hpp"

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(ErrorCode code, std::source_location location)
    : m_Code(code), m_Message(""), m_Location(location) {}

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(std::string message, std::source_location location)
    : m_Code(UNDEFINED), m_Message(message), m_Location(location) {}

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(ErrorCode code, std::string message, std::source_location location)
    : m_Code(code), m_Message(message), m_Location(location) {}

/* ------------------------------------------------------------------------------------------------------- */

ErrorCode
ErrorUnit::GetCode() const {
   return m_Code;
}

/* ------------------------------------------------------------------------------------------------------- */

std::string
ErrorUnit::GetMessage() const {
   return m_Message;
}

/* ------------------------------------------------------------------------------------------------------- */

const std::source_location &
ErrorUnit::GetLocation() const {
   return m_Location;
}

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::operator std::string() const { return m_Message; }

/* ------------------------------------------------------------------------------------------------------- */
