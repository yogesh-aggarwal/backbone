#pragma once

#include <memory>
#include <functional>
#include <utility>
#include <tuple>

#include <backbone/core/error.hpp>
#include <backbone/core/helpers.hpp>

// General template for Result
template<typename T>
class [[nodiscard]] Result {
private:
   std::optional<T> value;
   Ref<Error>       error;

public:
   Result(T value) : value(std::move(value)), error(nullptr) {}
   Result(const Error &error) : value(std::nullopt), error(std::make_shared<Error>(error)) {}
   Result(Ref<Error> error) : value(std::nullopt), error(std::move(error)) {}
   Result(T value, Ref<Error> error) : value(std::move(value)), error(std::move(error)) {}

   Result(const Result<T> &other)     = default;
   Result(Result<T> &&other) noexcept = default;
   ~Result()                          = default;

   Result<T> &
   operator=(const Result<T> &other) = default;
   Result<T> &
   operator=(Result<T> &&other) noexcept = default;

   explicit
   operator bool() const {
      return !error || !*error;
   }

   const T &
   get_value() const {
      if (!value) {
         throw std::runtime_error("Attempted to access value from an error Result");
      }
      return *value;
   }

   const Ref<Error> &
   get_error() const {
      return error;
   }

   bool
   is_error() const {
      return !*this;
   }

   const Result<T> &
   with_catch_fn(const std::function<void(Ref<Error>)> &handler) const {
      if (error) {
         handler(error);
      }
      return *this;
   }

   Result<T> &
   with_catch(const ErrorUnit &eu) {
      if (error) {
         error->Push(eu);
      } else {
         error = std::make_shared<Error>(eu);
      }
      return *this;
   }

   Result<T> &
   with_fallback(const T &fallback) {
      if (!value) {
         value = fallback;
      }
      return *this;
   }

   std::tuple<std::optional<T>, Ref<Error>>
   as_tuple() const {
      return { value, error };
   }

   static Result<T>
   ok(T value) {
      return Result<T>(std::move(value));
   }
};

// Specialization for void
template<>
class [[nodiscard]] Result<void> {
public:
   Ref<Error> error;

public:
   Result() : error(nullptr) {}
   Result(const Error &error) : error(std::make_shared<Error>(error)) {}
   Result(Ref<Error> error) : error(std::move(error)) {}

   Result(const Result<void> &other)     = default;
   Result(Result<void> &&other) noexcept = default;
   ~Result()                             = default;

   Result<void> &
   operator=(const Result<void> &other) = default;
   Result<void> &
   operator=(Result<void> &&other) noexcept = default;

   explicit
   operator bool() const {
      return !error || !*error;
   }

   const Ref<Error> &
   get_error() const {
      return error;
   }

   bool
   is_error() const {
      return !*this;
   }

   const Result<void> &
   with_catch_fn(const std::function<void(Ref<Error>)> &handler) const {
      if (error) {
         handler(error);
      }
      return *this;
   }

   Result<void> &
   with_catch(const ErrorUnit &eu) {
      if (error) {
         error->Push(eu);
      } else {
         error = std::make_shared<Error>(eu);
      }
      return *this;
   }

   static Result<void>
   ok() {
      return Result<void>();
   }
};
