#include "question.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketQuestion::PacketQuestion(const std::string &name, QueryType type, uint16_t class_)
    : m_Name(name), m_Type(type), m_Class(class_) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketQuestion::PacketQuestion(const PacketQuestion &other)
    : m_Name(other.m_Name), m_Type(other.m_Type), m_Class(other.m_Class) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketQuestion::PacketQuestion(PacketQuestion &&other)
    : m_Name(std::move(other.m_Name)), m_Type(other.m_Type), m_Class(other.m_Class) {}

/* ------------------------------------------------------------------------------------------------------- */

PacketQuestion
PacketQuestion::from_buffer(Ref<PacketBuffer> buffer) {
   // // Assuming PacketBuffer has methods to read data
   // std::string name   = buffer->read_string();
   // QueryType   type   = static_cast<QueryType>(buffer->read_uint16());
   // uint16_t    class_ = buffer->read_uint16();
   return PacketQuestion("", UNKNOWN, 0);
}

/* ------------------------------------------------------------------------------------------------------- */