#include "question.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketQuestion::PacketQuestion(const std::string &name, QueryType type, uint16_t class_)
    : m_Name(name), m_Type(type), m_Class(class_) {}

/* ------------------------------------------------------------------------------------------------------- */

Result<PacketQuestion>
PacketQuestion::from_buffer(Ref<PacketBuffer> buf) {
   /* Domain Name */
   auto _name = read_domain_name(buf).except("Invalid domain name");
   RETURN_IF_ERROR(_name);
   auto name = _name.get_value();

   /* Type */
   auto _type = buf->read_uint16().except("Invalid query type");
   RETURN_IF_ERROR(_type);
   auto type = static_cast<QueryType>(_type.get_value());

   /* Class */
   auto _class = buf->read_uint16().except("Invalid query class");
   RETURN_IF_ERROR(_class);
   auto class_ = _class.get_value();

   auto packet = PacketQuestion(name, type, class_);
   return packet;
}

/* ------------------------------------------------------------------------------------------------------- */

Result<void>
PacketQuestion::write_to_buffer(Ref<PacketBuffer> buf) const {
   return Result<void>();
}

/* ------------------------------------------------------------------------------------------------------- */

Result<std::string>
PacketQuestion::read_domain_name(Ref<PacketBuffer> buffer) {
   auto domain_name = buffer->read_qname().except("Failed to read domain name");
   return domain_name;
}

/* ------------------------------------------------------------------------------------------------------- */
