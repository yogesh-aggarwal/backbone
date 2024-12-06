#pragma once

#include <cstdint>

#include <backbone/core/pch>
#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class PacketHeader {
public:
   enum ResultCode {
      NO_ERROR        = 0,
      FORMAT_ERROR    = 1,
      SERVER_FAILURE  = 2,
      NAME_ERROR      = 3,
      NOT_IMPLEMENTED = 4,
      REFUSED         = 5,
      RESERVED1       = 6,
      RESERVED2       = 7,
      RESERVED3       = 8,
      RESERVED4       = 9,
      RESERVED5       = 10,
      RESERVED6       = 11,
      RESERVED7       = 12,
      RESERVED8       = 13,
      RESERVED9       = 14,
      RESERVED10      = 15,
   };

public:
   /**
    * 16-bits
    *
    * - A random identifier is assigned to query packets.
    * - Response packets must reply with the same id.
    * - This is needed to differentiate responses due to the stateless nature of UDP.
    */
   uint16_t id;

   /**
    * 1-bit
    *
    * - 0: Query
    * - 1: Response
    */
   bool query_response;

   /**
    * 4-bits
    *
    * Typically always 0.
    * - 0: Standard query
    * - 1: Inverse query
    * - 2: Server status request
    * - 3-15: Reserved
    */
   uint8_t op_code;

   /**
    * 1-bit
    *
    * Whether the server is authoritative for the domain name in the query i.e. owns it.
    */
   bool authoritative_answer;

   /**
    * 1-bit
    *
    * - Whether the message length exceeds 512 bytes or not.
    * - Traditionally a hint that the query can be reissued using TCP, for
    * which the length limitation doesn't apply.
    */
   bool truncated_message;

   /**
    * 1-bit
    *
    * Set by the sender of the request if the server should attempt to resolve the query
    * recursively if it does not have an answer readily available.
    */
   bool recursion_desired;

   /**
    * 1-bit
    *
    * Set by the server to indicate whether or not recursive queries are allowed.
    */
   bool recursion_available;

   /**
    * 3-bits
    *
    * Originally reserved for later use, but now used for DNSSEC queries.
    */
   uint8_t reserved;

   /**
    * 4-bits
    *
    * Set by the server to indicate the status of the response, i.e.
    * whether or not it was successful or failed, and in the latter
    * case providing details about the cause of the failure.
    *
    * - 0: No error
    * - 1: Format error
    * - 2: Server failure
    * - 3: Name error
    * - 4: Not implemented
    * - 5: Refused
    * - 6-15: Reserved
    */
   ResultCode response_code;

   /**
    * 16-bits
    *
    * The number of entries in the question section.
    */
   uint16_t question_count;

   /**
    * 16-bits
    *
    * The number of entries in the answer section.
    */
   uint16_t answer_count;

   /**
    * 16-bits
    *
    * The number of entries in the authority section.
    */
   uint16_t authority_count;

   /**
    * 16-bits
    *
    * The number of entries in the additional section.
    */
   uint16_t additional_count;

public:
   PacketHeader() = delete;
   PacketHeader(uint16_t   id,
                bool       query_response,
                uint8_t    op_code,
                bool       authoritative_answer,
                bool       truncated_message,
                bool       recursion_desired,
                bool       recursion_available,
                uint8_t    reserved,
                ResultCode response_code,
                uint16_t   question_count,
                uint16_t   answer_count,
                uint16_t   authority_count,
                uint16_t   additional_count);
   ~PacketHeader() = default;

   static Result<PacketHeader> from_buffer(Ref<PacketBuffer>);

   Result<void>
   write_to_buffer(Ref<PacketBuffer> buf) const;

   void
   print(const std::string &name = "") const;
};

/* ------------------------------------------------------------------------------------------------------- */
