#include "error.hpp"

#include <cmath>
#include <iostream>
#include <string>

#include <backbone/core/helpers.hpp>

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(ErrorCode code, std::source_location location)
    : m_Code(code), m_Message(""), m_Location(location) {}

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(std::string message, std::source_location location)
    : m_Code(Undefined), m_Message(std::move(message)), m_Location(location) {}

/* ------------------------------------------------------------------------------------------------------- */

ErrorUnit::ErrorUnit(ErrorCode code, std::string message, std::source_location location)
    : m_Code(code), m_Message(std::move(message)), m_Location(location) {}

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

Error::Error() : m_Errors() {}

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(const ErrorUnit &unit) { m_Errors.push_back(unit); }

/* ------------------------------------------------------------------------------------------------------- */

Error::Error(const std::vector<ErrorUnit> &errors) : m_Errors(errors) {}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::Push(const ErrorUnit &unit) {
   m_Errors.push_back(unit);
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::Clear() {
   m_Errors.clear();
}

/* ------------------------------------------------------------------------------------------------------- */

Error::operator bool() const { return m_Errors.size() > 0; }

/* ------------------------------------------------------------------------------------------------------- */

const ErrorUnit &
Error::First() const {
   return m_Errors[0];
}

/* ------------------------------------------------------------------------------------------------------- */

const ErrorUnit &
Error::Last() const {
   return m_Errors[m_Errors.size() - 1];
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::Print(const std::string &title) const {
   const int shellColumns = GetShellColumns();

   /* Print instructions on how to read the error trace */
   PrintSeparator();

   char instructions[100];
   sprintf(instructions,
           "(1) = Bottom most layer   &   (%d) = Top most layer",
           static_cast<int>(m_Errors.size()));
   PrintAtCenter(instructions, "|*--*[", "]*--*|");

   /* Print separator */
   printf("%s", std::string(shellColumns, '-').c_str());

   /* Print block's header */
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

   /* Print separator */
   printf("\n");
   PrintSeparator();
   printf("\n");
}

/* ------------------------------------------------------------------------------------------------------- */

void
Error::Raise() const {
   throw *this;
}

/* ------------------------------------------------------------------------------------------------------- */
