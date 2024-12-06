#pragma once

#include <string>
#include <vector>
#include <source_location>

enum ErrorCode {
   /* Generic Error Codes */

   UNDEFINED = -1,
   UNKNOWN   = 0x0,

   /* Buffer Codes */
   OUT_OF_BOUNDS = 0x1,
   FAILED_TO_READ_QNAME,
   FAILED_TO_READ_LABEL,

   /* Packet Error Codes */
   FAILED_TO_PARSE_HEADER = 0x2,
   FAILED_TO_WRITE_HEADER,
   FAILED_TO_PARSE_QUESTION,
   FAILED_TO_WRITE_QUESTION,
   FAILED_TO_PARSE_RECORD,
   FAILED_TO_WRITE_RECORD,
};

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

class Error {
private:
   std::vector<ErrorUnit> m_Errors;

public:
   Error();
   Error(const ErrorUnit &unit);
   explicit Error(const std::vector<ErrorUnit> &errors);

   void
   push(const ErrorUnit &unit);

   void
   clear();

   operator bool() const;

   const ErrorUnit &
   first() const;

   const ErrorUnit &
   last() const;

   void
   print(const std::string &title = "") const;

   void
   panic() const;
};
