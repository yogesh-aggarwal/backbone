#pragma once

#include "buffer.hpp"
#include "header.hpp"
#include "question.hpp"
#include "record.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class Packet
{
public:
   PacketHeader                header;
   std::vector<PacketQuestion> questions;
   std::vector<PacketRecord>   answers;
   std::vector<PacketRecord>   authorities;
   std::vector<PacketRecord>   additionals;   // or resources

   Packet(PacketHeader                header,
          std::vector<PacketQuestion> questions,
          std::vector<PacketRecord>   answers,
          std::vector<PacketRecord>   authorities,
          std::vector<PacketRecord>   additionals);
   Packet(const Packet &other);
   Packet(Packet &&other);
   ~Packet() = default;

   Packet &
   operator=(const Packet &other);

   Packet &
   operator=(Packet &&other);

public:
   static Result<Packet>
   from_buffer(Ref<PacketBuffer> buffer);
};

/* ------------------------------------------------------------------------------------------------------- */
