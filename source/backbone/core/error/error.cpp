#include "error.hpp"

#include <cmath>
#include <iostream>
#include <string>

#include <backbone/core/common/helpers.hpp>

/* ------------------------------------------------------------------------------------------------------- */

Error::Error() : m_Errors() {}

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(const ErrorUnit &unit) { m_Errors.push_back(unit); }

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(const std::vector<ErrorUnit> &errors) : m_Errors(errors) {}

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(std::string message, std::source_location location) {
   m_Errors.push_back(ErrorUnit(message.c_str(), location));
}

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(ErrorCode code, std::source_location location) { m_Errors.push_back(ErrorUnit(code, location)); }

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(ErrorCode code, std::string message, std::source_location location) {
   m_Errors.push_back(ErrorUnit(code, message.c_str(), location));
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::push(const ErrorUnit &unit) {
   m_Errors.push_back(unit);
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::clear() {
   m_Errors.clear();
}

/* ------------------------------------------------------------------------------------------------------- */

Error::operator bool() const { return m_Errors.size() > 0; }

/* ------------------------------------------------------------------------------------------------------- */

const ErrorUnit &
Error::first() const {
   return m_Errors[0];
}

/* ------------------------------------------------------------------------------------------------------- */

const ErrorUnit &
Error::last() const {
   return m_Errors[m_Errors.size() - 1];
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::print(const std::string &title) const {
   const int shellColumns = GetShellColumns();

   /* print instructions on how to read the error trace */
   PrintSeparator();

   char instructions[100];
   sprintf(instructions,
           "(1) = Bottom most layer   &   (%d) = Top most layer",
           static_cast<int>(m_Errors.size()));
   PrintAtCenter(instructions, "|*--*[", "]*--*|");

   /* print separator */
   printf("%s", std::string(shellColumns, '-').c_str());

   /* print block's header */
   if (title.size() > 0) {
      PrintAtCenter(title, "[", "]", false, true);
   }

   for (int i = 0; i < m_Errors.size(); i++) {
      const auto &error = m_Errors[i];

      int indent = 1                    // (
                   + 2                  // "00"
                   + log10(i + 1) + 1   // i + 1
                   + 1                  // )
                   + 1;                 // ' '

      printf("\n(%03d) [E:%d] %s:%d:%d\n%s\"%s\"",
             i + 1,
             error.GetCode(),
             error.GetLocation().file_name(),
             error.GetLocation().line(),
             error.GetLocation().column(),
             std::string(indent, ' ').c_str(),
             //  "error str"
             error.GetMessage().c_str());
   }

   /* print separator */
   printf("\n");
   PrintSeparator();
   printf("\n");
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::panic(const std::string &title) const {
   print(title);
   exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------------------------------------- */
