use super::core::{packet_buffer::PacketBuffer, query_type::QueryType};
use crate::utility::result::Result;

#[derive(Clone, Debug)]
pub struct DNSQuestion {
    /**
     * Label sequence specifying the domain name to be resolved.
     */
    pub name: String,

    /**
     * 2-bytes
     *
     * The record type
     */
    pub question_type: QueryType,

    /**
     * 2-bytes
     *
     * The class, in practice always set to 1.
     */
    pub class: u16,
}

impl DNSQuestion {
    pub fn new() -> DNSQuestion {
        DNSQuestion {
            name: String::new(),
            question_type: QueryType::A,
            class: 1,
        }
    }

    pub fn from_buffer(buffer: &mut PacketBuffer) -> Result<DNSQuestion> {
        let mut result = DNSQuestion::new();

        /* Read the domain name */
        buffer
            .read_qname()
            .and_then(|qname| {
                result.name = qname;
                Ok(())
            })
            .expect("Failed to read domain name from buffer.");

        /* Read the question type */
        buffer
            .read_as_u16()
            .and_then(|question_type| {
                result.question_type = QueryType::from_num(question_type);
                Ok(())
            })
            .expect("Failed to read question type from buffer.");

        /* Read the class */
        buffer
            .read_as_u16()
            .and_then(|class| {
                result.class = class;
                Ok(())
            })
            .expect("Failed to read class from buffer.");

        Ok(result)
    }
}
