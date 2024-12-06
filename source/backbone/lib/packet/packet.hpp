#pragma once

#include "buffer.hpp"
#include "header.hpp"
#include "question.hpp"
#include "record.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class Packet {
public:
   PacketHeader                header;
   std::vector<PacketQuestion> questions;
   std::vector<PacketRecord>   answers;
   std::vector<PacketRecord>   authorities;
   std::vector<PacketRecord>   additionals;   // or resources

public:
   Packet() = delete;
   Packet(PacketHeader                header,
          std::vector<PacketQuestion> questions,
          std::vector<PacketRecord>   answers,
          std::vector<PacketRecord>   authorities,
          std::vector<PacketRecord>   additionals);
   ~Packet() = default;

public:
   static Result<Packet>
   from_buffer(Ref<PacketBuffer> buffer);

   Result<void>
   write_to_buffer(Ref<PacketBuffer> buffer) const;
};

/* ------------------------------------------------------------------------------------------------------- */
