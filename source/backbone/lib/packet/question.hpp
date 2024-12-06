#pragma once

#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class PacketQuestion {
public:
   enum QueryType {
      UNKNOWN = UINT16_MAX,
      A       = 1,
      AAAA    = 28,
      NS      = 2,
      CNAME   = 5,
      SOA     = 6,
      PTR     = 12,
      MX      = 15,
      TXT     = 16,
      SRV     = 33,
      ANY     = 255,
   };

private:
   std::string m_Name;
   QueryType   m_Type;
   uint16_t    m_Class;

public:
   PacketQuestion() = delete;
   PacketQuestion(const std::string &name, QueryType type, uint16_t class_);
   ~PacketQuestion() = default;

   static PacketQuestion
   from_buffer(Ref<PacketBuffer> buffer);
};

/* ------------------------------------------------------------------------------------------------------- */
