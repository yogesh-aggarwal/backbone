#pragma once

#include <string>
#include <source_location>

#include "codes.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class ErrorUnit {
private:
   ErrorCode            m_Code;
   std::string          m_Message;
   std::source_location m_Location;

public:
   ErrorUnit(ErrorCode code, std::source_location location = std::source_location::current());
   ErrorUnit(std::string message, std::source_location location = std::source_location::current());
   ErrorUnit(ErrorCode            code,
             std::string          message,
             std::source_location location = std::source_location::current());

   ErrorCode
   GetCode() const;

   std::string
   GetMessage() const;

   const std::source_location &
   GetLocation() const;

   operator std::string() const;
};

/* ------------------------------------------------------------------------------------------------------- */
