#pragma once

#include <string>
#include <vector>
#include <source_location>

enum ErrorCode {
   /* Generic Error Codes */

   UNDEFINED = -1,
   Unknown   = 0x00,

   /* Buffer Codes */
   OUT_OF_BOUNDS = 0x01,

   /* Packet Error Codes */
   FAILED_TO_PARSE_HEADER = 0x2,

   /* Syscalls Error Codes */

   FILE_IO             = EIO,
   FILE_NOT_FOUND      = ENOENT,
   FILE_ALREADY_EXISTS = EEXIST,

   OPERATION_NOT_PERMITTED = EPERM,

   MKDIR_FAILED  = EACCES,
   MKDIR_EXISTED = EEXIST,

   MOUNT_FAILED      = EACCES,
   MOUNT_BIND_FAILED = EACCES,

   RMDIR_FAILED = EACCES,

   /* Reset the enum counter */

   STEVE_ERROR = 1 << 24,

   /* Utility Error Codes */

   DNS_CRITICAL_ERROR,

   /* Packet buffer */

   DNS_PACKETBUFFER_OVERFLOW,
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
   raise() const;
};