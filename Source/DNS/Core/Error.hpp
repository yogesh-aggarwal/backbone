#pragma once

#include <string>
#include <vector>
#include <source_location>

enum ErrorCode
{
   /* Generic Error Codes */

   Undefined = -1,
   Unknown   = 0x00,

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

   STEVE_CRITICAL_ERROR,

   /* Application Error Codes */
   STEVE_APPLICATION_INITIALIZATION_FAILED,
   STEVE_APPLICATION_RENDER_FAILED,
   STEVE_APPLICATION_WINDOW_CREATION_FAILED,
   STEVE_APPLICATION_WINDOW_NOT_INITIALIZED,
   STEVE_APPLICATION_WINDOW_ALREADY_RUNNING,
   STEVE_APPLICATION_WINDOW_GLAD_OPENGL_INITIALIZATION_FAILED,
   STEVE_APPLICATION_WINDOW_LIFECYCLE_NOT_PROVIDED,

   /* Shader Error Codes */
   STEVE_SHADER_PROGRAM_INITIALIZE_FAILED,
   STEVE_SHADER_PROGRAM_NOT_INITIALIZED,
   STEVE_SHADER_PROGRAM_UNIFORM_NOT_FOUND,
   STEVE_SHADER_INTIALIZE_FROM_FILE_FAILED,
   STEVE_SHADER_COMPILE_FAILED,
   STEVE_SHADER_INVALID_TYPE,

   /* Objects Error Codes */
   STEVE_OBJECTS_VERTEX_BUFFER_NOT_INITIALIZED,
   STEVE_OBJECTS_VERTEX_BUFFER_TOO_MANY_VERTICES,

   /* Renderer Error Codes */
   STEVE_RENDERER_NOT_INITIALIZED,
   STEVE_RENDERER_STATE_INITIALIZATION_FAILED,
   STEVE_RENDERER_SCENE_ALREADY_BEGUN,
   STEVE_RENDERER_SCENE_HAS_NOT_BEGUN,
   STEVE_RENDERER_NO_VERTICES_TO_RENDER,
};

class ErrorUnit
{
private:
   ErrorCode            m_Code;
   std::string          m_Message;
   std::source_location m_Location;

public:
   ErrorUnit(ErrorCode            code,
             std::source_location location = std::source_location::current());
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

class Error
{
private:
   std::vector<ErrorUnit> m_Errors;

public:
   Error();
   Error(const ErrorUnit &unit);
   Error(const std::vector<ErrorUnit> &errors);

   void
   Push(const ErrorUnit &unit);

   void
   Clear();

   operator bool() const;

   const ErrorUnit &
   First() const;

   const ErrorUnit &
   Last() const;

   void
   Print(const std::string &title = "") const;

   void
   Raise() const;

private:
   void
   PrintAtCenter(int         shellColumns,
                 std::string message,
                 std::string startDecorator   = "",
                 std::string endDecorator     = "",
                 bool        separatorAtStart = false,
                 bool        separatorAtEnd   = false) const;
};