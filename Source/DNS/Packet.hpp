#pragma once

#include <string>
#include <vector>
#include <stdint.h>

namespace DNS
{
   class Packet
   {
   public:
      class Header
      {
      private:
         /**
          * 16-bits
          *
          * - A random identifier is assigned to query packets.
          * - Response packets must reply with the same id.
          * - This is needed to differentiate responses due to the stateless
          * nature of UDP.
          */
         uint16_t m_ID;
         /**
          * 1-bit
          *
          * - 0: Query
          * - 1: Response
          */
         bool m_QueryResponse;
         /**
          * 4-bits
          *
          * Typically always 0.
          * - 0: Standard query
          * - 1: Inverse query
          * - 2: Server status request
          * - 3-15: Reserved
          */
         uint8_t m_OPCode;

         /**
          * 1-bit
          *
          * Whether the server is authoritative for the domain name in the query
          * i.e. owns it.
          */
         bool m_AuthoritativeAnswer;
         /**
          * 1-bit
          *
          * - Whether the message length exceeds 512 bytes or not.
          * - Traditionally a hint that the query can be reissued using TCP, for
          * which the length limitation doesn't apply.
          */
         bool m_TruncatedMessage;
         /**
          * 1-bit
          *
          * Set by the sender of the request if the server should attempt to
          * resolve the query recursively if it does not have an answer readily
          * available.
          */
         bool m_RecursionDesired;
         /**
          * 1-bit
          *
          * Set by the server to indicate whether or not recursive queries are
          * allowed.
          */
         bool m_RecursionAvailable;

         /**
          * 3-bits
          *
          * Originally reserved for later use, but now used for DNSSEC queries.
          */
         uint8_t m_Reserved;

         /**
          * 4-bits
          *
          * Set by the server to indicate the status of the response, i.e.
          * whether or not it was successful or failed, and in the latter case
          * providing details about the cause of the failure.
          *
          * - 0: No error
          * - 1: Format error
          * - 2: Server failure
          * - 3: Name error
          * - 4: Not implemented
          * - 5: Refused
          * - 6-15: Reserved
          */
         uint8_t m_ResponseCode;

         /**
          * 16-bits
          *
          * The number of entries in the question section.
          */
         uint16_t m_QuestionCount;
         /**
          * 16-bits
          *
          * The number of entries in the answer section.
          */
         uint16_t m_AnswerCount;
         /**
          * 16-bits
          *
          * The number of entries in the authority section.
          */
         uint16_t m_AuthorityCount;
         /**
          * 16-bits
          *
          * The number of entries in the additional section.
          */
         uint16_t m_AdditionalCount;

      public:
         Header()  = default;
         ~Header() = default;
      };

      class Question
      {
      private:
         /**
          * Label sequence specifying the domain name to be resolved.
          */
         std::string m_Name;
         /**
          * 2-bytes
          *
          * The record type
          */
         uint16_t m_QuestionType;
         /**
          * 2-bytes
          *
          * The class, in practice always set to 1.
          */
         uint16_t m_Class;

      public:
         Question()  = default;
         ~Question() = default;
      };

      class Record
      {
      public:
         Record()  = default;
         ~Record() = default;
      };

   private:
      Header                m_Header;
      std::vector<Question> m_Questions;
      std::vector<Record>   m_Answers;
      std::vector<Record>   m_Authorities;
      std::vector<Record>   m_Additionals;

   public:
      Packet()  = default;
      ~Packet() = default;
   };
}
