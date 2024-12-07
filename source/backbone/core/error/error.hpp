#pragma once

#include <string>
#include <vector>
#include <source_location>

#include "unit.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class Error {
private:
   std::vector<ErrorUnit> m_Errors;

public:
   Error();
   Error(const ErrorUnit &unit);
   Error(std::string message, std::source_location location = std::source_location::current());
   explicit Error(const std::vector<ErrorUnit> &errors);
   explicit Error(ErrorCode code, std::source_location location = std::source_location::current());
   explicit Error(ErrorCode            code,
                  std::string          message,
                  std::source_location location = std::source_location::current());

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
   panic(const std::string &title = "") const;
};

/* ------------------------------------------------------------------------------------------------------- */
