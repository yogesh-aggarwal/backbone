#pragma once

namespace DNS
{
   class DNS
   {
   public:
      class Header
      {
      public:
         Header()  = default;
         ~Header() = default;
      };

      class Packet
      {
      public:
         Packet()  = default;
         ~Packet() = default;
      };

      class Question
      {
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

   public:
      DNS()  = default;
      ~DNS() = default;
   };
}
