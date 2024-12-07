#pragma once

#define RETURN_IF_ERROR(result)  \
   if (result.is_error()) {      \
      return result.get_error(); \
   }
