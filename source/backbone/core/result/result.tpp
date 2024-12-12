#pragma once

#include <memory>
#include <functional>
#include <utility>
#include <tuple>
#include <optional>
#include <source_location>

#include "../error/error.hpp"
#include "../common/helpers.hpp"

// General template for Result
template<typename T>
class [[nodiscard]] Result {
private:
   std::optional<T>     value;
   std::optional<Error> error;

public:
   Result(T value) : value(std::move(value)), error(std::nullopt) {}
   Result(const Error &error) : value(std::nullopt), error(std::move(error)) {}
   Result(T value, const Error &error) : value(std::move(value)), error(std::move(error)) {}

   Result(const Result<T> &other)     = default;
   Result(Result<T> &&other) noexcept = default;
   ~Result()                          = default;

   Result<T> &
   operator=(const Result<T> &other) = default;
   Result<T> &
   operator=(Result<T> &&other) noexcept = default;

   explicit
   operator bool() const {
      return !error.has_value();
   }

   inline T &
   get_value() {
      if (!value.has_value()) {
         throw std::runtime_error("Attempted to access value from an error Result");
      }
      return value.value();
   }

   inline const Error &
   get_error() const {
      if (!error.has_value()) {
         throw std::runtime_error("Attempted to access error from a value Result");
      }
      return error.value();
   }

   inline bool
   is_error() const {
      return error.has_value();
   }

   inline const Result<T> &
   except_fn(const std::function<void(Error)> &handler) const {
      if (is_error()) {
         handler(error.value());
      }
      return *this;
   }

   inline Result<T> &
   except(const std::string &message, std::source_location location = std::source_location::current()) {
      if (is_error()) {
         error->push({ UNDEFINED, message, location });
      }
      return *this;
   }

   inline Result<T> &
   except(ErrorCode            ec,
          const std::string   &message,
          std::source_location location = std::source_location::current()) {
      if (is_error()) {
         error->push({ ec, message, location });
      }
      return *this;
   }

   inline Result<T> &
   with_fallback(const T &fallback) {
      if (!value) {
         value = fallback;
      }
      return *this;
   }

   inline Result<T> &
   panic_if_error(const std::string &title = "") {
      if (is_error()) {
         get_error().panic(title);
      }
      return *this;
   }

   inline std::tuple<std::optional<T>, Ref<Error>>
   as_tuple() const {
      return { value, error };
   }

   inline static Result<T>
   ok(T value) {
      return Result<T>(std::move(value));
   }
};

// Specialization for void
template<>
class [[nodiscard]] Result<void> {
public:
   std::optional<Error> error;

public:
   Result() : error(std::nullopt) {}
   Result(const Error &error) : error(std::move(error)) {}

   Result(const Result<void> &other)     = default;
   Result(Result<void> &&other) noexcept = default;
   ~Result()                             = default;

   Result<void> &
   operator=(const Result<void> &other) = default;
   Result<void> &
   operator=(Result<void> &&other) noexcept = default;

   explicit
   operator bool() const {
      return !error.has_value();
   }

   inline const Error &
   get_error() const {
      if (!error) {
         throw std::runtime_error("Attempted to access error from a value Result");
      }
      return error.value();
   }

   inline bool
   is_error() const {
      return error.has_value();
   }

   inline const Result<void> &
   except_fn(const std::function<void(Error)> &handler) const {
      if (is_error()) {
         handler(error.value());
      }
      return *this;
   }

   inline Result<void> &
   except(const std::string &message, std::source_location location = std::source_location::current()) {
      if (is_error()) {
         error->push({ UNKNOWN, message, location });
      }
      return *this;
   }

   inline Result<void> &
   except(ErrorCode            ec,
          const std::string   &message,
          std::source_location location = std::source_location::current()) {
      if (is_error()) {
         error->push({ ec, message, location });
      }
      return *this;
   }

   inline Result<void> &
   panic_if_error(const std::string &title = "") {
      if (is_error()) {
         get_error().panic(title);
      }
      return *this;
   }

   static Result<void>
   ok() {
      return Result<void>();
   }
};

// Helper function to return Ok() for Result<void>
inline Result<void>
Ok() {
   return Result<void>::ok();
}

using VoidResult = Result<void>;
